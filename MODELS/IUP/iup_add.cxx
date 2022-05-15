/*****************************************************************************/
/*                      ФАЙЛ ИСХОДНОГО КОДА МОДЕЛИ ЛА                        */
/*                         ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ                           */
/*                                                                           */
/*****************************************************************************/

/// Подключение стандартных заголовочных файлов
#include <string>
#include <iomanip>
#include <fstream>	// ofstream
#include <sstream>	// stringstream
#include <time.h>   // Для подписи СОКа

/// Подключение заголовочных файлов для работы с базой данных и пакетами json
#include <nlohmann/json.hpp>

// Подключение пользовательских заголовочных файлов
#include "db/db.hxx"
#include"iup_in.hxx"
#include"iup_out.hxx"

/// Объявление используемых структур
TIUP_IN IUP_in;
TIUP_OUT IUP_out;

/// Объявление пространства имен для работы с json
using json = nlohmann::json;

/// Входной json-пакет от диспетчера (тактирование)
extern json Timerdata;

/// Входной json-пакет от КСУ
extern json KSUdata;

/// Входной json-пакет от ФПЗ
extern json FPZdata;

/// Входной json-пакет от ОУ
extern json OUdata;

/// Входной json-пакет от СВС
extern json SVSdata;

/// Входной json-пакет от ИНС
extern json INSdata;

/// Входной json-пакет от ЛА
extern json LAdata;

/// Выходной json-пакет
extern json IUPdata;

