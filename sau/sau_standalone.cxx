#include "sau.hxx"
#include "db/db.hxx"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "string"
#include <unistd.h>

using json = nlohmann::json;
int main(){
    //get LA initial data from file
    std::string SAUinit_name = "LAstruct.json";
    std::string LAdb_name = "LAstruct";
    std::string SAU_db_name = "SAUstruct";
    std::string Input_mskbo_db_name = "INPUT_MSKBOstruct";

    //init from LA.json.file
    json Inputdata, SAUdata, LAdata;
    //std::ifstream i(SAUinit_name);
    std::stringstream LA1ss;
    //LA1ss << i.rdbuf();
    //std::string LAstr = LA1ss.str();
    std::string LAstr, SAUstr;
    //std::cout << LAstr;
    //i.close();
    //if ((json::accept(LAstr))&&(first_run==true))


    DB Inputdb,LAdb,SAUdb;
    //get joi data
    Inputdb.bind(db_test_local_get, Input_mskbo_db_name);
    
    LAdb.bind(db_test_local_get, LAdb_name);
    //add struct to bind  enum|from_sau_key|to_db_la_key
    SAUdb.bind(db_test_local_set, SAU_db_name);

    SAU LAsau(SAUdata);

    //tddo debug run first(to test connection)
    while (true)
    {
    //rework to streams
    //add error handling
    if (LAsau.first_run==true){
        //data get from init!!
        Inputdb.get(Inputdata);
                    //SAUdata = json::parse(LAstr);
            LAstr="{\"lat\": 43.4507, \"lon\": 39.9585, \"H\": 1000.0, \"psi\": 1.9, \"tet\": 0.0, \"gam\": 0.0, \"Upsi\": 0.0, \"Ugam\": 0.0, \"Utet\": 0.0, \"V\": 0.0, \"Ve\": 0.0, \"Vn\": 0.0, \"Vh\": 0.0, \"ax\": 0.0, \"ay\": 0.0, \"az\": 0.0, \"ny\": 1.0, \"nymax\": 10.0}";
            LAdata = json::parse(LAstr);
            //SAUstr="{\"lat\": 43.4507, \"lon\": 39.9585, \"H\": 1000.0, \"psi\": 1.9, \"tet\": 0.0, \"gam\": 0.0, \"tetZ\": 0.0, \"gamZ\": 0.0, \"psiZ\": 1.9, \"Upsi\": 0.0, \"Ugam\": 0.0, \"Utet\": 0.0, \"V\": 0.0, \"Vzad\": 0.0, \"VzadMax\": 70.0, \"Ve\": 0.0, \"Vn\": 0.0, \"Vh\": 0.0, \"ax\": 0.0, \"ay\": 0.0, \"az\": 0.0, \"ny\": 1.0, \"nymax\": 10.0}";
            //SAUdata = json::parse(LAstr);
        //LAdb.get(SAUdata);
        LAsau.update(LAdata,Inputdata);
        LAsau.first_run=false;
        SAUdb.set(LAsau.SAUdata);
    } else {
        Inputdb.get(Inputdata);
        LAdb.get(LAdata);
        
        
        LAsau.update(LAdata,Inputdata);
        
        SAUdb.set(LAsau.SAUdata);
    }
    sleep(1);
    
    }
    //get LA initial data from db
    //get sau name from config
    //todo
    //get sau name from db
    //todo
    //never runs
    return 0;
    
    
}