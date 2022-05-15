#include "vis/sivo/sivo.hxx"
#include <string.h>
#include <nlohmann/json.hpp>
class VIS
{
private:
//это значения по умолчанию, их не обязательно передавать в функцию send2sivo
int port=6100;
const char *Sivo_address = "192.168.1.91";
using json = nlohmann::json;
public:
void initConfig(std::string configName=".env");
void displaySend(json& json_obj_vis);
void testVis();
void indSend(json& json_obj_ind);
void indMessageSend(std::string ind_mes);
bool checkFixData(json& some_obj);

};