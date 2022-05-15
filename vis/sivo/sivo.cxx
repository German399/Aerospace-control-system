#include <unistd.h>
#include <nlohmann/json.hpp>
#include "sivoCameraProtocol.h"
#include "udp.hxx"
using json = nlohmann::json;
void testSivo(const char *Sivo_address,int port)
{
	//Сделать ip конфигурируемыми через конфигурационный файл
	//while (TRUE) {
		//в первой версии - прием позиции камеры
		//почитать дополнительно документацию константы дизайн и посмотреть
		//можно ли несколько объектов визуализировать(как у сухомлинова)
		//если можно, добавить запросы к визуализации для выставления дополнительных обьектов, написать обработчик
		//
		//Socket.RecvFrom(buffer, 100);
		//Socket.RecvFrom("");
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// пакет, передаваемый в визуализацию КД
//
// sizeof(PacketHeader) == 19
	CDpackIN.hdrPack.wSync = 0xCDEF;		// синхрослово = 0xCDEF
	CDpackIN.hdrPack.bProtocolVersion = 0X04;			// версия протокола (0х04)
	CDpackIN.hdrPack.wLength = 19 + 33;		// Длина пакета (общая, включая заголовок)
	CDpackIN.hdrPack.packet_type = 0x03;				// Тип пакета
	CDpackIN.hdrPack.packet_number = 1;//iii;			// Последовательный номер пакета
	CDpackIN.hdrPack.flag = 0;				//  Флаги = 0
	CDpackIN.hdrPack.dwRes = 0;				// резерв, пока не используется = 0
	//
	// sizeof(RecordHeader) == 4
	CDpackIN.hdrRec.wRecordType = 0x01;		// Тип записи
	CDpackIN.hdrRec.wRecordSize = 33;			// Размер данных в записи
	//
	// sizeof(NPR_CameraAbs) == 33
	//перевод в градусов в радианы осуществляется с использованием(pi/180) 0.017453292519943295769236907684886127134428718885417254560
	//ЦКР по умолчанию - карта сочи образца 2015 года(до олимпиады, без олимпийский объектов)
	//ключевые точки ЦКР: 43.4500, 39.9600, 30 - обзорная точка на берег
	//аэропорт адлер полоса:с43 27' 15.23" в39 57' 34.54" высота 28м, курс 210 ->43.4542N 39.9596E(малая)
	// 24 полоса в сторону моря(основная точка старта)43.4507 39.9585
	//левая нижняя точка границы 43.3333, 40.0000
	//левая нижняя граница суши 43.3860, 40.0000
	//правая точка граница суши и карты 
	//левая верхняя граница суши 44.0000, 39.1915
	//правая верхняя граница суши 44.0000, 40.0000
	//максимально возможная высота камеры превышает возможный порог ЛА, суша видна до пороговой высоты 40000м, 35000м рельеф различим
	//tet -1.570796326794896619231321691639751442098584699687552910487 gam 0
	//значения по умолчанию
	CDpackIN.cam.lat = 43.4500 * 0.017453292519943295769236907684886127134428718885417254560;		// Широта			[рад]
	CDpackIN.cam.lon = 39.9600 * 0.017453292519943295769236907684886127134428718885417254560;		// Долгота		[рад]
	CDpackIN.cam.ht = 30.;		// Высота			[м]
	CDpackIN.cam.tet = -1.570796326794896619231321691639751442098584699687552910487;			// Угол Tetta	[рад]
	CDpackIN.cam.psi = 0.;			// Угол Psi  	[рад]
	CDpackIN.cam.gam = 0.;//iii;			// Угол Gamma [рад]
	CDpackIN.cam.flag = 1;			// 1
	char *buffer= (char*)malloc(sizeof(CDpackIN));
	memcpy(buffer,(const char*)&CDpackIN,sizeof(CDpackIN));
	udpSend(buffer,sizeof(CDpackIN),Sivo_address,port);
	free(buffer);
	//43.3860, 39.1915
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}
void send2Sivo(json& LAdata,const char *Sivo_address,int port)
{
	CDpackIN.hdrPack.wSync = 0xCDEF;		// синхрослово = 0xCDEF
	CDpackIN.hdrPack.bProtocolVersion = 0X04;			// версия протокола (0х04)
	CDpackIN.hdrPack.wLength = 19 + 33;		// Длина пакета (общая, включая заголовок)
	CDpackIN.hdrPack.packet_type = 0x03;				// Тип пакета
	CDpackIN.hdrPack.packet_number = 1;//iii;			// Последовательный номер пакета
	CDpackIN.hdrPack.flag = 0;				//  Флаги = 0
	CDpackIN.hdrPack.dwRes = 0;				// резерв, пока не используется = 0

	CDpackIN.hdrRec.wRecordType = 0x01;		// Тип записи
	CDpackIN.hdrRec.wRecordSize = 33;			// Размер данных в записи

	CDpackIN.cam.lat = LAdata["lat"].get_ref<json::number_float_t&>();
    //* 0.017453292519943295769236907684886127134428718885417254560;		// Широта			[рад]
	CDpackIN.cam.lon = LAdata["lon"].get_ref<json::number_float_t&>();
    //* 0.017453292519943295769236907684886127134428718885417254560;		// Долгота		[рад]
	CDpackIN.cam.ht = LAdata["H"].get_ref<json::number_float_t&>();		// Высота			[м]
	CDpackIN.cam.tet = LAdata["tet"].get_ref<json::number_float_t&>();			// Угол Tetta	[рад]
	CDpackIN.cam.psi = LAdata["psi"].get_ref<json::number_float_t&>();			// Угол Psi  	[рад]
	CDpackIN.cam.gam = LAdata["gam"].get_ref<json::number_float_t&>();//iii;			// Угол Gamma [рад]
	CDpackIN.cam.flag = 1;			// 1
    //std::cout << CDpackIN.cam.tet<< std::endl;

    char *buffer= (char*)malloc(sizeof(CDpackIN));

	memcpy(buffer,(const char*)&CDpackIN,sizeof(CDpackIN));

    //char* data = (char*)malloc(sizeof(CDpackIN));
	//memcpy(data, (const char*)&CDpackIN, sizeof(data));
    udpSend(buffer,sizeof(CDpackIN),Sivo_address,port);
    free(buffer);
    

}
