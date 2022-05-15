

#include <string>
#include <iostream>
#include <stdexcept>
#include <stdio.h>	
#include <unistd.h>
#include <time.h>
#include <chrono>
#include <thread>
#include "config/config.hxx"
#include "db/db.hxx"
using json = nlohmann::json;///<Пространство имен, показывающее что объект типа JSON использует библиотеку nlohman JSON
using namespace std;
///Функция exec возвращает результат работы программы в виде строки, вызванной и выданный в командную строку, нужна для работы 
///с системнами вызовами, считываниях результата их вызова
std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
///Функция проверяет, установлен и работает ли БД redis
bool test_redis(){
//TODO add test for non local redis
//TODO add test for 
//проверяем, установлен и работает ли redis. Отправляем ему тестовый запрос и проверяем, получили ли стандартный ответ PONG в четырех символах
if(exec("redis-cli ping").find("PONG")==0){
    cout<<"redis db работает\n";
    return true;
    }
    else{    
        return false;
        }
}
/*! \brief Диспетчер стенда МСКБО мультипрограммной конфигурации
 *          Осуществляет запуск всех программ, инициализацию и работу таймера основного цикла, 
 *          синхронный старт всех исполняемых файлов.
 */
int main(int argc, char *argv[])
{
    //string command1 = "./MSKBOexec";
    //string command2 = "./mskboLOGexec";
    //Проверяем, работает ли база данных. Если не работает - запускаем в фоне
    if(!test_redis()){ 
    /// @warning На данном этапе, работает только для РМИ. Требуется написать блок конфигурации
    ///
    ///Для работы требуется БД redis, собранная из исходных кодов.
    /// @warning Конфигурационный файл содержит разрешение для небезопасного доступа всех клиентов в локальной сети
    ///
    ///и запускается в фоне с опциями в конфигурационном файле: protected-mode no и daemonize yes
    system("redis-server \"/home/mskbo-dev/redis-stable/redis.conf\"");
    sleep(1);
    if (!test_redis()){
        ///Если после команды запуска база данных redis не отвечает, то диспетчер завершает свою работу
        cout<<"redis server is not working properly\n";
        return 1;
    }
    }
    //В нижестоящем блоке формируются команды запуска программ
    //Эта часть аргумента командной строки basg, чтобы запускать программу в фоне, перенаправляя вывод.
    //Это позволяет запустить несколько программ в одной консоли
    string Run_bgd = " </dev/null &> /dev/null";
    //запускать в фоне и писать в файл(не работает)
    //string Run_bgd_1 = " & >> "+filename_log;
    string TIMER = "TimerMSKBOstruct";
    //string log = "./MSKBOlog"+Run_bgd;
    //Собираем аргументы для передачи системы всех исполняемых файлов в конфигурации multiexe build
    string OU = "./OU_exe"+Run_bgd;
    string FPZ = "./FPZ_exe"+Run_bgd;
    string KSU = "./KSU_exe"+Run_bgd;
    string LA = "./LA_exe"+Run_bgd;
    string INS = "./INS_exe"+Run_bgd;
    string SVS = "./SVS_exe"+Run_bgd;
    string IUP = "./IUP_exe"+Run_bgd;
    //string VIS = "";
    ///@todo как управлять исполнением и гарантировать последовательность срабатывания тиков
    //Начальные параметры таймера TODO:Вынести в отдельный header
    ///@todo описать конфигуратор
    ///@todo разбить диспетчер на множество функций
    //millisec цена тика, 10 = 0.01 sec
    unsigned long timeStep = 10;
    unsigned long count = 0;
    unsigned long maxCount;
    double MSKBO_count_runtime = 0;
    //признак запуска моделирования, переход в рабочий режим 0 - не работаем, 1 - старт.
    short go = 0;

timespec _time, _remain;

_time = {0, timeStep*1000000};
_remain.tv_nsec = 0;
DB timerdb;
json Timerdata;
//инициализация структуры таймера в БД от диспечера перед пуском моделей
Timerdata["timeStep"] = timeStep;
Timerdata["go"] = go;
Timerdata["count"] = count;
//очистить базу данных перед запуском
system("redis-cli \"FLUSHALL\" </dev/null &> /dev/null");
sleep(2);
///@todo сделать проверку, работают ли запросы к бд на чтение и запись при первой записи значения таймера
timerdb.bind(db_test_local_set, TIMER);
timerdb.set(Timerdata);

//system("redis-cli "flushDB SYNC" </dev/null &> /dev/null");
system(FPZ.c_str());
system(INS.c_str());
system(SVS.c_str());
system(IUP.c_str());
system(KSU.c_str());
system(LA.c_str());
system(OU.c_str());


json configData;

//начало костыля
DB FPZdb;
DB KSUdb;
DB LAdb;
DB OUdb;
DB INSdb;
DB SVSdb;
DB IUPdb;
/// 
std::string KSU_db_name="KSUstruct";
std::string FPZ_db_name="FPZstruct";
std::string LA_db_name="LAstruct";
std::string INS_db_name="INSstruct";
std::string SVS_db_name="SVSstruct";
std::string OU_db_name="OUstruct";
//std::string Timer_db_name ="TimerMSKBOstruct";
std::string IUP_db_name="IUPstruct";
 

// Связь с базой данных для получения параметров от ФПЗ
FPZdb.bind(db_test_local_get, FPZ_db_name);

// Связь с базой данных для получения параметров от КСУ
KSUdb.bind(db_test_local_get, KSU_db_name);

// Связь с базой данных для получения параметров от ОУ
OUdb.bind(db_test_local_get, OU_db_name);

// Связь с базой данных для получения параметров от ЛА
LAdb.bind(db_test_local_get, LA_db_name);

// Связь с базой данных для получения параметров от ИНС
INSdb.bind(db_test_local_get, INS_db_name);

// Связь с базой данных для получения параметров от СВС
SVSdb.bind(db_test_local_get, SVS_db_name);

// Связь с базой данных для возвращения значений от ИУП
IUPdb.bind(db_test_local_get, IUP_db_name);
int timerReady[7]{0,0,0,0,0,0,0},initReady[7]{0,0,0,0,0,0,0};
//конец костыля
sleep(1);
while(true){

    for(int i = 0; i < 7; i++){
        if((timerReady[i]!= true)||(initReady[i] != true)){
            configData = "";
            switch(i){
            case 0:
            try{
                FPZdb.get(configData);
            }
            catch (const std::exception& e)
            {
                std::cerr<<"дисп:Ошибка получения данных от ФПЗ!"<<std::endl;
            }
            break;
            case 1:
            try{
                KSUdb.get(configData);
            }
            catch (const std::exception& e)
            {
                std::cerr<<"дисп:Ошибка получения данных от КСУ!"<<std::endl;
            }
            break;
            case 2:
            try{
                OUdb.get(configData);
            }
            catch (const std::exception& e)
            {
                std::cerr<<"дисп:Ошибка получения данных от ОУ!"<<std::endl;
            }
            break;
            case 3:
            try{
                LAdb.get(configData);
            }
            catch (const std::exception& e)
            {
                std::cerr<<"дисп:Ошибка получения данных от ЛА!"<<std::endl;
            }
            break;
            case 4:
            try{
                INSdb.get(configData);
            }
            catch (const std::exception& e)
            {
                std::cerr<<"дисп:Ошибка получения данных от ИНС!"<<std::endl;
            }
            break;
            case 5:
            try{
                IUPdb.get(configData);
            }
            catch (const std::exception& e)
            {
                std::cerr<<"дисп:Ошибка получения данных от ИУП!"<<std::endl;
            }
            break;
            case 6:
            try{
                SVSdb.get(configData);
            }
            catch (const std::exception& e)
            {
                std::cerr<<"дисп:Ошибка получения данных от СВС!"<<std::endl;
            }
            break;
            };
            try{
            //cout << configData.dump()<<configData["initReady"]<<configData["timerReady"];
                initReady[i] = configData["initReady"].get_ref<json::number_integer_t&>();
                timerReady[i] = configData["timerReady"].get_ref<json::number_integer_t&>();
            }
            catch (const std::exception& e)
            {
                std::cerr<<"Диспетчер:еще не все данные инициализированны"<<std::endl;
            }
            sleep(0.05);
        }
    }
    //во всех ключах базы данных, должны лежать {"initReady":1,"timerReady":1}
    if((initReady[0]== true)&&(initReady[1]== true)&&(initReady[2]== true)&&(initReady[3]== true)&&(initReady[4]== true)&&(initReady[5]== true)&&(timerReady[0]= true)&&(timerReady[1]= true)&&(timerReady[2]= true)&&(timerReady[3]= true)&&(timerReady[4]= true)&&(timerReady[5]= true)&&(initReady[6]== true)&&(timerReady[6]= true)){
    //инициализация закончена
    std::cout << "Диспетчер:инициализация успешно завершена" << std::endl;
    go = 1;
    Timerdata["go"] = go;
    break;
    }

}
    //system(IUP.c_str());
while(true)
{
    //nanosleep( &_time, &_remain);
    std::this_thread::sleep_for(std::chrono::milliseconds(timeStep));

    count++;
    MSKBO_count_runtime = timeStep*count/1000.;
    Timerdata["count"] = count;
    Timerdata["MSKBO_count_runtime"] = MSKBO_count_runtime; 
    
    timerdb.set(Timerdata);
    //std::cout<<"count=" << count << "MSKBO_count_runtime=" << MSKBO_count_runtime << std::endl;
    //if (count< 10){break;}

    //
    //system(INS.c_str());
    //system(SVS.c_str());
    //system(IUP.c_str());
    if (count == 100000){break;}
}
    
    //test comment
    //system(command2.c_str());
    //Остановка всех исполняемых файлов системным вызовом
    system("ps aux  |  grep -i OU_exe  |  awk '{print $2}'  |  xargs kill -9");
    system("ps aux  |  grep -i SAU_exe |  awk '{print $2}'  |  xargs kill -9");
    system("ps aux  |  grep -i KSU_exe  |  awk '{print $2}'  |  xargs kill -9");
    system("ps aux  |  grep -i LA_exe  |  awk '{print $2}'  |  xargs kill -9");
    system("ps aux  |  grep -i INS_exe  |  awk '{print $2}'  |  xargs kill -9");
    system("ps aux  |  grep -i SVS_exe  |  awk '{print $2}'  |  xargs kill -9");

    system("ps aux  |  grep -i IUP_exe  |  awk '{print $2}'  |  xargs kill -9");
    return 0;

}
