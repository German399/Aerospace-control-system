/*****************************************************************************/
/*                      ФАЙЛ ИСХОДНОГО КОДА МОДЕЛИ ЛА                        */
/*                         ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ                           */
/*                                                                           */
/*****************************************************************************/

/// Подключение стандартных заголовочных файлов
#include <string>

/// Подключение заголовочных файлов для работы с базой данных и пакетами json
#include <nlohmann/json.hpp>

// Подключение пользовательских заголовочных файлов
#include "db/db.hxx"
#include"la_in.hxx"
#include"la_out.hxx"

// Период вызова модели [тик]
// Определяет частоту запуска модели 
#define N (double)2

// Шаг счета модели [с]
#define dt ((double)LA_in.step * N / 1000.0)

/// Объявление используемых структур
TLA_IN LA_in;
TLA_OUT LA_out;

/// Объявление пространства имен для работы с json
using json = nlohmann::json;

/// Входной json-пакет от диспетчера (тактирование)
extern json Timerdata;

/// Входной json-пакет от КСУ
extern json KSUdata;

/// Входной json-пакет от ФПЗ
extern json FPZdata;

/// Выходной json-пакет
extern json LAdata;

/// Функция приема данных из входных json-пакетов и заполенение струкутры LA_in
void from_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        LA_in.step = Timerdata["timeStep"];
        LA_in.tick = Timerdata["count"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ЛА от Таймера!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        LA_in.phi_rv = KSUdata["phi_rv"];
        LA_in.phi_el = KSUdata["phi_el"];
        LA_in.phi_rn = KSUdata["phi_rn"];
        LA_in.phi_AT = KSUdata["phi_AT"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ЛА от КСУ!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        LA_in.W = FPZdata["W"];
        LA_in.psi_W = FPZdata["psi_W"];
        LA_in.g = FPZdata["g"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ЛА от ФПЗ!"<<std::endl;
    }
}

/// Функция передачи данных в выходной json-пакет и заполенение струкутры LA_out
void to_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        // Широта географическая [рад]
        LAdata["phi"] = LA_out.Data.phi;

        // Долгота географическая [рад]
        LAdata["lm"] = LA_out.Data.lm;

        // Высота абсолютная [м]
        LAdata["H"] = LA_out.Data.H;

        // Курс ЛА [рад]
        LAdata["psi"] = LA_out.Data.psi;

        // Тангаж ЛА [рад]
        LAdata["tet"] = LA_out.Data.tet;

        // Крен ЛА [рад]
        LAdata["gam"] = LA_out.Data.gam;

        // Скорость ЛА [м/с]
        LAdata["V"] = LA_out.Data.V;

        // Компоненты скорости в георграфической СК [м/с]
        LAdata["V_e"] = LA_out.Data.V_e;
        LAdata["V_n"] = LA_out.Data.V_n;
        LAdata["V_h"] = LA_out.Data.V_h;

        // Компоненты ускорения в связанной СК [м/с/с]
        LAdata["a_x"] = LA_out.Data.a_x;
        LAdata["a_y"] = LA_out.Data.a_y;
        LAdata["a_z"] = LA_out.Data.a_z;

        // Компоненты угловой скорости в связанной СК [рад/с]
        LAdata["w_x"] = LA_out.Data.w_x;
        LAdata["w_y"] = LA_out.Data.w_y;
        LAdata["w_z"] = LA_out.Data.w_z;
        
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка выдачи данных от ЛА!"<<std::endl;
    }
}

// Функция инициализации модели ЛА
short la_init()
{
    // Широта географическая [рад]
    LA_out.Data.phi = 55.57 * 3.14159265 / 180.0;

    // Долгота географическая [рад]
    LA_out.Data.lm = 38.14 * 3.14159265 / 180.0;

    // Высота абсолютная [м]
    LA_out.Data.H = 120.0;

    // Курс ЛА [рад]
    LA_out.Data.psi = 0.0;

    // Тангаж ЛА [рад]
    LA_out.Data.tet = 0.0;

    // Крен ЛА [рад]
    LA_out.Data.gam = 0.0;

    // Скорость ЛА [м/с]
    LA_out.Data.V = 0.0;

    // Компоненты скорости в георграфической СК [м/с]
    LA_out.Data.V_e = 0.0;
    LA_out.Data.V_n = 0.0;
    LA_out.Data.V_h = 0.0;

    // Компоненты ускорения в связанной СК [м/с/с]
    LA_out.Data.a_x = 0.0;
    LA_out.Data.a_y = 0.0;
    LA_out.Data.a_z = 0.0;

    // Компоненты угловой скорости в связанной СК [рад/с]
    LA_out.Data.w_x = 0.0;
    LA_out.Data.w_y = 0.0;
    LA_out.Data.w_z = 0.0;

    return 0;
}

// Основная функция модели ЛА
short la()
{
    // Компоненты ускорения в связанной СК [м/с/с]
    LA_out.Data.a_x = LA_in.phi_AT * 20.0;
    LA_out.Data.a_y = 0.0;
    LA_out.Data.a_z = 0.0;

    // Скорость ЛА [м/с]
    LA_out.Data.V += LA_out.Data.a_x * dt;
    
    // Компоненты угловой скорости в связанной СК [рад/с]
    // Крена
    LA_out.Data.w_x = LA_in.phi_el * 0.8;

    // Курса
    LA_out.Data.w_y = LA_in.phi_rn * 0.8 /*+ LA_in.g * tan(LA_out.Data.gam) /
        (LA_out.Data.V * cos(LA_out.Data.tet))*/;

    // Тангажа
    LA_out.Data.w_z = LA_in.phi_rv * 0.8;

    // Курс ЛА [рад]
    LA_out.Data.psi += LA_out.Data.w_y * dt;

    // Тангаж ЛА [рад]
    LA_out.Data.tet += LA_out.Data.w_z * dt;

    // Крен ЛА [рад]
    LA_out.Data.gam += LA_out.Data.w_x * dt;

    // Компоненты скорости в георграфической СК [м/с]
    LA_out.Data.V_e = LA_out.Data.V * cos(LA_out.Data.tet) * sin(LA_out.Data.psi) +
        LA_in.W * sin(LA_in.psi_W);

    LA_out.Data.V_n = LA_out.Data.V * cos(LA_out.Data.tet) * cos(LA_out.Data.psi) +
        LA_in.W * cos(LA_in.psi_W);

    LA_out.Data.V_h = LA_out.Data.V * sin(LA_out.Data.tet);

    // Широта географическая [рад]
    //LA_out.Data.phi += LA_out.Data.V_n * dt / LA_in.R;

    // Долгота географическая [рад]
    //LA_out.Data.lm += LA_out.Data.V_e * dt / (LA_in.R * cos(LA_out.Data.phi));

    // Высота абсолютная [м]
    LA_out.Data.H += LA_out.Data.V_h * dt;

    return 0;
}