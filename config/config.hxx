#include <string>
using namespace std;
class CFG
{
private:
string MODEL_LA_NAME;
public:
bool bind(string cfgName);///<использование локального конфигурационного файла для инициализации программы. Гибкий способ конфигурации для группового моделирования
///возращает переменную с нужным ключом из конфигурационного файла
string get(string cfgKey);
///изменяет в текущей конфигурации один из ключей
bool set(string cfgKey);
};