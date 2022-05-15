/*****************************************************************************/
/*                      ФАЙЛ ИСХОДНОГО КОДА МОДЕЛИ КСУ                       */
/*                         ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ                           */
/*                                                                           */
/*****************************************************************************/

/// Подключение стандартных заголовочных файлов
#include <string>

/// Подключение заголовочных файлов для работы с базой данных и пакетами json
#include <nlohmann/json.hpp>

// Подключение пользовательских заголовочных файлов
#include "db/db.hxx"
#include"ksu_in.hxx"
#include"ksu_out.hxx"

// Период вызова модели [тик]
// Определяет частоту запуска модели 
#define N (double)10

// Шаг счета модели [с]
#define dt ((double)KSU_in.step * N / 1000.0)

/// Объявление используемых структур
TKSU_IN KSU_in;
TKSU_OUT KSU_out;

/// Объявление пространства имен для работы с json
using json = nlohmann::json;

/// Входной json-пакет от диспетчера (тактирование)
extern json Timerdata;

/// Входной json-пакет от ОУ
extern json OUdata;

/// Выходной json-пакет
extern json KSUdata;
//тык он
// Задание коэффициента усиления постоянных времени для апериодического звена 2-го порядка
double T1 = 2.0, T2 = 0.2;
double K = 1;

// Замена переменных
double T_1 = sqrt(T1 * T2);
double T_2 = T1 + T2;

// Вспомогательные переменные
double dy1;
double dy2;
double y_1;
double y_2;


/// Функция приема данных из входных json-пакетов и заполенение струкутры KSU_in
void from_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
		KSU_in.step = Timerdata["timeStep"];
        KSU_in.tick = Timerdata["count"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных КСУ от Таймера!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        KSU_in.stick_gam = OUdata["axis"]["X"];
        KSU_in.stick_tet = OUdata["axis"]["Y"];
        KSU_in.stick_psi = OUdata["rot"]["Z"];
        KSU_in.TCL = OUdata["axis"]["Z"];
        KSU_in.stick_tet = KSU_in.stick_tet * 2.0 - 1.0;
        KSU_in.stick_gam = KSU_in.stick_gam * 2.0 - 1.0;
        KSU_in.stick_psi = KSU_in.stick_psi * 2.0 - 1.0;
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных от ОУ!"<<std::endl;
    }
}

/// Функция передачи данных в выходной json-пакет и заполенение струкутры KSU_out
void to_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        KSUdata["phi_rv"]= KSU_out.Data.phi_rv;
        KSUdata["phi_rn"]= KSU_out.Data.phi_rn;
        KSUdata["phi_el"]= KSU_out.Data.phi_el;
        KSUdata["phi_AT"]= KSU_out.Data.phi_AT;
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка выдачи данных от КСУ!"<<std::endl;
    }
}

// Функция инициализации модели КСУ
short ksu_init()
{
    KSU_out.Data.phi_rv = 0.0;
    KSU_out.Data.phi_el = 0.0;
    KSU_out.Data.phi_rn = 0.0;
    KSU_out.Data.phi_AT = 0.0;
	dy1 = 0.0;
	dy2 = 0.0;
	y_1 = 0.0;
	y_2 = 0.0;

    return 0;
}


// Основная функция модели КСУ
short ksu()
{
	dy1 = y_2;
	dy2 = (K * KSU_in.stick_tet - T_2 * y_2 - y_1) / T_1 * T_1;
	y_1 += dy1 * dt;	
	y_2 += dy2 * dt;
	
	KSU_out.Data.phi_rv = -y_1;
    KSU_out.Data.phi_el = KSU_in.stick_gam;
    KSU_out.Data.phi_rn = KSU_in.stick_psi;
    KSU_out.Data.phi_AT = KSU_in.TCL;

    return 0;
}