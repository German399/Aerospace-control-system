/*****************************************************************************/
/*                           ФАЙЛ ИСХОДНОГО КОДА                             */
/*                               ФУНКЦИЯ MAIN                                */
/*                                                                           */
/*****************************************************************************/


///Включаем для компиляции системные библиотеки.
#include <unistd.h> 
#include <iostream>
#include <string>


/// Библиотека для пользования пакетами json
#include <nlohmann/json.hpp>
/// Подключение стандартных заголовочных файлов для работы с базой данных 
/// Подключение пользовательских заголовочных файлов
#include"db/db.hxx"
#include"kbo.hxx"



using json = nlohmann::json;



int main()
{
    
    //взять из конфигов
    std::string LA_db_name="LAstruct";
    std::string KBO_db_name="KBOstruct";
    std::string Timer_db_name ="TimerMSKBOstruct";

    json LAdata;
    json KBOdata;
    



    DB LAdb, Timerdb, KBOdb;
    KBO KBO1;
    //add struct to bind  enum|from_sau_key|to_db_la_key
    LAdb.bind(db_test_local_get, LA_db_name);
    Timerdb.bind(db_test_local_get, Timer_db_name);

    KBOdb.bind(db_test_local_set, KBO_db_name);

    Timerdb.get(KBO1.Timerdata);
    unsigned long prevTick_kbo = KBO1.Timerdata["count"].get_ref<json::number_float_t&>() / 10;

    //do debug run first(to test connection)
    //iu1LAdb.setClientNameKey(iu1LA.getUniqueId());
    while (true)
    {
    Timerdb.get(KBO1.Timerdata);
    LAdb.get(KBO1.LAdata);

    KBO1.from_json();

    // Выполняется раз в 10 тиков
    if(prevTick_kbo!=KBO1.KBO1.input.tick)
    {
        
        
    KBO1.integrate();
    // Cледующие две строчки будут вместе(1.структура в json 2. json to db)
    KBO1.to_json();
    KBOdb.set(KBO1.KBOdata);
        
    std::cout << KBO1.KBO1.input.tick <<std::endl;
        
    prevTick_kbo = KBO1.Timerdata["count"].get_ref<json::number_float_t&>() / 10;
    }
    sleep(0.005);
    //rework to streams
    //add error handling


    //KBO1.update();



   
    }
}