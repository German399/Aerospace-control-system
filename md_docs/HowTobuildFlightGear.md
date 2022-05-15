Нужно скачать скрипт download_and_compile.sh из https://sourceforge.net/p/flightgear/fgmeta/ci/master/tree/download_and_compile.sh,
создать папку fg в домашней директории, скрипт download_and_compile.sh разместить в папке ~/fg.
 ./download_and_compile.sh --lts
 Скрипт сначала ставит библиотеки для сборки, потом долго качает разные компоненты FlightGear. Рельеф FlightGear подгружает в рантайме.
 В папке fg_vis пример программы работы с flightgear как с визуализацией