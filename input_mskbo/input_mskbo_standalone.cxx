#include <string.h>
#include "input_mskbo.hxx"
#include "db/db.hxx"
#include "unistd.h"
   int main(){
    std::string Input_db_name = "json_adapter_joustic";
    std::string Input_mskbo_db_name = "INPUT_MSKBOstruct";
    bool first_run=true;
    J JOI;
    DB INPUTdb,INPUT_MSKBO_db;
    INPUTdb.bind(db_test_local_get, Input_db_name);
    INPUT_MSKBO_db.bind(db_test_local_set, Input_mskbo_db_name);

    while(true)
    {
    INPUTdb.get(JOI.Jmskbo);
    //JOI.J_LA;
    
    if(first_run){
    JOI.initJoi();
    JOI.normalizeJoi();
    JOI.printJoi();
    first_run = false;
    }else{
    INPUTdb.get(JOI.Jmskbo);
    JOI.updateJoi();
    JOI.normalizeJoi();}
     //JOI.printJoi();
    //std::cout << JOI.J_LA.dump() << std::endl;
    sleep(1);
    INPUT_MSKBO_db.set(JOI.J_LA);
    }
    return 0;
    }