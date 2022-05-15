/*****************************************************************************/
/*                      ЗАГОЛОВОЧНЫЙ ФАЙЛ МОДЕЛИ ИНС                         */
/*                           ВЫХОДНЫЕ ПАРАМЕТРЫ                              */
/*                                                                           */
/*****************************************************************************/
#ifndef INS_OUT_HXX
#define INS_OUT_HXX

// Структура выходных параметров ИНС
struct TINS_OUT
{
    // Выходной json "INSstruct"

    // Признак готовности модели (подключение к таймеру)
    // Ключ в json "timerReady"
    short timerReady;

    // Признак проведенной инициализации модели
    // Ключ в json "initReady"
    short initReady;

    /*Ниже необходимо написать свой код - наполнение входной структуры*/
    struct TRK
    {   
        // Ключ в json "RK_w1"
        unsigned short w1;

        // Ключ в json "RK_w2"
        unsigned short w2;

        // Ключ в json "RK_w3"
        unsigned short w3;
    } RK;

    struct TSD
    {
        // Достоверность GPS
        // Ключ в json "SD_GPS"
        unsigned short GPS      :1;

        // Достоверность ГЛОНАСС
        // Ключ в json "SD_GLONASS"
        unsigned short GLONASS  :1;

        // Резерв
        unsigned short rez      :14;
    } SD;

    struct TData
    {
        // Широта географическая [рад]
        // Ключ в json "phi"
        float phi;

        // Долгота географическая [рад]
        // Ключ в json "lm"
        float lm;

        // Высота абсолютная [м]
        // Ключ в json "H"
        float H;

        // Компоненты скорости в георграфической СК [м/с]
        // Ключ в json "V_e"
        float V_e;
        // Ключ в json "V_n"
        float V_n;
        // Ключ в json "V_h"
        float V_h;

        // Компоненты ускорения в связанной СК [м/с/с]
        // Ключ в json "a_x"
        float a_x;
        // Ключ в json "a_y"
        float a_y;
        // Ключ в json "a_z"
        float a_z;

        // Компоненты угловой скорости в связанной СК [рад/с]
        // Ключ в json "w_x"
        float w_x;
        // Ключ в json "w_y"
        float w_y;
        // Ключ в json "w_z"
        float w_z;

        // Курс ЛА [рад]
        // Ключ в json "psi"
        float psi;

        // Тангаж ЛА [рад]
        // Ключ в json "tet"
        float tet;

        // Крен ЛА [рад]
        // Ключ в json "gam"
        float gam;

    } Data;

    /*Конец пользовательского кода*/
};

extern TINS_OUT INS_out;

#endif