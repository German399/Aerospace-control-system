#ifndef KBO1_MSKBO_H    // если имя KBO_MSKBO_H ещё не определено
#define KBO1_MSKBO_H   // определить имя KBO_MSKBO_H  
#include <nlohmann/json.hpp>
using json = nlohmann::json;
struct tKBO1
{
    struct Tin
    {
  double
            t_kbo,
            ///Широта 
           lat,
            ///Долгота    
           lon,
           H,
           tet,
        V;
  unsigned long tick;
    }input;
    
    struct Tout
    {
  
  struct TSVS
  {
        double Vprib;
        double Vy;
  }SVS;

  struct TINS
  {
      double
        Ve,
        Vn,
        Vh,
        tet;
  }INS;
          
    }output;

  
};

class KBO
{
private:
//вынести в отдельный общий header general_data



public:
tKBO1 KBO1;
json LAdata;
json KBOdata;
json Timerdata;
bool init(std::string KBOStructName);
void print();
void update();
void integrate();
void from_json();
void to_json();
};


#endif //end of KBO1_MSKBO_H
