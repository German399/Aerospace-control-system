#include "log.hxx"
#include <chrono>
#include <sstream>
#include <iomanip>
bool LOG::init(std::string fileNameSet)
{   
   	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    start_time = ss.str();

    fileName = fileNameSet+ start_time+".txt";
    logDB.bind(db_test_local_get," ");
    
    return true;
}
bool LOG::writeHeader(){
std::ofstream logFileStream(fileName);

return true;
}

bool LOG::update(){


std::ofstream logFileStream(fileName);
//log_obj["TimerLog"] = T;
//log_obj["LogNum"] = 

//logFileStream << log_obj.dump();
logFileStream.close();
 

return true;
}
bool LOG::write(json& log_obj){


std::ofstream logFileStream(fileName);
//log_obj["TimerLog"] = T;
//log_obj["LogNum"] = 

logFileStream << log_obj.dump();
logFileStream.close();
 

return true;
}
bool LOG::timerAutologStart(std::string fileName,std::string logKeys){
init(fileName);
//timerhere
actualLogKeys=logKeys;
if(logDB.logAllKeys_typesget(logKeys)){
log_json =logDB.logAllKeys(logKeys);
//write(log_obj);
update();

return true;
}else
{return false;}
}
bool LOG::stream_autolog(std::string fileName,std::string streamKeys){
    //XREVRANGE mskbo_input + - COUNT 2
return true;
}