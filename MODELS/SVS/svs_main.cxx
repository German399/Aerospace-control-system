/*****************************************************************************/
/*                      ФАЙЛ ИСХОДНОГО КОДА МОДЕЛИ СВС                       */
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
#include"svs_in.hxx"
#include"svs_out.hxx"

/// Объявление пространства имен для работы с json
using json = nlohmann::json;

/// Создание объектов json для взаимодействия с моделями
json LAdata;
json FPZdata;
json Timerdata;

/// Создание объекта json для модели СВС
json SVSdata;

/// Создание объектов базы данных для взаимодействия с моделями
DB LAdb;
DB FPZdb;
DB Timerdb;

/// Создание объекта базы даных для модели СВС
DB SVSdb;

/// Ключи json-пакетов для моделей, с которыми происходит взаимодействие
std::string LA_db_name="LAstruct";
std::string FPZ_db_name="FPZstruct";
std::string Timer_db_name ="TimerMSKBOstruct";

/// Ключ json-пакета для модели СВС
std::string SVS_db_name="SVSstruct";

/// Объявление функции приема из json
void from_json();

/// Объявление функции передачи в json
void to_json();

/// Объявление функции инициализации
short SVS_init();

/// Объявление основной функции
short SVS();

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

    /// Связь с базой данных для получения параметров от ЛА
    LAdb.bind(db_test_local_get, LA_db_name);

    /// Связь с базой данных для получения параметров от ФПЗ
    FPZdb.bind(db_test_local_get, FPZ_db_name);

    /// Связь с базой данных для возвращения значений от СВС
    SVSdb.bind(db_test_local_set, SVS_db_name);

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
            SVS_in.tick = Timerdata["count"];

            // Формирование признака готовности таймера модели
            SVS_out.timerReady = 1;
            SVSdata["timerReady"] = SVS_out.timerReady;

            // Инициализация модели
            SVS_init();

            // Записать данные инициализации в json
            to_json();

            // Формирование признака проведенной инициализации
            SVS_out.initReady = 1;
            SVSdata["initReady"] = SVS_out.initReady;

            // Записать json-пакет в базу данных
            SVSdb.set(SVSdata);

            // Задержка для ограничения частоты блока инициализации 10Гц
            sleep(0.1);
        }

        // При получении разрешения, запускаем основной цикл
        if(Timerdata["go"] != 0)
        {
            /// Получение json-пакетов из базы данных
            Timerdb.get(Timerdata);
            LAdb.get(LAdata);
            FPZdb.get(FPZdata);

            // Получение значения тиков от комплекса
            SVS_in.tick = Timerdata["count"];

            // Работа с входным json-пакетом
            from_json();

            // Следующий if выполняется раз в 10 тиков диспетчирующего таймера
            if((int)(prevTick / 10) != (SVS_in.tick / 10))
            {
                /* Ниже код модели */

                SVS();

                /* Конец кода модели */
            
                /// Сформировать выходной json-пакет
                to_json();

                /// Записать jsom-пакет в базу данных
                SVSdb.set(SVSdata);
        
                // Отладка
                //std::cout<<"SVS_tick" << SVS_in.tick / 10 <<std::endl;

                // Запоминаем значение тактирующего таймера на текущем проходе
                prevTick = SVS_in.tick;
            }
            
            // Задержка для уменьшения частоты вызова функции
            sleep(0.005);
        }
    }
    return 0;
}