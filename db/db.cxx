#include "db.hxx"
#include <sstream>
#include <vector>
#include <iterator>
#include <boost/lexical_cast.hpp>
#include <cstdlib>
using json = nlohmann::json;
void DB::bind(bindmode bindmode,std::string bindNameJSONSet,std::string dbAddress){//функция принимает в качестве аргументов режим работы программы с базой данных, имя структуры данных в БД
mode = bindmode;
bindNameJSONkey = bindNameJSONSet;
if(dbAddress!=""){db_hostname = dbAddress;}
switch (bindmode)
    {
    case db_mskbo_get://init exchange
        init();
        //get some config
        
        //make bind with db
        break;
    case db_mskbo_set:
        init();
        /* code */
        //make bind with db
        break;
    case db_mskbo_get_set:
    init();
        /* code */
        //make bind with db
        break;
    case db_test_local_get:
        init_local();
        /* code */
        //make bind with db
        break;
    case db_test_local_set:
        init_local();
        /* code */
        //make bind with db
        break;
    case db_test_local_get_set:
        init_local();
        /* code */
        //make bind with db
        break;
    case db_test_get:
        //db_test_get bindName
        init_test();
        /* code */
        //make bind with db
        break;
    case db_test_set:
        init_test();
        /* code */
        //make bind with db
        break;
    case db_test_get_set:
        //db_test_get bindName
        init_test();
        /* code */
        //make bind with db
        break;
    default:
        std::cout << "неправильно объявлены имена для подключения к источникам данных"<<std::endl;
        break;
    }
 
}
bool DB::init(){//обращается к БД МСКБО
    //joyData init
    if (isunix) {
        c = redisConnectUnixWithTimeout(hostname, timeout);
    } else {
        c = redisConnectWithTimeout(hostname, port, timeout);
    }
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection to DB error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection to DB error: can't allocate redis context\n");
        }
        std::cout<<"Нет подключения к базе данных, невозможно подключить джойстики, подключитесь к сети МСКБО для корректной работы программы и перезапустите её"<<std::endl;
        return false;
    }
    //setClientNameKey(bindNameJSONkey);
    return true;
    //do AUTH
    //std::string getInquiry ="AUTH "+pwd;
    //    reply = (redisReply *)redisCommand(c,getInquiry.c_str());
    
    //std::cout<< std::setw(4) << J_LA << std::endl;
    
     
    //std::cout <<J_mskbo[i]["Name"]<<" "<<J_mskbo[i]["Value"]<<" "<<J_mskbo[i]["Offset"] <<'\n';
    //printf("GET json_adapter_joustic: %s\n", reply->str);
    //LAinit
    
    //std::ifstream i("LAtest.json");
    //std::stringstream LA1ss;
    //LA1ss << i.rdbuf();
    //LAstr = LA1ss.str();
    //i.close();

        //
    
}
void DB::init_test(){
//test ip and hostname. Make configurable
hostname = "mskbo";
port = 49153;
init();
}
void DB::init_local(){
hostname = "127.0.0.1";
port = 6379;
init();

}
bool DB::get(json& FromDBdata){
    if ((db_mskbo_get==mode)||(db_mskbo_get_set==mode)||(db_test_local_get)||(db_test_local_get_set==mode)||(db_test_get==mode)||(db_test_get_set==mode)){
        std::string DBstr;
        std::string getInquiry ="GET "+bindNameJSONkey;
        reply = (redisReply *)redisCommand(c,getInquiry.c_str());
        //если у нас есть данные, записываем их в JSON структуру
            if (reply != NULL){
            FromDBdata = json::parse(reply->str);
            freeReplyObject(reply);
            return true;
                // if (json::accept(DBstr))
                //     {
                //         DBstr = json::parse(DBstr);
                //         return true;    
                //     }
                // else
                //     {
                //     std::cout<<"объект с ключом:"<<bindNameJSONkey<<" Содержимое:"<<DBstr<< 
                //     "по запросу get не является объектом json и не может быть корректно записан в базу данных"<<std::endl;
                //     return false;
                //     }

                
            }
    } 
    else
        {
        std::cerr<<"программа не может выполнить запрос get к базе данных из-за неизвестного режима bindmode в процедуре с ключом"<<bindNameJSONkey<<std::endl;
        return false;
        }
        std::cerr<<"ошибка процедуры get неизвестный bindmode"<<" в процедуре с ключом"<<bindNameJSONkey<<std::endl;
        return false;
}
bool DB::set(json& FromDBdata){
    if ((db_mskbo_set==mode)||(db_mskbo_get_set==mode)||(db_test_local_set)||(db_test_local_get_set==mode)||(db_test_set==mode)||(db_test_get_set==mode))
    {
    std::string setstr="SET "+bindNameJSONkey+" "+FromDBdata.dump();
    reply = (redisReply *)redisCommand(c,setstr.c_str());
    //если у нас есть данные, записываем их в JSON структуру
        if (reply != NULL){
        //FromDBdata = json::parse(reply->str);
        freeReplyObject(reply);return true;
        }
        else{return false;}
    } else 
    {std::cout<<"программа не может выполнить запрос set к базе данных из-за режима bindmode в процедуре с ключом"<<bindNameJSONkey<<std::endl;return false;
    }

}
bool DB::setClientNameKey(std::string model_uniqueId){
///использовать после иницилизации bind. Позволяет базе данных получить имя моделируемого объекта без необходимости отдельно обрабатывать 
std::string setstr="CLIENT SETNAME "+model_uniqueId;
reply = (redisReply *)redisCommand(c,setstr.c_str());
setstr="CLIENT GETNAME";
reply = (redisReply *)redisCommand(c,setstr.c_str());
if(reply != NULL){
    freeReplyObject(reply);
    return true;
}
else
    {return false;}
}


