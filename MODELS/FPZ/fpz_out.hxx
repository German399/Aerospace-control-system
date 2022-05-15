/*****************************************************************************/
/*                       ЗАГОЛОВОЧНЫЙ ФАЙЛ МОДЕЛИ ФПЗ                        */
/*                           ВЫХОДНЫЕ ПАРАМЕТРЫ                              */
/*                                                                           */
/*****************************************************************************/
#ifndef FPZ_OUT_HXX
#define FPZ_OUT_HXX

// Структура выходных параметров ФПЗ
struct TFPZ_OUT
{
    // Выходной json "FPZstruct"

    // Признак готовности модели (подключение к таймеру)
    // Ключ в json "timerReady"
    short timerReady;

    // Признак проведенной инициализации модели
    // Ключ в json "initReady"
    short initReady;

    /*Ниже необходимо написать свой код - наполнение входной структуры*/
    
    struct TData
    {
        // Радиус Земли [м]
        // Ключ в json "R"
        float R;

        // Ускорение свободного падения [м/с2]
        // Ключ в json "g"
        float g;

        // Высота рельефа [м]
        // Ключ в json "H_r"
        float H_r;

        // Скорость ветра [м/с]
        // Ключ в json "W"
        float W;

        // Курс ветра [м/с]
        // Ключ в json "psi_W"
        float psi_W;

        // Температура воздуха на высоте
        // Ключ в json "T_atmo"
		float T_atmo;

		// Давление воздуха на высоте H и широте phi [Па]
        // Ключ в json "P_atmo"
		float P_atmo;

		// Плотность воздуха на высоте H и широте phi [кг/м^3]
        // Ключ в json "rho_atmo"
		float rho_atmo;
    } Data;

    /*Конец пользовательского кода*/
};

extern TFPZ_OUT FPZ_out;

#endif