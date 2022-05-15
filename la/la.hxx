#include <string.h>
#include <nlohmann/json.hpp>
class gLA///generalLA общего вида летательный аппарат, рекомендуется использовать принципы
///объектно-ориентированного программирования и наследовать от этого объекта свои классы
///Входные параметры
///От других систем


{

using json = nlohmann::json;
private:
//jsondata
///При создании объекта указывается его уникальный идентификатор
std::string UniqueId;
std::string LaJSONname;

public:
std::string LaJSONkey;
///при создании объекта надо обязательно указать его ID, его нельзя изменить в ходе работы программы
gLA(std::string initId) :UniqueId(initId){}
json LAdata;
json SAUdata;
json J_LA;
std::string getUniqueId(){return UniqueId;}
std::string getLaJSONname(){return LaJSONname;}
//std::string getLaJSONkey(){return LaJSONkey;}
void joiInputUpdate(json& j_input);
void inputDB(){
    //получить данные от базы данных, потом обновить данные от джойстиков
}

void print();
void integrate();

struct tdata{
            //входные данные
            //данные от ИУП - джойстиков и других органов управления
    double J_X,
           J_Y,
           J_Z,
           J_Xrot,
           J_Yrot,
           J_Zrot;
	bool J_Btn[100];
            //входные данные от САУ 
    double tetZ, 
           gamZ, 
           psiZ, 
           Vzad,
           VzadMax,

            //внешняя среда
           ///общий глобальный таймер стенда моделирования Добавить
           t_mskbo, 
           We, 
           Wn, 
           gN, 
           gE, 
           gH,
            //входные/выходные данные(на первом шаге входными являются данные инициализации, начальные условия/позиция) Добавить
           t_la,
            ///Широта 
           lat,
            ///Долгота    
           lon,
           H,
           psi, 
           tet, 
           gam,
           Upsi, 
           Ugam,
           Utet,
           V,
           Ve,
           Vn,
           Vh,
           ax,
           ay,
           az,
           ny,
           nymax;

}LA;//распакованная структура данных, для её создания из джсон надо вызвать метод from_json(), а после интегрирования упаковать назад при помощи to_json()
//void gLA::from_json(const json& LAdata, gLA::tdata& LA);
void from_json();
void to_json();
void cfgbind(std::string configname);
//void gLA::to_json(json& LAdata,const gLA::tdata& LA);
//NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(tdata, lat,lon,H, psi, tet, gam, tetZ, gamZ, psiZ, Vzad,VzadMax, Upsi, Ugam, Utet,V,Ve,Vn,Vh,ax,ay,az,ny,nymax, J_X,J_Y,J_Z,J_Xrot,J_Yrot,J_Zrot);
    // void to_json(json& j, const person& p) {
    //     j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
    // }

    // void from_json(const json& j, person& p) {
    //     j.at("name").get_to(p.name);
    //     j.at("address").get_to(p.address);
    //     j.at("age").get_to(p.age);
    // }
//NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(data,lat,lon,H, psi, tet, gam, tetZ, gamZ, psiZ, Upsi, Ugam, Utet,V,Vzad,VzadMax,Ve,Vn,Vh,ax,ay,az,ny,nymax);
bool init(std::string LaStructName);
void update();
};