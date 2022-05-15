/*****************************************************************************/
/*                     ФАЙЛ ИСХОДНОГО КОДА МОДЕЛИ ИНС                        */
/*                         ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ                           */
/*                                                                           */
/*****************************************************************************/

/// Подключение стандартных заголовочных файлов
#include <string>

/// Подключение заголовочных файлов для работы с базой данных и пакетами json
#include <nlohmann/json.hpp>

// Подключение пользовательских заголовочных файлов
#include "db/db.hxx"
#include"ins_in.hxx"
#include"ins_out.hxx"

/// Объявление используемых структур
TINS_IN INS_in;
TINS_OUT INS_out;

/// Объявление пространства имен для работы с json
using json = nlohmann::json;

/// Входной json-пакет от диспетчера (тактирование)
extern json Timerdata;

/// Входной json-пакет от ЛА
extern json LAdata;

/// Входной json-пакет от ФПЗ
extern json FPZdata;

/// Выходной json-пакет
extern json INSdata;

// Добавить комментарий что это за функция
/// Функция приема данных из входных json-пакетов и заполенение струкутры INS_in
void from_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        INS_in.tick = Timerdata["count"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ИНС от Таймера!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        // Широта географическая [рад]
        INS_in.phi = LAdata["phi"];

        // Долгота географическая [рад]
        INS_in.lm = LAdata["lm"];

        // Высота абсолютная [м]
        INS_in.H = LAdata["H"];

        // Курс ЛА [рад]
        INS_in.psi = LAdata["psi"];

        // Тангаж ЛА [рад]
        INS_in.tet = LAdata["tet"];

        // Крен ЛА [рад]
        INS_in.gam = LAdata["gam"];

        // Скорость ЛА [м/с]
        INS_in.V = LAdata["V"];

        // Компоненты скорости в георграфической СК [м/с]
        INS_in.V_e = LAdata["V_e"];
        INS_in.V_n = LAdata["V_n"];
        INS_in.V_h = LAdata["V_h"];

        // Компоненты ускорения в связанной СК [м/с/с]
        INS_in.a_x = LAdata["a_x"];
        INS_in.a_y = LAdata["a_y"];
        INS_in.a_z = LAdata["a_z"];

        // Компоненты угловой скорости в связанной СК [рад/с]
        INS_in.w_x = LAdata["w_x"];
        INS_in.w_y = LAdata["w_y"];
        INS_in.w_z = LAdata["w_z"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ИНС от ЛА!"<<std::endl;
    }
}

/// Функция передачи данных в выходной json-пакет и заполенение струкутры INS_out
void to_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        // Широта географическая [рад]
        INSdata["phi"] = INS_out.Data.phi;

        // Долгота географическая [рад]
        INSdata["lm"] = INS_out.Data.lm;

        // Компоненты скорости в георграфической СК [м/с]
        INSdata["V_e"] = INS_out.Data.V_e;
        INSdata["V_n"] = INS_out.Data.V_n;
        INSdata["V_h"] = INS_out.Data.V_h;

        // Компоненты ускорения в связанной СК [м/с/с]
        INSdata["a_x"] = INS_out.Data.a_x;
        INSdata["a_y"] = INS_out.Data.a_y;
        INSdata["a_z"] = INS_out.Data.a_z;

        // Компоненты угловой скорости в связанной СК [рад/с]
        INSdata["w_x"] = INS_out.Data.w_x;
        INSdata["w_x"] = INS_out.Data.w_y;
        INSdata["w_x"] = INS_out.Data.w_z;

        // Курс ЛА [рад]
        INSdata["psi"] = INS_out.Data.psi;

        // Тангаж ЛА [рад]
        INSdata["tet"] = INS_out.Data.tet;

        // Крен ЛА [рад]
        INSdata["gam"] = INS_out.Data.gam;
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка выдачи данных от ИНС!"<<std::endl;
    }
}

// Функция инициализации модели ИНС
short ins_init()
{
    // Широта географическая [рад]
    INS_out.Data.phi = 55.57 * 3.14159265 / 180.0;

    // Долгота географическая [рад]
    INS_out.Data.lm = 38.14 * 3.14159265 / 180.0;

    // Высота абсолютная [м]
    INS_out.Data.H = 120.0;

    // Компоненты скорости в георграфической СК [м/с]
    INS_out.Data.V_e = 0.0;
    INS_out.Data.V_n = 0.0;
    INS_out.Data.V_h = 0.0;

    // Компоненты ускорения в связанной СК [м/с/с]
    INS_out.Data.a_x = 0.0;
    INS_out.Data.a_y = 0.0;
    INS_out.Data.a_z = 0.0;

    // Компоненты угловой скорости в связанной СК [рад/с]
    INS_out.Data.w_x = 0.0;
    INS_out.Data.w_y = 0.0;
    INS_out.Data.w_z = 0.0;

    // Курс ЛА [рад]
    INS_out.Data.psi = 0.0;

    // Тангаж ЛА [рад]
    INS_out.Data.tet = 0.0;

    // Крен ЛА [рад]
    INS_out.Data.gam = 0.0;

    return 0;
}

// Основная функция модели ИНС
short ins()
{
    // Широта географическая [рад]
    INS_out.Data.phi = INS_in.phi;

    // Долгота географическая [рад]
    INS_out.Data.lm = INS_in.lm;

    // Высота абсолютная [м]
    INS_out.Data.H = INS_in.H;

    // Компоненты скорости в георграфической СК [м/с]
    INS_out.Data.V_e = INS_in.V_e * 1.1;
    INS_out.Data.V_n = INS_in.V_n * 1.1;
    INS_out.Data.V_h = INS_in.V_h * 1.1;

    // Компоненты ускорения в связанной СК [м/с/с]
    INS_out.Data.a_x = INS_in.a_x;
    INS_out.Data.a_y = INS_in.a_y;
    INS_out.Data.a_z = INS_in.a_z;

    // Компоненты угловой скорости в связанной СК [рад/с]
    INS_out.Data.w_x = INS_in.w_x;
    INS_out.Data.w_y = INS_in.w_y;
    INS_out.Data.w_z = INS_in.w_z;

    // Курс ЛА [рад]
    INS_out.Data.psi = INS_in.psi;

    // Тангаж ЛА [рад]
    INS_out.Data.tet = INS_in.tet;

    // Крен ЛА [рад]
    INS_out.Data.gam = INS_in.gam;

    return 0;
}