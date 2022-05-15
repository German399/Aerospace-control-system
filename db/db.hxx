#if !defined(DB_HH)
#define DB_HH
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <nlohmann/json.hpp>
#include <string.h>
#include <hiredis/hiredis.h>
/*! \enum bindmode db.hxx "db/db.hxx"
 *  \brief Определяет режим работы с базой данных. Это необходимо для 
 */
enum bindmode
{
    db_mskbo_get,
    db_mskbo_set,
    db_mskbo_get_set,
    db_test_local_get,
    db_test_local_set,
    db_test_local_get_set,
    db_test_get,
    db_test_set,
    db_test_get_set
};

enum autoTypeMSKBO
{
    t_double,
    t_int,
    t_str,
    t_bool,
    t_null,
    t_json
};

class DB///объект для доступа к базе данных с использованием базы данных redis. Предоставляет различным объектам доступ к базе данных. Имеет элементы
///искуственного интеллекта для запросов по группам ключей, автопределения типов данных и контроля типов допустимых запросов для обычных запросов get и set
{
using json = nlohmann::json;
private:
//конфигурационные переменные 
//

bindmode mode;
std::string db_hostname;
std::string bindNameJSONkey;
json jsonData;
json   logDB;
std::string pwd="MSKBO_DB";
//logAllKeys data structs
std::vector<std::string> keys;
std::vector<enum autoTypeMSKBO> keys_type;
//jsondata

//redis consts
    unsigned int j, isunix = 0;
    redisContext *c;
    redisReply *reply;
    //todo .env config
    const char *hostname = "mskbo";
    int port = 49153;
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
bool init();
void init_local();
void init_test ();
public:
void remote_cfg_bind(std::string cfgName);///<данный метод создан для выгрузки конфигурационного файла из базы данных, для удаленного управления конфигурирования моделью.
///<Вызывается перед стартом программы в случае сетецентрической конфигурации 

void bind(bindmode bindmode,std::string bindNameJSONSet,std::string dbAddress="");///<<B>перед работой с базой данных необходимо вызвать этот метод</B>, он конфигурирует объект базы данных, 
///<получая от него адреса, необходимые порты и прочие настройки. Для стенда мскбо есть наборы таких данных по умолчанию. последний аргумент опциональный
void customMSGtoDB();///<метод общего вида для отправки сообщения в БД
void unbind(){redisFree(c);}///<при необходимости, при смене конфигурации или смены имени объекта можно очистить объект БД и заного его инициализоровать посредством bind
bool get(json& FromDBdata);///<ключевой метод работы с объектами. Позволяет <B>получать данные</B> из базы данных. Для синхронности работы, рекомендуется получать формат json
bool set(json& ToDBdata);///<ключевой метод работы с объектами. Позволяет <B>отдавать данные</B> из базы данных. Для синхронности работы, рекомендуется получать формат json
bool setClientNameKey(std::string model_uniqueId);
bool logAllKeys_typesget(std::string keysToLog);///< получение типов данных, посредством их единичного запроса и анализа, формирует массив keys_type с типами данных
json logAllKeys(std::string keysToLog);///<запрос нескольких ключей из базы данных. Перед его вызовом для определения типов данных необходимо вызвать logAllKeys_typesget()
 
};

#endif // DB_HH end