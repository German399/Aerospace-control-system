
#include <unistd.h> 
#include <nlohmann/json.hpp>
#include"iup.hxx"
#include"db/db.hxx"
using json = nlohmann::json;
int main(){
    
    //взять из конфигов
    std::string LA_db_name="LAstruct";
    std::string KBO_db_name="KBOstruct";
    //iu1LA.init("LAstruct.json");
    //load to verify 
    //перезапись параметров на тестовые, пример начальной выставки
    //iu1LA.LAdata["H"] = 1000.0;
    //iu1LA.LAdata["lat"] = 43.4507* 0.017453292519943295769236907684886127134428718885417254560;
    //iu1LA.LAdata["lon"] = 39.9585* 0.017453292519943295769236907684886127134428718885417254560;
    DB LAdb;
    DB KBOdb;
    IUP IUPcommon;
    //add struct to bind  enum|from_sau_key|to_db_la_key
    LAdb.bind(db_test_local_get, LA_db_name);

    KBOdb.bind(db_test_local_get, KBO_db_name);
    //do debug run first(to test connection)
    //iu1LAdb.setClientNameKey(iu1LA.getUniqueId());
    while (true)
    {
    //rework to streams
    //add error handling
    LAdb.get(IUPcommon.LAdata);
    KBOdb.get(IUPcommon.KBOdata);
    IUPcommon.print();

    sleep(1);
    
    }
}