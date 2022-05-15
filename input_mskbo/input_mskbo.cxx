#include "input_mskbo.hxx"
#include "../db/db.hxx"
#include <iomanip>
#include <fstream>
using json = nlohmann::json;
bool J::normalizeJoi(){
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



bool J::updateJoi(){
    //выполняем get запрос к noSQLBD redis
    J_DB.get(Jmskbo);
    //reply = (redisReply *)redisCommand(c,"GET json_adapter_joustic");
    //если у нас есть данные, записываем их в JSON структуру
    //if (reply != NULL){
    //J_mskbo = json::parse(reply->str);
    //freeReplyObject(reply);
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

bool J::initJoi(){
    j_model_connected.saitek_x52 = false;
    j_model_connected.JA165 = false;
    j_model_connected.pedal = false;
    J_LA["axis"] = { {"X", 0.0},{"Y", 0.0},{"Z", 0.0} };
    J_LA["rot"] = { {"X", 0.0},{"Y", 0.0},{"Z", 0.0} };
    //joyData init
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
    //     std::cout<<"Нет подключения к базе данных, невозможно подключить джойстики, подключитесь к сети МСКБО для корректной работы программы и перезапустите её"<<std::endl;
    //     return false;
    // }
    J_DB.bind(db_test_local_get,"json_adapter_joustic");
    
    updateJoi();
    //joy model autoconfig, initial disconnect all

    //std::cout<<J_mskbo;
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
        //TODO сделать возможность подключать несколько джойстиков

    }

    //std::cout<< std::setw(4) << J_LA << std::endl;
    
     
    //std::cout <<J_mskbo[i]["Name"]<<" "<<J_mskbo[i]["Value"]<<" "<<J_mskbo[i]["Offset"] <<'\n';
    //printf("GET json_adapter_joustic: %s\n", reply->str);
    //LAinit
    return true; 
   
}

void J::toFileJoi(){
std::ofstream o("json_adapter_joustic_data.json");
    o << std::setw(4) << Jmskbo  << std::endl;
}
void J::printJoi(){

    if(j_model_connected.saitek_x52){std::cout<<"К модели подключен джойстик saitek_x52"<<std::endl;}
    if(j_model_connected.JA165){std::cout<<"К модели подключен джойстик JA165"<<std::endl;}
    if(j_model_connected.pedal){std::cout<<"К модели подключены педали"<<std::endl;}
    //std::cout << J_mskbo.dump() << std::endl;
    std::cout <<"При инициализации получены показания джойстика(нейтральное положение):"<<std::endl<< J_LA.dump() << std::endl;
}    