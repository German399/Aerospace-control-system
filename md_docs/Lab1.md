<H2>Лабораторная 1. Программирование: Написание простого программного модуля для стенда МСКБО</H2>
Предлагается написать модуль на языке Python.
Подключается библиотека для работы с базой данных redis и используется для обмена формат данных JSON. Соотвественно, данная програма считывает данные от базы данных и записывает их в файл. После этого, она создает тестовые ответные данные по высоте и типу летательного аппарата, которые отправляет в отдельное поле базы данных model_reply.
~~~~~~~~~~~~~~~{.py}
import json
import redis
r = redis.StrictRedis(host='127.0.0.1', port=6379, db=1)
with open('LA.json') as data_file:
    test_data = json.load(data_file)
#здесь нужно добавить функцию, создающую тестовые ответные данные по высоте и типу летательного аппарата
r.set('model_reply', test_data)
~~~~~~~~~~~~~~~
Такая программа иллюстрируют простейший способ интеграции в информационно-управляющих контур стенда. 
Практическое задание - написать функциональную программу.
Для этого, нужно предпринять следующие шаги:
1. создать программу папку test и в ней файл с именем test_mskbo.py;
2. Вписать в неё вышеуказанный фрагмент кода;
3. Сохранить программу;
4. Создать в папке с этой программой git репозиторий командой git init;
5. Добавить свою программу в систему контроля кода МСКБО, создав в ней отдельный репозиторий;
6. После загрузки программы добавить специальный файл(jenkinsfile) конфигурации для удаленной сборки и выполения программы;
7. Показать результаты работы преподавателю.