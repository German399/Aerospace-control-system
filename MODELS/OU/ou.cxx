#include "ou.hxx"
#include "../db/db.hxx"
#include <iomanip>
#include <fstream>
#include "unistd.h"
using json = nlohmann::json;
bool OU::normalizeJoi(){
        //JA 165 фиолетовые стикеры на дне
    //for (size_t i = 13; i < 17; i++)
    //{
     //std::cout <<J_mskbo[i]["Name"]<<" "<<J_mskbo[i]["Value"]<<" "<<J_mskbo[i]["Offset"] <<'\n';
    //}
    //оси x нейтраль 0.5 отклонение влево x=0 отклонение вправо x=1
    //оси y нейтраль 0.5 джойстик от себя y=1 джойстик на y=0
    //ось z управляется с ближней к пилоту ручки с надписью dvtech. 1 положение от себя к джойстика(поднята вверх), 0 нейтральная в плоскости джойстика
    //поворот по оси z: поворот влево 0, вправо 1.
    //переделать в json
    //use name of joy as 

    if (j_model_connected.JA165){
    Eps = 0.01;
    x_deadzone_const = 0.005;
    x_base_value = 0.5;
    y_deadzone_const = 0.002;
    y_base_value = 0.5;
    z_deadzone_const = 0;
    z_base_value = 1;
    x_rot_deadzone_const = 0;
    x_rot_base_value = 0;
    y_rot_deadzone_const = 0;
    y_rot_base_value = 0;
    z_rot_deadzone_const = 0.03;
    z_rot_base_value = 0.5;
    }
    //saitek x52 всего кнопок 34
    //x правая ручка влево 0 вправо 1
    //y правая ручка вперед 1 на себя 0, y_deadzone 0.01
    //z левая ручка от себя до упора 0, на себя 1.
    //вращение вокруг оси y кольцо вращения на левом джойстике. вправо до упора rot_y 0 влево до упора 1
    //вращение нижнего кольца до упора по оси х rot_x_ по часовой 1, против 0
    //rot z правая ручка поворот влево - 0, вправо 1
    if (j_model_connected.saitek_x52){
    Eps = 0.001;
    x_deadzone_const = 0.001;
    x_base_value = 0.5;
    y_deadzone_const = 0.001;
    y_base_value = 0.5;
    z_deadzone_const = 0.001;
    z_base_value = 1;
    x_rot_deadzone_const = 0.01;
    x_rot_base_value = 0.5;
    y_rot_deadzone_const = 0.01;
    y_rot_base_value = 0.5;
    z_rot_deadzone_const = 0.01;
    z_rot_base_value = 0.5;

    }
    if(J_LA.is_object()){
        if(J_LA["axis"]["X"].is_number_float()){
            if (fabs(J_LA["axis"]["X"].get_ref<json::number_float_t&>()-x_base_value)-x_deadzone_const < Eps){
                J_LA["axis"]["X"] = x_base_value;
            }
        }
        if(J_LA["axis"]["Y"].is_number_float()){
            if (fabs(J_LA["axis"]["Y"].get_ref<json::number_float_t&>()-y_base_value)-y_deadzone_const < Eps){
                J_LA["axis"]["Y"] = y_base_value;
            }
        }
        if(J_LA["axis"]["Z"].is_number_float()){
            if (fabs(J_LA["axis"]["Z"].get_ref<json::number_float_t&>()-z_base_value)-z_deadzone_const < Eps){
                J_LA["axis"]["Z"] = z_base_value;
            }
        }
        if(J_LA["rot"]["X"].is_number_float()){
            if (fabs(J_LA["rot"]["X"].get_ref<json::number_float_t&>()-x_rot_base_value)-x_rot_deadzone_const < Eps){
                J_LA["rot"]["X"] = x_rot_base_value;
            }
        }
        if(J_LA["rot"]["Y"].is_number_float()){
            if (fabs(J_LA["rot"]["Y"].get_ref<json::number_float_t&>()-y_rot_base_value)-y_rot_deadzone_const < Eps){
                J_LA["rot"]["Y"] = y_rot_base_value;
            }
        }
        if(J_LA["rot"]["Z"].is_number_float()){
            if (fabs(J_LA["rot"]["Z"].get_ref<json::number_float_t&>()-z_rot_base_value)-z_rot_deadzone_const < Eps){
                J_LA["rot"]["Z"] = z_rot_base_value;
            }
        }
    }
    return true;
}  

    //todo в протоколе обмена сделать последним элементом массив кнопок. всего кнопок 13
    //}



bool OU::inDataJoi(){
    ///выполняем get запрос к noSQLBD redis
    ///Объект J использует встроенную базу данных J_DB
    OU_DB_general_in.get(Jmskbo);
    ///OU_DB_MSKBO_in.get(Jmskbo); не забыть взять

     return true;
}

