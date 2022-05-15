#include"iup.hxx"
#include"config/general_mskbo.hxx"
#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void IUP::from_json()
{
//KBO1.input.V = LAdata["V"].get_ref<json::number_float_t&>();

return;
}
// void IUP::to_json()
// {
//      KBOdata["V"]= KBO1.output.SVS.Vprib;
// return;
// }

void IUP::print()
{
    //std::cout << LAdata["tet"]<<"      "<<KBOdata["tet"]<<std::endl;
    std::cout << "axisXYZ=" << LAdata["axis"]["X"]<<" "<< LAdata["axis"]["Y"]<<" "<< LAdata["axis"]["Z"]<<std::endl;

    //std::cout<<"Ключ ЛА в базе данных:" << LA_db_name <<std::endl;
    //std::cout << LAdata.dump()<<std::endl;
    //std::cout << LAdata.dump()<<"\r";
    //std::cout<<"Ключ КБО в базе данных:" << KBO_db_name <<std::endl;
    //std::cout << KBOdata.dump()<<std::endl;
    //std::cout << LAdata.dump()<<"\r";
    //KBO.t_KBO = KBO.t_mskbo;
    ///здесь действия
    return;
}
