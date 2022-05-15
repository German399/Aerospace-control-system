#include "../db/db.hxx"
#include <string.h>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
class LOG{
private:
std::string start_time;
std::string fileName;
std::string actualLogKeys;
//Текущий шаг логирования
unsigned long long LogNum;
public:
DB logDB;
json log_json;
bool init(std::string fileName);
bool writeHeader();
bool update();
bool write(json& log_obj);
bool timerAutologStart(std::string fileName,std::string logKeys);
bool stream_autolog(std::string fileName, std::string streamKeys);
//bool timerAutologStart(std::string fileName, json& log_obj);

};