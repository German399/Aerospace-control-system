#include "sau.hxx"
#include "../la/la.hxx"
#include <cstdio>
using json = nlohmann::json;
///механизм работы сау следующий: в функцию подается json, которому необходима система автоматического управления, и в него записываются параметры
///полученные по результатам работы. САУ добавляет параметры заданные в структуру ЛА, которые потом в соотвествии с законом интегрирования движения
///модель ЛА отрабатывает в интеграторе
//json -> SAU::data
void SAU::from_json()
{
//Sp.V = LA["V"];
//Sp.Vh = LA["Vh"];
//Sp.psi = LA["psi"];
//Sp.tet = LA["tet"];
//Sp.gam = LA["gam"];
//Sp.tetZ = LA["tetZ"];
////Sp.gamZ = LA["gamZ"];
//Sp.psiZ = LA["psiZ"];
//Sp.Vzad = LA["Vzad"];
//Sp.VzadMax = LA["VzadMax"];
 if (Mp.joi_assist==true){
 try{    
 Sp.J_X = J["axis"]["X"].get_ref<json::number_float_t&>(); 
 Sp.J_Y = J["axis"]["Y"].get_ref<json::number_float_t&>();
 Sp.J_Z = J["axis"]["Z"].get_ref<json::number_float_t&>();
 Sp.J_Xrot = J["rot"]["X"].get_ref<json::number_float_t&>();
 Sp.J_Yrot = J["rot"]["Y"].get_ref<json::number_float_t&>();
 Sp.J_Zrot = J["rot"]["Z"].get_ref<json::number_float_t&>();
 }
 catch (const std::exception& e)
{
    std::cerr<<"В САУ мусорные данные от джойстиков! Ошибка перепаковки данных"<<std::endl;
    /* При отсутствия поля не выбивает! */
}
}
}
void SAU::to_json()
{
try{   
SAUdata["axis"]["X"] = Sp.J_X;
SAUdata["axis"]["Y"] = Sp.J_Y;
SAUdata["axis"]["Z"] = Sp.J_Z;
SAUdata["rot"]["X"] = Sp.J_Xrot;
SAUdata["rot"]["Y"] = Sp.J_Yrot;
SAUdata["rot"]["Z"] = Sp.J_Zrot;
}
 catch (const std::exception& e)
{
    std::cerr<<"Из САУ не получилось положить от джойстиков! Ошибка перепаковки данных"<<std::endl;
    /* При отсутствия поля не выбивает! */
}
try{   
SAUdata["tetZ"]= Sp.tetZ;
SAUdata["gamZ"] = Sp.gamZ;
SAUdata["psiZ"] = Sp.psiZ;
SAUdata["Vzad"] = Sp.Vzad;
}
 catch (const std::exception& e)
{
    std::cerr<<"Из САУ не получилось положить заданные параметры! Ошибка перепаковки данных"<<std::endl;
    /* При отсутствия поля не выбивает! */
}
//std::cout<<"до tojsonTetZ " <<LA["tetZ"]<<" знач tetZ="<<Sp.tetZ<<std::endl;    
//LA["tetZ"]=0;//Sp.tetZ;
//LA.emplace("tetZ",Sp.tetZ);
//std::cout<<"после tojsonTetZ " <<LA["tetZ"]<<std::endl;    
//LA["gamZ"]=0;//Sp.gamZ;
//LA["psiZ"]=0;//Sp.psiZ;
//LA["Vzad"]=100;//Sp.Vzad;
//LA["VzadMax"]=200;//Sp.VzadMax;

}

// bool SAU::formParamAutopilot(){
// return false;
// }

bool SAU::formParamJoi(){
Sp.tetZ = -(Sp.J_Y-0.5)*M_PI;
Sp.gamZ  = (Sp.J_X-0.5)*M_PI;
Sp.psiZ  = (Sp.J_Zrot-0.5)*M_PI;
Sp.Vzad = Sp.J_Z * Sp.VzadMax;

return true;
}
// bool SAU::routeDataFromDBcorr()
// {
// return false;
// }
// bool SAU::modePrivedenieGorizonta()
// {
// return false;
// }
// bool SAU::modeXParamCorr()
// {
// return false;
// }
double dTetzCorr=0.1;
double dGamCorr=0.1;
double dPsiCorr=0.1;
bool SAU::formParam()//формирование
{
// Sp.tetZ += dTetzCorr;
// Sp.gamZ += dGamCorr;
// Sp.psiZ += dPsiCorr;
// return true;
return false;
}
int SAU::update(json &someLA_update, json &someJoi_update){

LA = someLA_update;
J = someJoi_update;
 
from_json();
// if (Mp.auto_pilot==true){
// formParamAutopilot();}
if (Mp.joi_assist==true){
formParamJoi();}
// if (Mp.route_mode==true)
// {
// routeDataFromDBcorr();
// }

// if (Mp.privedenie_gor==true){
// modePrivedenieGorizonta();
// }
// if (Mp.modeX==true){
// modeXParamCorr();
// }
formParam();
to_json();
//сохранить необходимые параметры предыдущего шага
/* prevSp.Vzad = LA["Vzad"]; */

//вернуть новый объект ла с заданными значениями
return 0;
  
}

///проверить, работает ли разыменование