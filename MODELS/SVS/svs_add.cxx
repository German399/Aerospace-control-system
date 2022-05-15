/*****************************************************************************/
/*                      ФАЙЛ ИСХОДНОГО КОДА МОДЕЛИ СВС                       */
/*                         ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ                           */
/*                                                                           */
/*****************************************************************************/

/// Подключение стандартных заголовочных файлов
#include <string>

/// Подключение заголовочных файлов для работы с базой данных и пакетами json
#include <nlohmann/json.hpp>

// Подключение пользовательских заголовочных файлов
#include "db/db.hxx"
#include"svs_in.hxx"
#include"svs_out.hxx"

/// Объявление используемых структур
TSVS_IN SVS_in;
TSVS_OUT SVS_out;

/// Объявление пространства имен для работы с json
using json = nlohmann::json;

/// Входной json-пакет от диспетчера (тактирование)
extern json Timerdata;

/// Входной json-пакет от ЛА
extern json LAdata;

/// Входной json-пакет от ФПЗ
extern json FPZdata;

/// Выходной json-пакет
extern json SVSdata;

// Добавить комментарий что это за функция
/// Функция приема данных из входных json-пакетов и заполенение струкутры SVS_in
void from_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        SVS_in.tick = Timerdata["count"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных СВС от Таймера!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        // Скорость ЛА [м/с]
        SVS_in.V = LAdata["V"];

        // Высота абсолютная [м]
        SVS_in.H = LAdata["H"];

    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных СВС от ЛА!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        // Ускорение свободного падения [м/с/c]
        SVS_in.g = FPZdata["g"];

        // Скорость ветра [м/с]
        SVS_in.W = FPZdata["W"];

        // Курс ветра [м/с]
        SVS_in.psi_W = FPZdata["psi_W"];

        // Температура воздуха на высоте
	    SVS_in.T_atmo = FPZdata["T_atmo"];

	    // Давление воздуха на высоте H и широте phi [Па]
	    SVS_in.P_atmo = FPZdata["P_atmo"];

	    // Плотность воздуха на высоте H и широте phi [кг/м^3]
	    SVS_in.rho_atmo = FPZdata["rho_atmo"];

    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных СВС от ФПЗ!"<<std::endl;
    }
}

/// Функция передачи данных в выходной json-пакет и заполенение струкутры SVS_out
void to_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        SVSdata["V"]= SVS_out.Data.V;
        SVSdata["H"]= SVS_out.Data.H;
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка выдачи данных от СВС!"<<std::endl;
    }
}

// Функция инициализации модели СВС
short SVS_init()
{
    SVS_out.Data.H = 120.0;
    SVS_out.Data.V = 0.0;

    return 0;
}

// Основная функция модели СВС
short SVS()
{
    SVS_out.Data.H = SVS_in.H * 1.1;
    SVS_out.Data.V = SVS_in.V * 1.2;

    return 0;
}