bool OU::updateDataJoi(){
    for(auto iter : Jmskbo)    // пока не дойдем до конца
    {
        //TODO сделать возможность подключать несколько джойстиков
        if("Ось X"==iter["Name"]){
            J_LA["axis"]["X"] = iter["Value"];
        }
        if("Ось Y"==iter["Name"]){
            J_LA["axis"]["Y"] = iter["Value"];
        }
        if("Ось Z"==iter["Name"]){
            J_LA["axis"]["Z"] = iter["Value"];
        }
        if("Вращение вокруг оси X"==iter["Name"]){
            J_LA["rot"]["X"] = iter["Value"];
        }
        if("Вращение вокруг оси Y"==iter["Name"]){
            J_LA["rot"]["Y"] = iter["Value"];
        }
        if("Вращение вокруг оси Z"==iter["Name"]){
            J_LA["rot"]["Z"] = iter["Value"];
        } 
    }
    return true;
}
bool OU::outDataJoi(){
if (J_LA!=""){
OU_DB_MSKBO_out.set(J_LA);
    return true;
}
else{
    return false;
}

}
bool OU::initJoi(){
    ///ставим флаги подключения в отрицательное значение
    j_model_connected.saitek_x52 = false;
    j_model_connected.JA165 = false;
    j_model_connected.pedal = false;
    ///Инициализируем нулевыми координатами ключевые значения
    J_LA["axis"] = { {"X", 0.0},{"Y", 0.0},{"Z", 0.0} };
    J_LA["rot"] = { {"X", 0.0},{"Y", 0.0},{"Z", 0.0} };
    OU_DB_general_in.bind(db_test_local_get,Input_general_ou_db_name);
    ///поле для кабиныJ_DB.bind(db_test_local_get,Input_mskbo_ou_db_name);
    OU_DB_MSKBO_out.bind(db_test_local_set, Output_mskbo_db_name);
    


    inDataJoi();
    ///Ищем поле с именем джойстика при помощи итератора по структуре
    for(auto iter : Jmskbo)    // пока не дойдем до конца
    {
        
        if ("f2ae6640-778a-11eb-8001-444553540000"==iter["InputDevice"]){
        j_model_connected.saitek_x52 = true;
        }
        if ("05a81ca0-81d6-11eb-8001-444553540000"==iter["InputDevice"]){
        j_model_connected.JA165 = true;
        }
        if ("a744e070-779a-11eb-8001-444553540000"==iter["InputDevice"]){
        j_model_connected.pedal = true;
        }
        ///если во входном JSONe программа-адапетер упакует несколько джойстиков
        ///то они все определятся, а для каждых из показаний будут определены приоритетные
        //TODO сделать возможность подключать несколько джойстиков

    }

    return true; 
   
}
bool OU::syncStart(){
    Timerdb.bind(db_test_local_get, Timer_db_name);
    
    go = 0;
    while(true){
    try{
    Timerdb.get(Timerdata);
    tick = Timerdata["count"];
    J_LA["timerReady"] = 1;
        if(Timerdata["go"] == 1)
            {    
                // Получение значения тиков от комплекса
                //tick = Timerdata["count"];

                // Формирование признака готовности таймера модели
                //timerReady = 1;
                //J_LA["timerReady"] = 1;
                

                // Записать json-пакет в базу данных
                OU_DB_MSKBO_out.set(J_LA);
                prevTick =Timerdata["count"];
                return true;
            }
        }
    catch (const std::exception& e)
        {
            std::cerr<<"Ошибка при инициализации ОУ!"<<std::endl;
        }
    sleep(0.1);
    }
}
void OU::toFileJoi(){
std::ofstream o("json_adapter_joustic_data.json");
    o << std::setw(4) << Jmskbo  << std::endl;
}
/// Выводит начальные данные, полученные при инициализации органов управления
void OU::printInitJoi(){
    if(j_model_connected.saitek_x52){std::cout<<"К модели подключен джойстик saitek_x52"<<std::endl;}
    if(j_model_connected.JA165){std::cout<<"К модели подключен джойстик JA165"<<std::endl;}
    if(j_model_connected.pedal){std::cout<<"К модели подключены педали"<<std::endl;}
    //std::cout << J_mskbo.dump() << std::endl;
    std::cout <<"При инициализации получены показания джойстика(нейтральное положение):"<<std::endl<< J_LA.dump() << std::endl;
} 
/// выводит отладочные и перепакованные данные 
void OU::printJoi(){
    if(j_model_connected.saitek_x52){std::cout<<"К модели подключен джойстик saitek_x52"<<std::endl;}
    if(j_model_connected.JA165){std::cout<<"К модели подключен джойстик JA165"<<std::endl;}
    if(j_model_connected.pedal){std::cout<<"К модели подключены педали"<<std::endl;}
    std::cout << J_LA.dump() << std::endl;
    //std::cout <<"При инициализации получены показания джойстика(нейтральное положение):"<<std::endl<< J_LA.dump() << std::endl;
}       