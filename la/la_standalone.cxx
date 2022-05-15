#include"la.hxx"
#include"db/db.hxx"
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <iostream>
using json = nlohmann::json;
int main(){
    gLA LA1("Airplane_001");
    LA1.init("LAstruct.json");
    //взять из конфигов
    std::string SAU_db_name="SAUstruct";
    std::string LA_db_name="LAstruct";
    std::string Input_mskbo_db_name = "INPUT_MSKBOstruct";
    //iu1LA.init("LAstruct.json");
    //load to verify 
    //перезапись параметров на тестовые, пример начальной выставки
    //iu1LA.LAdata["H"] = 1000.0;
    //iu1LA.LAdata["lat"] = 43.4507* 0.017453292519943295769236907684886127134428718885417254560;
    //iu1LA.LAdata["lon"] = 39.9585* 0.017453292519943295769236907684886127134428718885417254560;
    DB SAUdb,LAdb;
    json SAUdata;
    //DB INPUT_MSKBO_db;
    //INPUT_MSKBO_db.bind(db_test_local_get, Input_mskbo_db_name);
    
    
    //add struct to bind  enum|from_sau_key|to_db_la_key
    SAUdb.bind(db_test_local_get, SAU_db_name);

    LAdb.bind(db_test_local_set, LA_db_name);
    //do debug run first(to test connection)
    //iu1LAdb.setClientNameKey(iu1LA.getUniqueId());
    while (true)
    {
    //rework to streams
    //add error handling
    SAUdb.get(LA1.SAUdata);

    //INPUT_MSKBO_db.get(LA1.J_LA);
    //LAdb.get(LA1.LAdata);
    LA1.update();
    
    //iu1LA.print();

    LAdb.set(LA1.LAdata);
    sleep(1);

    }
}