#if !defined(SAU_HH)
#define SAU_HH
#include <nlohmann/json.hpp>
#include <iostream>
class SAU///система автоматического управления общего вида
{
    using json = nlohmann::json;
    private:
    json LA, J;
    struct tdata{
    //double lat,lon,H, psi, tet, gam, tetZ, gamZ, psiZ, Vzad,VzadMax, Upsi, Ugam, Utet,V,Ve,Vn,Vh,ax,ay,az,ny,nymax, J_X,J_Y,J_Z,J_Xrot,J_Yrot,J_Zrot;
    double V, Vh, psi, tet, gam, tetZ, gamZ, psiZ, Vzad,VzadMax,J_X,J_Y,J_Z,J_Xrot,J_Yrot,J_Zrot;		
}Sp;//SAU parametrs - параметры САУ, структура хранит значения переменных, необходимых для работы САУ
   tdata prevSp;//параметры состояния предыдущего шага
   ///при необходимости, можно создать массив состояний предыдущих шагов
   ///tdata prevSp[20];
   ///формирование такого массива рекомендуется делать в отдельной функции
   ///её можно назвать void statecontrol()
struct tmode{
    bool auto_pilot, joi_assist,route_mode, privedenie_gor, modeX;
}Mp;//mode parameters, boolean flags, determintes work of SAU. 
tmode MpResult;///в данную структуру записываются результаты работы сау, если функция не отработала
///возвращается false. Позволяет следить за корректностью работы системы автоматического управления
    void from_json();
    void to_json();
    bool formParamAutopilot();
    bool formParamJoi();
    //bool routeDataFromDBcorr();
    //bool modePrivedenieGorizonta();
    //bool modeXParamCorr();
    bool formParam();
    public:
    SAU(json& someLA){
        LA = someLA;
        //std::cout<<"SAU "<< LA.dump()<<std::endl;
        Mp.auto_pilot = false;
        Mp.joi_assist = true;
        Mp.route_mode = false;
        Mp.privedenie_gor = false;
        Mp.modeX = false;
        Sp.VzadMax = 70.0;
        };
    json SAUdata;
    bool first_run=true;
    int update(json &someLA_update, json &someJoi_update);

};

#endif // SAU_HH end