bool DB::logAllKeys_typesget(std::string keysToLog){
       ///извлекаем из строки все ключи для записи

        {
             std::istringstream s ( keysToLog);
             keys.insert(keys.end(), 
                 std::istream_iterator<std::string>(s),  
                 std::istream_iterator<std::string>());
        }
    
        //std::string redis_json_log="MGET "+keysToLog; 
        

        

     /*
         
         #include <string>

        std::string str;

        try {
            int i = boost::lexical_cast<int>( str.c_str());
            float f = boost::lexical_cast<int>( str.c_str());
            double d = boost::lexical_cast<int>( str.c_str());
            } catch( boost::bad_lexical_cast const& ) {
                // Error management
        }
     */
    //keys init
    // for (j = 0; keys.; j++) {
    // std::cout<<j<<std::endl;     
    // };
        for(int j = 0; j < keys.size(); j++)
        {
        keys_type.push_back(t_str);}
         int j = 0;
         for(auto it = std::begin(keys); it != std::end(keys); ++it) {
         
        
             
         
         std::string key ="GET "+*it;
         reply = (redisReply *)redisCommand(c,key.c_str());
            if(reply != NULL){
                    std::string str = reply->str;
                    std::cout << str << "\n";
                    try{
                        double d = boost::lexical_cast<double>(str);
                        std::cout<<"double int=" << d << "\n";
                        keys_type[j]=t_double;
                    }
                    catch(boost::bad_lexical_cast const&){};
                    try{
                        int i = boost::lexical_cast<int>(str);
                        std::cout<<"casted int=" << i << "\n";
                        keys_type[j]=t_int;
                    }
                    catch(boost::bad_lexical_cast const&){};
                    try{    bool temp;
                            if ((str=="true")||(str=="false")||(str=="TRUE")||(str=="FALSE")){
                            if ((str=="true")||(str=="TRUE")){temp = true;}
                            else {temp = false;};
                            std::cout<<"casted bool=" << temp << "\n";
                            keys_type[j]=t_bool;
                        }
                    }
                    catch(boost::bad_lexical_cast const&){};
                    try{
                        if(keys_type[j]==t_str){
                        std::cout<<"string for json accept check=" << str << "\n";
                        json::parse(str);
                        keys_type[j] = t_json;
                        }
                    }
                    catch(json::exception& e){
                        std::cout<<"err="<<e.what()<<std::endl;
                    };
                    //float f = boost::lexical_cast<int>(reply->str);

                    //if(reply->element[j]->str)
                    //if(json::accept(reply->element[j]->str))
                    //std::string redis_type="type "+*it ; 
                    //std::cout << redis_type << "\n";
                    //reply = (redisReply *)redisCommand(c,redis_type.c_str());
                   
                    
                    
                    }
            j++;
                  
             
         }
           for (int i = 0; i < keys_type.size(); i++)
                    {
                        std::cout << keys_type[i] << " "; 
                    }  
     
     return true;
    //return false;    
     
       
        
///проверяем все типы значений в базе данных
///итератор по вектору
/* for(auto it = std::begin(keys); it != std::end(keys); ++it) {
     try{
         std::string redis_type="type "+*it ; 
         std::cout << redis_type << "\n";
         reply = (redisReply *)redisCommand(c,redis_type.c_str());
    std::cout << reply->str << "\n";
     }
     catch(){
    return false;    
     } */
    
     
    
    
 
    

 //после, из строк определить джсоны
}


json DB::logAllKeys(std::string keysToLog){
    //TODO take keys from config
 logDB.clear();
    

 std::string redis_json_log="MGET "+keysToLog; 
 reply = (redisReply *)redisCommand(c,redis_json_log.c_str());

 std::cout<<"mget=" << redis_json_log.c_str()<<std::endl;
  if(reply != NULL){
//     for()
//       std::cout<<"reply:"<< reply->element[0]->str;
//       std::cout<<"reply:"<< reply->element[1]->str;
json temp;
for (j = 0; j < reply->elements; j++) {
    switch (keys_type[j])
    {
    ///в данной функции можно обрабатывать объекты специальным образом
    /* пример упаковки определенной переменной в определенную часть структуры
    case t_double:
    if(key[j]=="X"){logDB[joi]["X"]=reply->element[j]->str}
    break; */
    case t_double:
    temp[keys[j]]= boost::lexical_cast<double>(reply->element[j]->str);
    break;  
    case t_int:
    temp[keys[j]]= boost::lexical_cast<int>(reply->element[j]->str);
    break; 
     case t_bool:
     temp[keys[j]]= (bool)(reply->element[j]->str);
     break;
     //case t_null:
           //reply->type
    case t_json:
    
    temp = json::parse(reply->element[j]->str);
    //else{
    //    temp = keys[j]+ " " + (reply->element[j]->str);
    
        /* code */
        break;

    default:
       //std::cout<<"Тип элемента"<<keys_type[j] <<"не обработан в функции logAllKeys" <<std::endl;
       //std::string str ="{\""+keys[j]+ "\":" + (reply->element[j]->str)+"}";
       if(reply->element[j]->str!=nullptr){
       temp[keys[j]]= reply->element[j]->str;
       }else{ std::cout<<"reply for key "<<keys[j]<< " is NULL"<<std::endl;}
        break;
    }

    std::cout<<"key="<<keys[j]<<"reply:"<<j<<""<< reply->element[j]->str<<std::endl;
    std::cout<<"temp parsed:"<<temp<<std::endl;
    if((temp!="")||(temp!=" "))
    {logDB.update(temp);}
    temp.clear();

}

     //
    freeReplyObject(reply);
    return logDB;
}
  else 
    {return NULL;}
}

void customMSGtoDB(){

}