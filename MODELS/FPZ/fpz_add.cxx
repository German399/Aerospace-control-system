/*****************************************************************************/
/*                      ФАЙЛ ИСХОДНОГО КОДА МОДЕЛИ ФПЗ                       */
/*                         ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ                           */
/*                                                                           */
/*****************************************************************************/

/// Подключение стандартных заголовочных файлов
#include <string>

/// Подключение заголовочных файлов для работы с базой данных и пакетами json
#include <nlohmann/json.hpp>

// Подключение пользовательских заголовочных файлов
#include "db/db.hxx"
#include"fpz_in.hxx"
#include"fpz_out.hxx"

// Период вызова модели [тик]
// Определяет частоту запуска модели 
#define N (double)10

// Шаг счета модели [с]
#define dt ((double)FPZ_in.step * N / 1000.0)

// Температура воздуха на уровне моря [К]
const double T_0 = 288.15;
	
// Плотность воздуха на уровне моря [Па]
const double P_0 = 101325;		
    
// Коэффициент изменеия температуры с изменением высоты [К/м]
const double L = -0.0065;
    
// Универсальная газовая постоянная [Дж/(моль*К)]
const double R = 8.31447;		
    
// Молярная масса сухого воздуха [кг/моль]
const double M = 0.0289644;	

/// Объявление используемых структур
TFPZ_IN FPZ_in;
TFPZ_OUT FPZ_out;

/// Объявление пространства имен для работы с json
using json = nlohmann::json;

/// Входной json-пакет от диспетчера (тактирование)
extern json Timerdata;

/// Входной json-пакет от ЛА
extern json LAdata;

/// Выходной json-пакет 
extern json FPZdata;

/// Функция приема данных из входных json-пакетов и заполенение струкутры FPZ_in
void from_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        FPZ_in.step = Timerdata["timeStep"];
        FPZ_in.tick = Timerdata["count"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ФПЗ  от Таймера!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        FPZ_in.phi = LAdata["phi"];
        FPZ_in.lm = LAdata["lm"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ФПЗ от ЛА!"<<std::endl;
    }
}

/// Функция передачи данных в выходной json-пакет и заполенение струкутры FPZ_out
void to_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        // Радиус Земли [м]
        FPZdata["R"]= FPZ_out.Data.R;

        // Ускорение свободного падения [м/с2]
        FPZdata["g"]= FPZ_out.Data.g;

        // Высота рельефа [м]
        FPZdata["H_r"]= FPZ_out.Data.H_r;

        // Скорость ветра [м/с]
        FPZdata["W"]= FPZ_out.Data.W;
        
        // Курс ветра [м/с]
        FPZdata["psi_W"]= FPZ_out.Data.psi_W;

        // Температура воздуха на высоте H [К]
		FPZdata["T_atmo"] = FPZ_out.Data.T_atmo;

		// Давление воздуха на высоте H и широте phi [Па]
		FPZdata["P_atmo"] = FPZ_out.Data.P_atmo;

		// Плотность воздуха на высоте H и широте phi [кг/м^3]
		FPZdata["rho_atmo"] = FPZ_out.Data.rho_atmo;
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка выдачи данных от ФПЗ!"<<std::endl;
    }
}

// Функция инициализации модели ФПЗ
short fpz_init()
{
    // Радиус Земли [м]
    FPZ_out.Data.R = 6371000.0;

    // Ускорение свободного падения [м/с2]
    FPZ_out.Data.g = 9.81;

    // Высота рельефа [м]
    FPZ_out.Data.H_r = 120.0;

    // Скорость ветра [м/с]
    FPZ_out.Data.W = 0.0;

    // Курс ветра [м/с]
    FPZ_out.Data.psi_W = 0.0;

    // Температура воздуха на высоте H [К]
	FPZ_out.Data.T_atmo = 288.15;

	// Давление воздуха на высоте H и широте phi [Па]
	FPZ_out.Data.P_atmo = 101325.0;

	// Плотность воздуха на высоте H и широте phi [кг/м^3]
	FPZ_out.Data.rho_atmo = 0.0;

    return 0;
}

// Основная функция модели ФПЗ
short fpz()
{
    // Радиус Земли [м]
    FPZ_out.Data.R = 6371000.0;

    // Ускорение свободного падения в зависимости от высоты и широты [м/с^2]
	FPZ_out.Data.g = 9.780318 * (1 + 0.005302*sin(FPZ_in.phi)*sin(FPZ_in.phi) - 
        0.000006*sin(2 * FPZ_in.phi)*sin(2 * FPZ_in.phi)) - 0.000003086 * FPZ_in.H;
	
	// Температура воздуха на высоте H [К]
	FPZ_out.Data.T_atmo = T_0 + FPZ_in.H * L;

	// Давление воздуха на высоте H и широте phi [Па]
	FPZ_out.Data.P_atmo = P_0 * pow((1 + ((L * FPZ_in.H) / T_0)), ((-FPZ_out.Data.g * M) / (R * L)));
	
	// Плотность воздуха на высоте H и широте phi [кг/м^3]
	FPZ_out.Data.rho_atmo  = ((FPZ_out.Data.P_atmo * M) / (R * FPZ_out.Data.T_atmo));

    // Высота рельефа [м]
    FPZ_out.Data.H_r = 120.0;

    // Скорость ветра [м/с]
    FPZ_out.Data.W = 0.0;

    // Курс ветра [м/с]
    FPZ_out.Data.psi_W = 0.0;

    return 0;
}