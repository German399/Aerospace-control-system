<H2>Рассмотрим подробно основные программно-технологические решения модульного проекта</H2>

-# Модульный проект на языке C/C++. Пример создания модуля: 
-# Модуль документирования данного проекта, встроенный в систему сборки
Документирование проекта основано на системе контроля документации DoxyGen
-# Модуль сборки на основе Cmake
Использует файл CMakeLists.txt для сборки проекта. Для этого, вызывается скрипт install, содержащий команды языка-оболочки linux bash

~~~~~~~~~~~~~~~{.sh}
#!/bin/sh
#устанавливаем и запускаем
mkdir build_docker
cd build_docker
cmake ../ && make &&./MSKBOexec
~~~~~~~~~~~~~~~
Такая система сборки типовая для систем, написанных на Си/С++ 
-# Модуль визуального динамического управления конфигурацией 
Создаем файл типа pipeline в графическом редакторе, следующий год
-# Автоконфигурируемый модуль для подключения и отладки экспертных систем
Предлагается следующие возможные способы подключения экспертных систем:
    а. Модуль-адаптер. На первом шаге ЭС запрашивает набор доступных данных и выдает в ответ те данные, которые хочет получать. Получает все данные перед шагом визуализации, и паралелльно с ним выполняет вычисления. Адаптер получает данные от ЭС и выводит на МФИ.
    b.Модуль конфигурации моделирования в виртуальной среде
    c. Модуль конфигруации моделей на основе параметров окружения и .env-файлов
Общая схема работы вид взаимодействия моделей с базой данных представлена на рисунке схемы развертования стенда МСКБО:
\image html "deploy.jpg" "Схема развёртывания стенда МСКБО" width=100%
\image rtf "deploy.jpg" "Схема развёртывания стенда МСКБО" width=5cm
\image latex "deploy.jpg" "Схема развёртывания стенда МСКБО" width=5cm 
7. Модуль работы с базой данных
Пишет данные из основной базы redis для постобработки
8. Модуль работы с большими данными и базами знаний
9. Модуль записи данных эксперимента
10. Модуль построения графиков и формирования отчетов
Дашбоард на базе библиотеки dash и языка python
11. Модуль тестирования и верификации на основе автотестов и анализа типового поведения моделирующей системы(наблюдатель?)
12. Единый диспетчер моделирования - интегрирует все системы и их статусы
Алгоритм работы следующий:
    1.1 База данных очищается командой  FLUSHDB
    b. Конфигурация помещается в jenkins
    c. Запускаются экзешники, создаются потоки и группы для работы с ними в виде описания - jenkinsfile
        - создается конфигурационный файл всех потоков, которые работают в приложении
        - инициализируется  поток записи данных mskboLOGexec, он подключается ко всем нижеуказанным потокам в режиме чтения
        - инициализируется  поток визуализации данных mskboWebIUPexec, он подключается ко всем нижеуказанным потокам в режиме чтения
        - mskbo_input и mskbo_input_group получает, хранит и передает данные джойстиков
        - wago_adapter и xoutput записывают данные в поток командой XWRITEGROUP
        - модель совмещенная САУ + ЛА считывает эти данные командой XREADGROUP
        - после вычислений, создается поток и группа la_data la_data_group XWRITEGROUP
        - далее, её обрабатывают прикладные программы: la_data читает vis_adapter
        - vis adapter создает свою группы visualized_data и visualized_data_group
    d. Создание отчета по информации логирующей системы после выполнения эксперимента
    e. Постэкспериментальный анализ данных эксперимента системой искусственного интеллекта
    f. При использовании нескольких эквивалентных моделей в рамках автоматического прогона, после получения данных диспетчер может перезапускать систему
13. Система визуализации всех вышеуказанных модулей как цифрового двойника
Рисует всякие модели, их характеристики и графы их связей для демонстрационных целей