/*****************************************************************************/
/*                      ФАЙЛ ИСХОДНОГО КОДА МОДЕЛИ ЛА                        */
/*                               ФУНКЦИЯ MAIN                                */
/*                                                                           */
/*****************************************************************************/

/// Подключение стандартных заголовочных файлов
#include <unistd.h>
#include <iostream>

/// Подключение заголовочных файлов для работы с базой данных и пакетами json
#include <nlohmann/json.hpp>

// Подключение пользовательских заголовочных файлов
#include"db/db.hxx"
#include"iup_in.hxx"
#include"iup_out.hxx"

/// Объявление пространства имен для работы с json
using json = nlohmann::json;

/// Создание объектов json для взаимодействия с моделями
json Timerdata;
json KSUdata;
json FPZdata;
json OUdata;
json SVSdata;
json INSdata;
json LAdata;

/// Создание объекта json для модели ИУП
json IUPdata;

/// Создание объектов базы данных для взаимодействия с моделями
DB FPZdb;
DB KSUdb;
DB LAdb;
DB OUdb;
DB SVSdb;
DB INSdb;
DB Timerdb;

/// Создание объекта базы даных для модели ИУП
DB IUPdb;

/// Ключи json-пакетов для моделей, с которыми происходит взаимодействие
std::string KSU_db_name="KSUstruct";
std::string FPZ_db_name="FPZstruct";
std::string LA_db_name="LAstruct";
std::string SVS_db_name="SVSstruct";
std::string INS_db_name="INSstruct";
std::string OU_db_name="OUstruct";
std::string Timer_db_name ="TimerMSKBOstruct";

/// Ключ json-пакета для модели ЛА
std::string IUP_db_name="IUPstruct";

/// Объявление функции приема из json
void from_json();

/// Объявление функции передачи в json
void to_json();

/// Объявление функции инициализации
short iup_init();

/// Объявление основной функции
short iup();

/*****************************************************************************/
/*                                   MAIN                                    */
/*                                                                           */
/*****************************************************************************/
int main()
{
    /// Предыдущее значение тактов модели
    unsigned long prevTick;

    /// Связь с базой данных для получения значения таймера
    Timerdb.bind(db_test_local_get, Timer_db_name);

    /// Связь с базой данных для получения параметров от ФПЗ
    FPZdb.bind(db_test_local_get, FPZ_db_name);

    /// Связь с базой данных для получения параметров от КСУ
    KSUdb.bind(db_test_local_get, KSU_db_name);

    /// Связь с базой данных для получения параметров от ОУ
    OUdb.bind(db_test_local_get, OU_db_name);

    /// Связь с базой данных для получения параметров от ЛА
    LAdb.bind(db_test_local_get, LA_db_name);

    /// Связь с базой данных для получения параметров от СВС
    SVSdb.bind(db_test_local_get, SVS_db_name);

    /// Связь с базой данных для получения параметров от ИНС
    INSdb.bind(db_test_local_get, INS_db_name);

    /// Связь с базой данных для возвращения значений от ИУП
    IUPdb.bind(db_test_local_set, IUP_db_name);

    // Получение json-пакета от диспетчера (таймера) из базы данных
    // Для получения Timerdata["go"]
    Timerdb.get(Timerdata);

    prevTick = Timerdata["count"];

    while (1)
    {
        // Получение json-пакета от диспетчера (таймера) из базы данных
        Timerdb.get(Timerdata);

        // Пока не получили разрешение от диспетчера на запуск основного цикла
        // Следим за разрешением на запуск, читаем значение тиков, инициализируем
        if(Timerdata["go"] == 0)
        {    
            // Получение значения тиков от комплекса
            IUP_in.tick = Timerdata["count"];

            // Формирование признака готовности таймера модели
            IUP_out.timerReady = 1;
            IUPdata["timerReady"] = IUP_out.timerReady;

            // Инициализация модели
            iup_init();

            // Записать данные инициализации в json
            to_json();

            // Формирование признака проведенной инициализации
            IUP_out.initReady = 1;
            IUPdata["initReady"] = IUP_out.initReady;

            // Записать json-пакет в базу данных
            IUPdb.set(IUPdata);

            // Задержка для ограничения частоты блока инициализации 10Гц
            sleep(0.1);
        }

        // При получении разрешения, запускаем основной цикл
        if(Timerdata["go"] != 0)
        {
            // Получение json-пакетов из базы данных
            Timerdb.get(Timerdata);
            KSUdb.get(KSUdata);
            FPZdb.get(FPZdata);
            LAdb.get(LAdata);
            SVSdb.get(SVSdata);
            INSdb.get(INSdata);
            OUdb.get(OUdata);

            // Получение значения тиков от комплекса
            IUP_in.tick = Timerdata["count"];

            // Работа с входным json-пакетом
            from_json();

            // Следующий if выполняется раз в 10 тиков диспетчирующего таймера
            if((int)(prevTick / 10) != (IUP_in.tick / 10))
            {
                /* Ниже код модели */

                iup();

                /* Конец кода модели */
            
                /// Сформировать выходной json-пакет
                to_json();

                /// Записать jsom-пакет в базу данных
                IUPdb.set(IUPdata);
        
                // Отладка
                //std::cout<<"iup_tick " << IUP_in.tick / 10 <<std::endl;

                // Запоминаем значение тактирующего таймера на текущем проходе
                prevTick = IUP_in.tick;
            }
            
            // Задержка для уменьшения частоты вызова функции
            sleep(0.005);
        }
    }
    return 0;
}