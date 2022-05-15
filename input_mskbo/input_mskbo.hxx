#include <nlohmann/json.hpp>
#include "../db/db.hxx"
class J///Joystick - класс отвечающий за работу с органами управления 
{
using json = nlohmann::json;
private:
DB J_DB;
//jsondata

    double Eps = 0.01;
    double x_deadzone_const;
    double x_base_value;
    double y_deadzone_const;
    double y_base_value;
    double z_deadzone_const;
    double z_base_value;
    double x_rot_deadzone_const;
    double x_rot_base_value;
    double y_rot_deadzone_const;
    double y_rot_base_value;
    double z_rot_deadzone_const;
    double z_rot_base_value;

public:
json Jmskbo;
json J_LA;///< хранит данные джойстику в удобном для пользователя формате. Формат зависит от конкретного джойстика, можно узнать параметры командой printJoi()

struct j_models{
bool saitek_x52;///<<IMG SRC="https://www.saitek.com/uk/imgs/product/x52/Saitek-X52-Flight-Control-System-01.jpg "> 
bool JA165;///<<IMG SRC="https://avatars.mds.yandex.net/get-mpic/4080439/img_id3310239157473266349.jpeg/13hq "> 
bool pedal;///<<IMG SRC="https://resource.logitechg.com/content/dam/gaming/en/products/flight-rudder-pedals/flight-rudder-pedals-gallery-1.png "> 
}j_model_connected;///<экземпляр данной стуктуры по умолчанию, заполняется функцией initJoi()
/*! \struct j_models input_mskbo.hxx "input_mskbo/input_mskbo.hxx"
 *  \brief Хранит определенную функцией initJoi() модель подключенного джойстика, где false джойстик не подключен, true джойстик подключен. 
 */


bool initJoi();///<получает данные о джойстике по сети. <B>Неявно инициализирует базу данных, делает первичный запрос для проверки работы данной базы</B> 
///<Автоматически определяет модель джойстика
bool updateJoi();///<получает данные о джойстике по сети. Неявно вызывает базу данных и делает запрос к базе данных для обновления данных
bool normalizeJoi();///<нормализирует полученные данные джойстика, устраняя дреф нуля
void toFileJoi();///<сохраняет данные, полученные от джойстика, в файл. Для отладочных целей
void printJoi();///<выводит какой джойстик подключен, и данные основные обработанные данные джойстика на консоль
};