/// Функция приема данных из входных json-пакетов и заполенение струкутры LA_in
void from_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        IUP_in.step = Timerdata["timeStep"];
        IUP_in.tick = Timerdata["count"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ИУП от Таймера!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        IUP_in.fromOU.stick_psi = OUdata["rot"]["Z"];
        IUP_in.fromOU.stick_gam = OUdata["axis"]["Y"];
        IUP_in.fromOU.stick_tet = OUdata["axis"]["X"];
        IUP_in.fromOU.TCL = OUdata["axis"]["Z"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ИУП от ОУ!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        IUP_in.fromLA.a_x = LAdata["a_x"];
        IUP_in.fromLA.a_y = LAdata["a_y"];
        IUP_in.fromLA.a_z = LAdata["a_z"];

        IUP_in.fromLA.psi = LAdata["psi"];
        IUP_in.fromLA.tet = LAdata["tet"];
        IUP_in.fromLA.gam = LAdata["gam"];

        IUP_in.fromLA.w_x = LAdata["w_x"];
        IUP_in.fromLA.w_y = LAdata["w_y"];
        IUP_in.fromLA.w_z = LAdata["w_z"];

        IUP_in.fromLA.phi = LAdata["phi"];
        IUP_in.fromLA.lm = LAdata["lm"];
        IUP_in.fromLA.H = LAdata["H"];

        IUP_in.fromLA.V_e = LAdata["V_e"];
        IUP_in.fromLA.V_n = LAdata["V_n"];
        IUP_in.fromLA.V_h = LAdata["V_h"];

        IUP_in.fromLA.V = LAdata["V"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ИУП от ЛА!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        // Радиус Земли [м]
        IUP_in.fromFPZ.R = FPZdata["R"];

        // Ускорение свободного падения [м/с2]
        IUP_in.fromFPZ.g = FPZdata["g"];

        // Высота рельефа [м]
        IUP_in.fromFPZ.H_r = FPZdata["H_r"];

        // Скорость ветра [м/с]
        IUP_in.fromFPZ.W = FPZdata["W"];

        // Курс ветра [м/с]
        IUP_in.fromFPZ.psi_W = FPZdata["psi_W"];

        // Температура воздуха на высоте
		IUP_in.fromFPZ.T_atmo = FPZdata["T_atmo"];

		// Давление воздуха на высоте H и широте phi [Па]
		IUP_in.fromFPZ.P_atmo = FPZdata["P_atmo"];

		// Плотность воздуха на высоте H и широте phi [кг/м^3]
		IUP_in.fromFPZ.rho_atmo = FPZdata["rho_atmo"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ИУП от ФПЗ!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        IUP_in.fromKSU.phi_rv = KSUdata["phi_rv"];
        IUP_in.fromKSU.phi_rn = KSUdata["phi_rn"];
        IUP_in.fromKSU.phi_el = KSUdata["phi_el"];
        IUP_in.fromKSU.phi_AT = KSUdata["phi_AT"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ИУП от КСУ!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        IUP_in.fromSVS.H = SVSdata["H"];
        IUP_in.fromSVS.H = SVSdata["V"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ИУП от СВС!"<<std::endl;
    }

    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        // Широта географическая [рад]
        IUP_in.fromINS.phi = INSdata["phi"];

        // Долгота географическая [рад]
        IUP_in.fromINS.lm = INSdata["lm"];

        // Компоненты скорости в георграфической СК [м/с]
        IUP_in.fromINS.V_e = INSdata["V_e"];
        IUP_in.fromINS.V_n = INSdata["V_n"];
        IUP_in.fromINS.V_h = INSdata["V_h"];

        // Компоненты ускорения в связанной СК [м/с/с]
        IUP_in.fromINS.a_x = INSdata["a_x"];
        IUP_in.fromINS.a_y = INSdata["a_y"];
        IUP_in.fromINS.a_z = INSdata["a_z"];

        // Компоненты угловой скорости в связанной СК [рад/с]
        IUP_in.fromINS.w_x = INSdata["w_x"];
        IUP_in.fromINS.w_y = INSdata["w_x"];
        IUP_in.fromINS.w_z = INSdata["w_x"];

        // Курс ЛА [рад]
        IUP_in.fromINS.psi = INSdata["psi"];

        // Тангаж ЛА [рад]
        IUP_in.fromINS.tet = INSdata["tet"];

        // Крен ЛА [рад]
        IUP_in.fromINS.gam = INSdata["gam"];
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка получения данных ИУП от ИНС!"<<std::endl;
    }
}

/// Функция передачи данных в выходной json-пакет и заполенение струкутры LA_out
void to_json()
{
    /// Обработка возможных ошибок, используется только на этапе отадки
    try
    {
        
    }
    catch (const std::exception& e)
    {
        std::cerr<<"Ошибка выдачи данных ИУП!"<<std::endl;
    }
}

FILE *SOKTextFile = fopen("/home/mskbo-dev/SOK.txt", "w");

// Функция инициализации модели ИУП
short iup_init()
{
    if (SOKTextFile == NULL)		// Если не удалось создать файл записи параметров
	{							// выводим сообщение "Problems"
		puts("Problems");
		return EXIT_FAILURE;
	}
    return 0;

}


static std::string SOKfilename;
std::ofstream SOK;

// Основная функция модели ИУП
short iup()
{   
    static short SOKfirstRun = 1;

    if (SOKfirstRun)
    {
        std::string dmonth, dday, dmin, dhour, dsec;
		std::stringstream str;

		// Далее идет работа со временем. Подробнее читать здесь: http://cppstudio.com/cat/309/326/ и здесь: http://cppstudio.com/post/587/
		// Работа со строками описана тут: http://www.cyberforum.ru/cpp-beginners/thread203685.html
		time_t date_time = time(NULL);
		struct tm* aTm = localtime(&date_time);
		int year = aTm->tm_year + 1900;
		int month = aTm->tm_mon + 1;
		int day = aTm->tm_mday;
		int hour = aTm->tm_hour;
		int min = aTm->tm_min;
		int sec = aTm->tm_sec;

		if (month < 10) dmonth = ".0";
		else dmonth = ".";
		if (day < 10) dday = "0";
		else dday = "";
		if (hour < 10) dhour = "0";
		else dhour = "";
		if (min < 10) dmin = ".0";
		else dmin = ".";
		if (sec < 10) dsec = ".0";
		else dsec = ".";

		str << "/home/mskbo-dev/SOK/TEST_" << dday << day << dmonth << month << "." << year << " " << dhour << hour << dmin << min << dsec << sec << ".txt";
		str >> SOKfilename;


        // Открываем для записи в конец файла
        SOK.open(SOKfilename, std::ios_base::app);

        // Шапка таблицы
        // МСКБО
        SOK << "Время_комплекса ";

        // Регистрация ФПЗ
        SOK << "ФПЗ_R ФПЗ_g ФПЗ_H_r ФПЗ_W ФПЗ_psi_W ФПЗ_T_atmo ФПЗ_P_atmo ФПЗ_rho_atmo ";

        // Регистрация ОУ
        SOK << "ОУ_St_psi ОУ_St_tet ОУ_St_gam ОУ_TCL ";

        // Регистрация КСУ
        SOK << "КСУ_rn КСУ_rv КСУ_el КСУ_AT ";

        // Регистрация ЛА
        SOK << "ЛА_phi ЛА_lm ЛА_H ЛА_psi ЛА_tet ЛА_gam ЛА_V ЛА_V_e ЛА_V_n ЛА_V_h ЛА_a_x ЛА_a_y ЛА_a_z ЛА_w_x ЛА_w_y ЛА_w_z ";

        // Регистрация ИНС
        SOK << "ИНС_phi ИНС_lm ИНС_H ИНС_psi ИНС_tet ИНС_gam ИНС_V_e ИНС_V_n ИНС_V_h ИНС_a_x ИНС_a_y ИНС_a_z ИНС_w_x ИНС_w_y ИНС_w_z ";
    
        // Регистрация СВС
        SOK << "СВС_H СВС_V ";
    
        // Перевод строки в СОК-файле
        SOK << std::endl;

        // Закрыть СОК для записи
		SOK.close();

        //fprintf(SOKTextFile, "Система объективного контроля (СОК)\n\nНачальные условия\n");

        SOKfirstRun = 0;
    }

    if (!SOKfirstRun)
    {
        // Открываем для записи в конец файла
        SOK.open(SOKfilename, std::ios_base::app);
        
        // Первый столбец - время комплекса [с]
        SOK << std::fixed << std::setprecision(2) << (double)(IUP_in.tick * IUP_in.step) / 1000.0 << " ";

        // Регистрация ФПЗ
        SOK << std::fixed << std::setprecision(2) << 
            IUP_in.fromFPZ.R << " " << 
            IUP_in.fromFPZ.g << " " << 
            IUP_in.fromFPZ.H_r << " " << 
            IUP_in.fromFPZ.W << " " << 
            IUP_in.fromFPZ.psi_W << " " << 
            IUP_in.fromFPZ.T_atmo << " " << 
            IUP_in.fromFPZ.P_atmo << " " << 
            IUP_in.fromFPZ.rho_atmo << " " ;

        // Регистрация ОУ
        SOK << std::fixed << std::setprecision(2) << 
            IUP_in.fromOU.stick_psi << " " <<
            IUP_in.fromOU.stick_tet << " " <<
            IUP_in.fromOU.stick_gam << " " <<
            IUP_in.fromOU.TCL << " ";

        // Регистрация КСУ
        SOK << std::fixed << std::setprecision(2) << 
            IUP_in.fromKSU.phi_rn << " " <<
            IUP_in.fromKSU.phi_rv << " " <<
            IUP_in.fromKSU.phi_el << " " <<
            IUP_in.fromKSU.phi_AT << " ";

        // Регистрация ЛА
        SOK << std::fixed << std::setprecision(2) << 
            IUP_in.fromLA.phi << " " <<
            IUP_in.fromLA.tet << " " <<
            IUP_in.fromLA.H << " " <<
            IUP_in.fromLA.psi << " " <<
            IUP_in.fromLA.tet << " " <<
            IUP_in.fromLA.gam << " " <<
            IUP_in.fromLA.V << " " <<
            IUP_in.fromLA.V_e << " " <<
            IUP_in.fromLA.V_n << " " <<
            IUP_in.fromLA.V_h << " " <<
            IUP_in.fromLA.a_x << " " <<
            IUP_in.fromLA.a_y << " " <<
            IUP_in.fromLA.a_z << " " <<
            IUP_in.fromLA.w_x << " " <<
            IUP_in.fromLA.w_x << " " <<
            IUP_in.fromLA.w_x << " ";
            
        // Регистрация ИНС
        SOK << std::fixed << std::setprecision(2) << 
            IUP_in.fromINS.phi << " " <<
            IUP_in.fromINS.tet << " " <<
            IUP_in.fromINS.H << " " <<
            IUP_in.fromINS.psi << " " <<
            IUP_in.fromINS.tet << " " <<
            IUP_in.fromINS.gam << " " <<
            IUP_in.fromINS.V_e << " " <<
            IUP_in.fromINS.V_n << " " <<
            IUP_in.fromINS.V_h << " " <<
            IUP_in.fromINS.a_x << " " <<
            IUP_in.fromINS.a_y << " " <<
            IUP_in.fromINS.a_z << " " <<
            IUP_in.fromINS.w_x << " " <<
            IUP_in.fromINS.w_x << " " <<
            IUP_in.fromINS.w_x << " ";
            
        // Регистрация СВС
        SOK << std::fixed << std::setprecision(2) << 
            IUP_in.fromSVS.H << " " <<
            IUP_in.fromSVS.V << " ";

        // Перевод строки в СОК-файле
        SOK << std::endl;
        // Закрыть СОК для записи
		SOK.close();

    }







    system("clear");
    
    printf("От модели ЛА\n");
    printf("        Широта       Долгота    Высота         КРЕН         ТАНГАЖ       КУРС        Скорость ЛА\n");
    printf("     %8.3f     %8.3f     %8.3f     %8.3f     %8.3f     %8.3f     %8.3f\n\n", 
    IUP_in.fromLA.phi, IUP_in.fromLA.lm, IUP_in.fromLA.H, IUP_in.fromLA.gam, IUP_in.fromLA.tet, IUP_in.fromLA.psi, IUP_in.fromLA.V);
    
    printf("От модели ИНС\n");
    printf("        Широта       Долгота    Высота         КРЕН         ТАНГАЖ       КУРС        Скорость ЛА\n");
    printf("     %8.3f     %8.3f     %8.3f     %8.3f     %8.3f     %8.3f     %8.3f\n\n", 
    IUP_in.fromINS.phi, IUP_in.fromINS.lm, IUP_in.fromINS.H, IUP_in.fromINS.gam, IUP_in.fromINS.tet, IUP_in.fromINS.psi);



    //printf("\033c");
    



    
    return 0;
}