#include <iostream>
#include "vis.hxx"
#include "sivo/sivo.hxx"


bool VIS::checkFixData(json& some_obj){
    
    //lat -> phi град
    //lon -> ln град 
    //CDpackIN.cam.lat = 43.4500 * 0.017453292519943295769236907684886127134428718885417254560;		// Широта			[рад]
	//CDpackIN.cam.lon = 39.9600 * 0.017453292519943295769236907684886127134428718885417254560;		// Долгота		[рад]
	//CDpackIN.cam.ht = 30.;		// Высота			[м]
	//CDpackIN.cam.tet = -1.570796326794896619231321691639751442098584699687552910487;			// Угол Tetta	[рад]
	//CDpackIN.cam.psi = 0.;			// Угол Psi  	[рад]
	//CDpackIN.cam.gam = 0.;//iii;			// Угол Gamma [рад]

try{
//проверяем широту    
if(some_obj["lat"].empty()){
//сделать проверку на возможные границы отображения
if(some_obj["phi"].is_number_float()){
///заполняем поле lat, поскольку оно стандартное для системы визуализации
some_obj["lat"] =some_obj["phi"];
}
}
if(some_obj["lon"].empty()){
//сделать проверку на возможные границы отображения
if(some_obj["lm"].is_number_float()){
some_obj["lon"] =some_obj["lm"];
}
}

}
catch (const std::exception& e)
    {
        std::cerr<<"VIS:Ошибка выдачи данных от ЛА!"<<std::endl;
    }
//проверяем долготу
//ln
return true;
}
void VIS::displaySend(json& json_obj_vis){
send2Sivo(json_obj_vis,Sivo_address,port);

}
void VIS::testVis()
{
testSivo(Sivo_address,port);
}
void VIS::indSend(json& json_obj_ind)
{
    return;
    //not implemented
    //web ind send here
}
void initConfig(std::string configName=".env"){
///todo config from .env file
///readenv
///int port=6100;
///const char *Sivo_address = "195.19.46.45";
///192.168.1.91 92 93
}