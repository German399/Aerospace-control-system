Написание новых модулей предполагает использование системы контроля версий для внесения измениний, указанную в руководстве [Как собрать проект для отладки](md_docs/HowToBuild.md).
1. Рекомендуется размещать отдельные модули проекта в отдельных папках.
2. Рекомендации по именованию: модуль модели ЛА располагается в подпапке la папки проекта MSKBO, содержит файлы la.cpp, la.h. Если модель будет запускаться отдельно от main в основной папке проекта(в отдельном исполняемом файле), то надо создать файл вида la.cpp(приведен ниже в качестве примера). Рекомендуется предерживаться такой же системы именований, заменить la на имя вашей модели.
3. Использовать для работы с объектами принципы объектно-ориентированного программирования: создавать объект, объект должен иметь методы init(), update(), from_json(), to_json().
4. Для инициализации используется файл с именем
5. В данном руководстве приведен пример создания - la.cpp и la.h, 
6. Для успешной сборки такого проекта, необходимо внести изменения в файл CMakeLists.txt в папке проекта MSKBO:
~~~~~~~~~~~~~~~
CMakeLists.txt example, что нужно менять
#хороший курс по созданию cmake: https://hsf-training.github.io/hsf-training-cmake-webpage/
cmake_minimum_required(VERSION 3.4.0) 
project(mskbo VERSION 1.1)
#в set указываются необходимые исполняемые файлы, если они используются в проекте. Обязателен db/db.cpp
set(LAexample db/db.cpp la/la.cpp sau/sau.cpp input_mskbo/input_mskbo.cpp udp_simple/udp.cpp vis/visual.cxx vis/sivo/sivo.cxx)
#для работы с базой данных redis требуется линковка библиотеки
target_link_libraries(LAexample LINK_PUBLIC hiredis)
#линковка проекта требует использования библиотеки работы с json объектами - nlohman json.
target_link_libraries(LAexample PRIVATE nlohmann_json::nlohmann_json)
#вместо LAexample и la/la.cxx подставьте свои имена!
~~~~~~~~~~~~~~~
рассмотрим пример заголовочного файла la.h


~~~~~~~~~~~~~~~{.cpp}
//la.h example(замените la на свое имя файла, такое как heliLA.h например)
#include <string.h>
#include <nlohmann/json.hpp>
//ВНИМАНИЕ - НАСТОЯТЕЛЬНО РЕКОМЕНДУЕТСЯ МЕНЯТЬ ИМЯ КЛАССа someLA на другое, оно для примера. Назовите класс по виду моделируемого объекта, 
// примеры названий класса: heliLA(вертолетный ЛА), mig29LA(модель миг 29) или babichenkoPlaneLA(модель самолета авторства Бабиченко)
class someLA///LA - летательный аппарат, рекомендуется использовать принципы
///объектно-ориентированного программирования и наследовать от этого объекта свои классы

