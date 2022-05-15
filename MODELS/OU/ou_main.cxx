/*****************************************************************************/
/*                      ФАЙЛ ИСХОДНОГО КОДА МОДЕЛИ ОУ                        */
/*                               ФУНКЦИЯ MAIN                                */
/*                                                                           */
/*****************************************************************************/

#include <string.h>
#include "ou.hxx"
#include "db/db.hxx"
#include "unistd.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
   int main(){
   ///Объявляем объект типа органов управления, описанного в ou.hxx
   
   OU ou1;
   ou1.Input_general_ou_db_name = "json_adapter_joustic";///<Выбираем ключи для работы с базой данных json_adapter_joustic - ключ, в который пишет xInput
   ou1.Input_cabin_db_name = "cabin_adapter_mskbo";///<cabin_adapter_mskbo - ключ, в который пишет адаптер для подключения кабины МСКБО

   ou1.Output_mskbo_db_name = "OUstruct";///<выходная структура INPUT_MSKBOstruct
   ou1.Timer_db_name ="TimerMSKBOstruct";
   /// переменная для отслеживания 
   ///для корректной работы нужно при первом шаге получить данные джойстика и определить его модель
   ou1.initJoi();
   ou1.inDataJoi();
   ou1.updateDataJoi();
   ou1.normalizeJoi();
   ou1.initReady = 1;
   ou1.J_LA["initReady"] = ou1.initReady;
   ou1.timerReady = 0;
   ou1.J_LA["timerReady"] = ou1.timerReady;
   ou1.outDataJoi();
   ou1.printInitJoi();
   ou1.syncStart();

   /// Бесконечный цикл
   while(true){
         ou1.Timerdb.get(ou1.Timerdata);
         ou1.tick =ou1.Timerdata["count"];

         //std::cout << ou1.tick << std::endl;

         //INPUTdb.get(ou1.Jmskbo);
         //if((int)(ou1.prevTick / 10) != (ou1.tick / 10)){
         ou1.inDataJoi();
         ou1.updateDataJoi();
         ou1.normalizeJoi();
         ou1.outDataJoi();
         //ou1.printJoi();
         //}
         ou1.prevTick = ou1.tick;
         sleep(0.02);
   }
///никогда не выполняется
return 0;
}