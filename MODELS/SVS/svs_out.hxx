/*****************************************************************************/
/*                       ЗАГОЛОВОЧНЫЙ ФАЙЛ МОДЕЛИ СВС                        */
/*                           ВЫХОДНЫЕ ПАРАМЕТРЫ                              */
/*                                                                           */
/*****************************************************************************/
#ifndef SVS_OUT_HXX
#define SVS_OUT_HXX

// Структура выходных параметров СВС
struct TSVS_OUT
{
    // Выходной json "SVSstruct"

    // Признак готовности модели (подключение к таймеру)
    // Ключ в json "timerReady"
    short timerReady;

    // Признак проведенной инициализации модели
    // Ключ в json "initReady"
    short initReady;

    /*Ниже необходимо написать свой код - наполнение входной структуры*/
    
    struct TData
    {
        // Скорость ЛА [м/с]
        // Ключ в json "V"
        float V;
        
        // Высота ЛА [м]
        // Ключ в json "H"
        float H;
        
    } Data;

    /*Конец пользовательского кода*/
};

extern TSVS_OUT SVS_out;

#endif