{
//
using json = nlohmann::json;
private:

///При создании объекта указывается его уникальный идентификатор
std::string UniqueId;
//имя файла инициализации модели
std::string LaJSONfilename;

public:
std::string LaJSONkey;
//при создании объекта надо обязательно указать его ID, его нельзя изменить в ходе работы программы, это нужно для 
//его однозначной идентификации 
someLA(std::string initId) :UniqueId(initId){}
//для хранения данных ЛА
json LAdata;
//для хранения данных джойстиков
json J_LA;
std::string getUniqueId(){return UniqueId;}
std::string getLaJSONname(){return LaJSONname;}
//std::string getLaJSONkey(){return LaJSONkey;}
void joiInputUpdate(json& j_input);
void print();
void integrate();
struct tdata{
    double lat,lon,H, psi, tet, gam, tetZ, gamZ, psiZ, Vzad,VzadMax, Upsi, Ugam, Utet,V,Ve,Vn,Vh,ax,ay,az,ny,nymax, J_X,J_Y,J_Z,J_Xrot,J_Yrot,J_Zrot;	
}LA;//распакованная структура данных, для её создания из джсон надо вызвать метод from_json(), а после интегрирования упаковать назад при помощи to_json()
//void gLA::from_json(const json& LAdata, gLA::tdata& LA);
void from_json();
void to_json();
void cfgbind(std::string configname);

bool init(std::string LaStructName);
void update();
};
~~~~~~~~~~~~~~~
рассмотрим подробный пример интегрированной модели la.cpp:
~~~~~~~~~~~~~~~{.h}
//la.cpp example
//замените la на свое имя файла!
#include "la.h"
//здесь показан пример подключения БД в файле la.cpp для обмена с другими подсистемами
#include <nlohmann/json.hpp>
using json = nlohmann::json;
//первой приведена основная функция для наглядности. В ней производятся все создания объектов и их конфигурирования
int main(){
string LaStructName = "LAstruct.json";
string LaJSONkey = "LAstruct";

LAdb.bind(db_test_local_get_set, LaJSONkey);
LAdb.setClientNameKey(iu1LA.getUniqueId());
//далее, рекомендуется создать свой объект, его описание размещать в la.h,а его методы в la.cpp
someLA LA1;
//рекомендуется, чтобы объект имел методы init(), update(), from_json(), to_json();
//метод init() вызывается один раз после создания объекта
LA1.init(LaStructName); 
// далее, 
//создание объекта БД, создание соединения с БД и выбор ключа БД
DB LAdb;
//отправка объекта типа JSON в базу данных после инициализации
LAdb.set(LA1.LAdata);
return 0;
while(true){
    
    LA1.update();
    LAdb.set(LA1.LAdata);

}
//распаковывает данные джойстиков
void someLA::joiInputUpdate(json& j_input){
LAdata["axis"]["X"]=j_input["axis"]["X"];
LAdata["axis"]["Y"]=j_input["axis"]["Y"];
LAdata["axis"]["Z"]=j_input["axis"]["Z"];
LAdata["rot"]["X"]=j_input["rot"]["X"];
LAdata["rot"]["Y"]=j_input["rot"]["Y"];
LAdata["rot"]["Z"]=j_input["rot"]["Z"];}
//распаковывает данные из формата json в структуру С++
void someLA::from_json()
{
LA.V = LAdata["V"];
LA.Vzad = LAdata["Vzad"];
LA.VzadMax = LAdata["VzadMax"];
LA.Ve = LAdata["Ve"];
LA.Vn = LAdata["Vn"];
LA.Vh = LAdata["Vh"];
LA.lat = LAdata["lat"];
LA.lon = LAdata["lon"];
LA.H = LAdata["H"];
LA.psi = LAdata["psi"];
LA.tet = LAdata["tet"];
LA.gam = LAdata["gam"];
LA.psiZ = LAdata["psiZ"];
LA.tetZ = LAdata["tetZ"];
LA.gamZ = LAdata["gamZ"];
}
//упаковывает данные в формат json
void someLA::to_json()
{
LAdata["V"]=LA.V;
LAdata["Vzad"]=LA.Vzad;
LAdata["VzadMax"]=LA.VzadMax;
LAdata["Ve"]=LA.Ve;
LAdata["Vn"]=LA.Vn;
LAdata["Vh"]=LA.Vh;
LAdata["lat"]=LA.lat;
LAdata["lon"]=LA.lon;
LAdata["H"]=LA.H;
LAdata["psi"]=LA.psi;
LAdata["tet"]=LA.tet;
LAdata["gam"]=LA.gam;
LAdata["psiZ"]=LA.psiZ;
LAdata["tetZ"]=LA.tetZ;
LAdata["gamZ"]=LA.gamZ;
}
//пример инициализации
bool someLA::init(std::string LaStructName){
    LaJSONname = LaStructName;
    //ключ в базе данных формируется из имени файла инициализации
    LaJSONkey = LaStructName.replace(LaStructName.end()-5,LaStructName.end(),"");
   
    std::string LAstr;
    std::ifstream i(LaJSONname);
    std::stringstream LA1ss;
    LA1ss << i.rdbuf();
    LAstr = LA1ss.str();
    i.close();
    if (json::accept(LAstr))
        {
            gLA::LAdata = json::parse(LAstr);
            return true;    
        }
    else
        {
        return false;
        }

}
//пример цикла интегрирования
void someLA::integrate(){

 double Eps = 0.001;
 double dT = 0.1;
 double Ti = 1;//шаг интегрирования в c
 double Rz = 6400000.0;//радиус земли метров
 usleep(dT*1000000);//в микросекундах
 LA.tet = LA.tet + (dT/Ti)*(LA.tetZ - LA.tet);
 LA.gam = LA.gam + (dT/Ti)*(LA.gamZ - LA.gam);
 LA.psi = LA.psi + (dT/Ti)*(LA.psiZ);
 LA.V = LA.V + (dT/Ti)*(LA.Vzad-LA.V);
 LA.lat =  LA.lat + dT*(LA.V *cos(LA.tet)*cos(LA.psi))*(1/Rz);
 LA.lon =  LA.lon + dT*(LA.V *cos(LA.tet)*sin(LA.psi))*(1/(Rz*cos(LA.lat)));
 LA.H = LA.H + dT*(LA.V*sin(LA.tet));


}
//для отладочных целей выводит значения параметров до цикла интегрирования
void someLA::print()
{
std::cout<<"Заданный ключ в базе данных:" << LaJSONname <<std::endl;
std::cout << LAdata.dump()<<std::endl;

     
}
//вызывает функции в цикле в нужно порядке каждый шаг
void someLA::update(){
    from_json();
    print();
    integrate();
    to_json();

}

~~~~~~~~~~~~~~~