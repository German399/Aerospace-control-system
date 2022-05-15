#ifndef IUP_COMMON_MSKBO_H    // если имя KBO_MSKBO_H ещё не определено
#define IUP_COMMON_MSKBO_H   // определить имя KBO_MSKBO_H  
#include <string>
#include <nlohmann/json.hpp>
//#include "config/general_mskbo.hxx"
//#include "general_mskbo.h"
using json = nlohmann::json;


class IUP
{
private:
//вынести в отдельный общий header general_data

void from_json();
void to_json();
public:
json LAdata;
json KBOdata;
std::string LA_db_name;
std::string KBO_db_name;
void print();
void integrate();
};
#endif //end of IUP_COMMON_MSKBO_H 
