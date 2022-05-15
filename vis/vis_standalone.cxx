#include <unistd.h>
#include "vis/vis.hxx"
#include "db/db.hxx"
int main(){
    VIS RMDvis;
    json LAdata;
    DB LAdb;
    while(true)
    {
    std::string LA_db_name="LAstruct";
    LAdb.bind(db_test_local_get, LA_db_name);
    LAdb.get(LAdata);
    ///todo сделать рассылки на три камеры, если флаг МСКБО, проверять границы,сделать выбор айпишника и порта для пересылки
    RMDvis.checkFixData(LAdata);
    RMDvis.displaySend(LAdata);
    sleep(1);
    }
    return 0;
}