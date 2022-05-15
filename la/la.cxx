#pragma GCC diagnostic ignored "-pedantic"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>
//#include </home/mskbo/Downloads/aedis-master/include/aedis>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <hiredis.h>

//for networking
//#include "boost/asio.hpp"


//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//la
#include <unistd.h>
//g++ JsonTEST.cpp -I"/home/mskbo/nlohmann_json_cmake_fetchcontent/include"
//apt install nlohmann-json3-dev прописать в докерфайле



#include "la.hxx"
using json = nlohmann::json;

// void gLA::joiInputUpdate(json& j_input){
// LAdata["axis"]["X"]=j_input["axis"]["X"];
// LAdata["axis"]["Y"]=j_input["axis"]["Y"];
// LAdata["axis"]["Z"]=j_input["axis"]["Z"];
// LAdata["rot"]["X"]=j_input["rot"]["X"];
// LAdata["rot"]["Y"]=j_input["rot"]["Y"];
// LAdata["rot"]["Z"]=j_input["rot"]["Z"];
// }
void gLA::from_json()
{
LA.J_X = SAUdata["axis"]["X"];
LA.J_Y = SAUdata["axis"]["X"];
LA.J_Z = SAUdata["axis"]["X"];
LA.J_Xrot = SAUdata["rot"]["X"];
LA.J_Yrot = SAUdata["rot"]["Y"];
LA.J_Zrot = SAUdata["rot"]["Z"];
// LA.V = LAdata["V"];
// LA.Vzad = LAdata["Vzad"];
// LA.VzadMax = LAdata["VzadMax"];
// LA.Ve = LAdata["Ve"];
// LA.Vn = LAdata["Vn"];
// LA.Vh = LAdata["Vh"];
// LA.lat = LAdata["lat"];
// LA.lon = LAdata["lon"];
// LA.H = LAdata["H"];
// LA.psi = LAdata["psi"];
// LA.tet = LAdata["tet"];
// LA.gam = LAdata["gam"];
LA.psiZ = SAUdata["psiZ"];
LA.tetZ = SAUdata["tetZ"];
LA.gamZ = SAUdata["gamZ"];
/* LA.J_X = LAdata["axis"]["X"];
LA.J_Y = LAdata["axis"]["Y"];
LA.J_Z = LAdata["axis"]["Z"];
LA.J_Xrot = LAdata["rot"]["X"];
LA.J_Yrot = LAdata["rot"]["Y"];
LA.J_Zrot = LAdata["rot"]["Z"]; */
}
void gLA::to_json()
{
LAdata["V"]=LA.V;

LAdata["Ve"]=LA.Ve;
LAdata["Vn"]=LA.Vn;
LAdata["Vh"]=LA.Vh;
LAdata["lat"]=LA.lat;
LAdata["lon"]=LA.lon;
LAdata["H"]=LA.H;
LAdata["psi"]=LA.psi;
LAdata["tet"]=LA.tet;
LAdata["gam"]=LA.gam;
///sau
LAdata["Vzad"]=LA.Vzad;
LAdata["VzadMax"]=LA.VzadMax;
LAdata["psiZ"]=LA.psiZ;
LAdata["tetZ"]=LA.tetZ;
LAdata["gamZ"]=LA.gamZ;

LAdata["axis"]["X"] = LA.J_X;
LAdata["axis"]["Y"] = LA.J_Y;
LAdata["axis"]["Z"] = LA.J_Z;

LAdata["rot"]["X"] = LA.J_Xrot;
LAdata["rot"]["Y"] = LA.J_Yrot;
LAdata["rot"]["Z"] = LA.J_Zrot;






/* LAdata["axis"]["X"].get_to(LA.J_X);
LAdata["axis"]["Y"].get_to(LA.J_Y);
LAdata["axis"]["Z"].get_to(LA.J_Z);
LAdata["rot"]["X"].get_to(LA.J_Xrot);
LAdata["rot"]["Y"].get_to(LA.J_Yrot);
LAdata["rot"]["Z"].get_to(LA.J_Zrot); */
}
bool gLA::init(std::string LaStructName){
    LaJSONname = LaStructName;
    LaJSONkey = LaStructName.replace(LaStructName.end()-5,LaStructName.end(),"");
    // bind(db_mskbo,"LAdata");
    // //joyData init
    // if (isunix) {
    //     c = redisConnectUnixWithTimeout(hostname, timeout);
    // } else {
    //     c = redisConnectWithTimeout(hostname, port, timeout);
    // }
    // if (c == NULL || c->err) {
    //     if (c) {
    //         printf("Connection to DB error: %s\n", c->errstr);
    //         redisFree(c);
    //     } else {
    //         printf("Connection to DB error: can't allocate redis context\n");
    //     }
    //     std::cout<<json& LAdata,const gLA::tdata& LA"Нет подключения к базе данных, невозможно подключить джойстики, подключитесь к сети МСКБО для корректной работы программы и перезапустите её"<<std::endl;
    //     return false;
    // }
    // updateJoi();
    //joy model autoconfig, initial disconnect all
    // j_model_connected.saitek_x52 = false;
    // j_model_connected.JA165 = false;
    // j_model_connected.pedal = false;
    LAdata = "{\"lat\": 43.4507, \"lon\": 39.9585, \"H\": 1000.0, \"psi\": 1.9, \"tet\": 0.0, \"gam\": 0.0, \"tetZ\": 0.0, \"gamZ\": 0.0, \"psiZ\": 1.9, \"Upsi\": 0.0, \"Ugam\": 0.0, \"Utet\": 0.0, \"V\": 0.0, \"Vzad\": 0.0, \"VzadMax\": 70.0, \"Ve\": 0.0, \"Vn\": 0.0, \"Vh\": 0.0, \"ax\": 0.0, \"ay\": 0.0, \"az\": 0.0, \"ny\": 1.0, \"nymax\": 10.0}";
    J_LA["axis"] = { {"X", 0.0},{"Y", 0.0},{"Z", 0.0} };
    J_LA["rot"] = { {"X", 0.0},{"Y", 0.0},{"Z", 0.0} };
    //std::cout<<J_mskbo;
    // for(auto iter : J_mskbo)    // пока не дойдем до конца
    // {
        
    //     if ("f2ae6640-778a-11eb-8001-444553540000"==iter["InputDevice"]){
    //     j_model_connected.saitek_x52 = true;
    //     }
    //     if ("05a81ca0-81d6-11eb-8001-444553540000"==iter["InputDevice"]){
    //     j_model_connected.JA165 = true;
    //     }
    //     if ("a744e070-779a-11eb-8001-444553540000"==iter["InputDevice"]){
    //     j_model_connected.pedal = true;
    //     }
    //     //TODO сделать возможность подключать несколько джойстиков

    // }

    //std::cout<< std::setw(4) << J_LA << std::endl;
    
     
    //std::cout <<J_mskbo[i]["Name"]<<" "<<J_mskbo[i]["Value"]<<" "<<J_mskbo[i]["Offset"] <<'\n';
    //printf("GET json_adapter_joustic: %s\n", reply->str);
    //LAinit
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
        //
   // initSivo();
}

