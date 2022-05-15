#include "la/la.hxx"
#include "db/db.hxx"
#include "sau/sau.hxx"
#include "input_mskbo/input_mskbo.hxx"
#include "vis/vis.hxx"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
int main(int argc, char **argv) {


    //iu1LAdb.cfg_bind("env_local");
    


    /*!создаем объект - летательный аппарат общего вида gLA и даем ему идентификатор Airlane_001
    \code
    gLA iu1LA("Airplane_001");
    \endcode
    */
    gLA iu1LA("Airplane_001");
    ///
    /*!инициализируем его структурой из файла LAstruct.json
    \code
    iu1LA.init("LAstruct.json");
    \endcode
    */
    iu1LA.init("LAstruct.json");
    /*!используем ЛА в связке с базой данных - создаем объект iu1LAdb, это необходимо для сохранения данных
    *подпрограммой log_standalone_fromDB.cxx 
    * работающей независимо от основной программы
    \code
    DB iu1LAdb;
    \endcode
    */
    DB iu1LAdb;
    /*!
    *
    \code

    \endcode
    */
    J iu1LAjoi;
    /*!
    *
    \code

    \endcode
    */
    VIS RMDvis;
    //iu1LAjoi.initJoi();
    //iu1LAjoi.normalizeJoi();
    //iu1LAjoi.printJoi();
    //iu1LA.joiInputUpdate(iu1LAjoi.J_LA);
    
    /*!команда бинд задает параметры работы с базой данных
    *принимает два обязательных и один необязательный, всего три аргумента, 
    *режим работы(задан в структуре enum db.h), имя ключа, по которому надо обращаться к параметру, и опционально можно задать адрес
    *в режимах DB::init_test() и DB::init_local(), адресы заданы в функциях db.cpp, их задавать не надо, режим DB::init_local() задает параметры по умолчанию редиса на локальной машине
    *режим тест гибко настраивается
    *примеры использования других режимов
    *iu1LAdb.bind(db_mskbo_get_set, iu1LA.LaJSONkey,"mskbo");
    *также в режиме есть постфикс get и set, или их комбинация. Это выбор режима работы с базой данных,
    * get - чтение set - запись get_set - чтение и запись
    * это сделано для безопасности работы с базой данных, чтобы не повредить базу данных случайно, выбрав неподходящий запрос
    * если сделать запрос get в режиме set, ничего не произойдет
    *можно вводить свои режимы при необходимости
    */
   
    iu1LAdb.bind(db_test_local_set, iu1LA.LaJSONkey);
    
    
    iu1LAdb.setClientNameKey(iu1LA.getUniqueId());
    // iu1LA.LAdata["VzadMax"] = 70.0;
    iu1LA.LAdata["H"] = 1000.0;
    iu1LA.LAdata["lat"] = 43.4507* 0.017453292519943295769236907684886127134428718885417254560;
    iu1LA.LAdata["lon"] = 39.9585* 0.017453292519943295769236907684886127134428718885417254560;
    // iu1LA.LAdata["psi"] = 0.0;
    SAU iu1LAsau(iu1LA.LAdata);
    while(true){
    //iu1LAjoi.updateJoi();
    //iu1LAjoi.normalizeJoi();
    //iu1LA.joiInputUpdate(iu1LAjoi.J_LA);
    iu1LA.print();
    //fix!
    //iu1LA.LAdata = iu1LAsau.update(iu1LA.LAdata);
    iu1LA.print();
    iu1LA.update();

    iu1LAdb.set(iu1LA.LAdata);
    
    RMDvis.displaySend(iu1LA.LAdata);
    }

return 0;
}
