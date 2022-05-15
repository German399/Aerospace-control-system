/*****************************************************************************/
/*                      ФАЙЛ ИСХОДНОГО КОДА МОДЕЛИ КСУ                       */
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
#include"ksu_in.hxx"
#include"ksu_out.hxx"

/// Объявление пространства имен для работы с json
using json = nlohmann::json;

/// Создание объектов json для взаимодействия с моделями
json OUdata;
json Timerdata;

/// Создание объекта json для модели ИНС
json KSUdata;

/// Создание объектов базы данных для взаимодействия с моделями
DB OUdb;
DB Timerdb;

/// Создание объекта базы даных для модели КСУ
DB KSUdb;

/// Ключи json-пакетов для моделей, с которыми происходит взаимодействие
std::string OU_db_name="OUstruct";
std::string Timer_db_name ="TimerMSKBOstruct";

/// Ключ json-пакета для модели КСУ
std::string KSU_db_name="KSUstruct";

/// Объявление функции приема из json
void from_json();

/// Объявление функции передачи в json
void to_json();

/// Объявление функции инициализации
short ksu_init();

/// Объявление основной функции
short ksu();

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

    /// Связь с базой данных для получения параметров от ОУ
    OUdb.bind(db_test_local_get, OU_db_name);

    /// Связь с базой данных для возвращения значений от КСУ
    KSUdb.bind(db_test_local_set, KSU_db_name);

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
            KSU_in.tick = Timerdata["count"];

            // Формирование признака готовности таймера модели
            KSU_out.timerReady = 1;
            KSUdata["timerReady"] = KSU_out.timerReady;

            // Инициализация модели
            ksu_init();

            // Записать данные инициализации в json
            to_json();

            // Формирование признака проведенной инициализации
            KSU_out.initReady = 1;
            KSUdata["initReady"] = KSU_out.initReady;

            // Записать json-пакет в базу данных
            KSUdb.set(KSUdata);

            // Задержка для ограничения частоты блока инициализации 10Гц
            sleep(0.1);
        }

        // При получении разрешения, запускаем основной цикл
        if(Timerdata["go"] != 0)
        {
            // Получение json-пакетов из базы данных
            Timerdb.get(Timerdata);
            OUdb.get(OUdata);

            // Получение значения тиков от комплекса
            KSU_in.tick = Timerdata["count"];

            // Работа с входным json-пакетом
            from_json();

            // Следующий if выполняется раз в 10 тиков диспетчирующего таймера
            if((int)(prevTick / 10) != (KSU_in.tick / 10))
            {
                /* Ниже код модели */

                ksu();

                /* Конец кода модели */
            
                /// Сформировать выходной json-пакет
                to_json();

                /// Записать jsom-пакет в базу данных
                KSUdb.set(KSUdata);
        
                // Отладка
                //std::cout<<"ksu_tick" << KSU_in.tick / 10 <<std::endl;

                // Запоминаем значение тактирующего таймера на текущем проходе
                prevTick = KSU_in.tick;
            }
            
            // Задержка для уменьшения частоты вызова функции
            sleep(0.005);
        }
    }
    return 0;
}