void gLA::integrate(){

 double Eps = 0.001;
 double dT = 0.1;
 double Ti = 1;//шаг интегрирования в c
 double Rz = 6400000.0;//радиус земли метров
 usleep(dT*1000000);//в микросекундах
 //вычисление ЛА заданных на основе входных показаний джойстиков
 //считается по оси джойстика
 
 
 //if(abs((J_X-0.5)*M_PI) > Eps){ 

     LA.tet = LA.tet + (dT/Ti)*(LA.tetZ - LA.tet);
     //LAdata["tet"] = tet + (dT/Ti)*(tetZ - tet);
    // }
 //if(abs((J_Y-0.5)*M_PI) > Eps){
     LA.gam = LA.gam + (dT/Ti)*(LA.gamZ - LA.gam);
     //LAdata["gam"] = gam + (dT/Ti)*(gamZ - gam);
     //}
 //if(abs((J_Zrot-1)*M_PI)>Eps){
     
     LA.psi = LA.psi + (dT/Ti)*(LA.psiZ);
    //  LAdata["psi"] = psi + (dT/Ti)*(psiZ);
     //}//нужны педали

 LA.V = LA.V + (dT/Ti)*(LA.Vzad-LA.V);
 LA.lat =  LA.lat + dT*(LA.V *cos(LA.tet)*cos(LA.psi))*(1/Rz);
 LA.lon =  LA.lon + dT*(LA.V *cos(LA.tet)*sin(LA.psi))*(1/(Rz*cos(LA.lat)));
 //LAdata["Vzad"] = J_Z * VzadMax;
 //LAdata["V"] = V + (dT/Ti)*(Vzad-V);
 //LAdata["lat"] =  lat + dT*(V *cos(tet)*cos(psi))*(1/Rz);
 //LAdata["lon "] =  lon + dT*(V *cos(tet)*sin(psi))*(1/(Rz*cos(lat)));
 //LAdata["lon"] =  lon + dT*(V *0.0000003060);
 //LAdata["lat"] =  lat + dT*(V *0.0000001050);
 LA.H = LA.H + dT*(LA.V*sin(LA.tet));
 //LAdata["H"] = H + dT*(V*sin(tet));

}
void gLA::print()
{
//std::cout<<"Заданный ключ в базе данных:" << LaJSONname <<std::endl;
//std::cout << LAdata.dump()<<std::endl;

     
}



// void updateData(bindmode bindmode,std::string bindName){//функция принимает в качестве аргументов режим работы программы с базой данных, имя структуры данных
// switch (bindmode)
//     {
//     case db_mskbo://init exchange
//         DB.initDB();
//         /* code */
//         //make bind with db
//         break;
//     case db_local:
//         DB.initDB_local();
//         /* code */
//         //make bind with db
//         break;
//     case db_test_local:
//         DB.initDB_test_local();
//         /* code */
//         //make bind with db
//         break;
//     case db_test:
//         DB.initDB_test();
//         /* code */
//         //make bind with db
//         break;
//     default:
//         std::cout << "неправильно объявлены имена для подключения к источникам данных"<<std::endl;
//         break;
//     }
 
// }
void gLA::cfgbind(std::string configname){
//get arguments for bind from config
//bind()

}
//TODO: сделать номера портов и адрес через .env

void gLA::update(){
    from_json();
    //print();
    //updateJoi();
    //normalizeJoi();
    //printJoi();
    
    //displaySend();
    integrate();
    to_json();

}

