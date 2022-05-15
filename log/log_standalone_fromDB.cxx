#include <thread>
#include <unistd.h>
#include "log.hxx"


int main(){

LOG logAutoLogger;
json log_json;
std::string fileName = "logMSKBO";
//std::string keys  ="LAstruct json_adapter_joustic";
std::string keys  = "LAstruct KBOstruct";
std::string streamkeys = "mskbo_input";
logAutoLogger.timerAutologStart(fileName ,keys);
while(true)
{
//log_json =logAutoLogger.logAllKeys();
//logAutoLogger.update();
sleep(1);
}

//logAutoLogger.stream_autolog(fileName, streamkeys);
return 0;
//std::thread thr(threadFunction);
}