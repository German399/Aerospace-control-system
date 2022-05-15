#include <nlohmann/json.hpp>
using json = nlohmann::json;
//default values

void testSivo(const char *Sivo_address, int port);
void send2Sivo(json& LAdata, const char *Sivo_address,int port);
