#include <string>
#include "config.hxx"
using namespace std;
bool CFG::bind(string cfgName){///<использование локального конфигурационного файла для инициализации программы. Гибкий способ конфигурации для группового моделирования
///возращает переменную с нужным ключом из конфигурационного файла

if(cfgName=="env_local"){
    MODEL_LA_NAME=getenv("MODEL_LA_NAME");
    return true;
}
if(cfgName=="env_bd"){
    //ask bd for config
    //iu1LAdb.bind(db_test_local_get, iu1LA.LaJSONkey);
    //iu1LAdb.get(db_test_local_get, iu1LA.LaJSONkey);
    //MODEL_LA_NAME=getenv("MODEL_LA_NAME");
    return true;


return false;
};
}
string get(string cfgKey){
    string key="";
    return key;
    };
///изменяет в текущей конфигурации один из ключей
bool set(string cfgKey){
    return false;
};


