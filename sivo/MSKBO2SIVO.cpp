#include "Network.h"
#include "sivoCameraProtocol.h"
#include "MSKBO2SIVO.h"
WSASession Session;
UDPSocket Socket;
void sendInit()
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
	//43.3860, 39.1915
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}
void send2Sivo()
{
	//std::string data = "hello world";
	char* data = (char*)malloc(sizeof(CDpackIN));
	memcpy(data, (const char*)&CDpackIN, sizeof(CDpackIN));
	//char buffer[100];
	//сделать проверку координат на основе доступных краев карты местности. Получать эти данные из
	//общего файла, создаваемого моделью мира(для возможности смены карты без переписывания кода)
	if (TRUE) {
		for (int i = 0; i < sizeof(CDpackIN); i++)
			printf("%02X", data[i]);
		printf("\n");
		//стандартный адрес/РМИ 192.168.1.21, порт 6100
		Socket.SendTo("192.168.1.21", 6100, data, sizeof(CDpackIN));

		for (int i = 0; i < sizeof(CDpackIN); i++)
			printf("%02X", data[i]);
		printf("\n");
		free(data);
	}
}
int main()
{
	try
	{
		sendInit();
			//Test: отображение полета по кругу - вынести потом в отдельную программу)
			//примем скорость за 100м/с при разбеге(360км/ч), самолет вида кукурузник
			//обновляем с частотой 25Гц, 4метра за обновление 
			//взлет
			int j;
			for (j = 0; j < 200;j++)
			{
				//для теста считаем 1град за 111км, для 4 метров в град это 27750
				//CDpackIN.cam.lat = ((43.4542 + (j*0.002250)) * 0.017453292519943295769236907684886127134428718885417254560);		// Широта			[рад]
				CDpackIN.cam.lat = ((43.4507 - (j * 0.0001050)) * 0.017453292519943295769236907684886127134428718885417254560);		// Широта			[рад]
				//движение по 25 метров  по широте и долготе за шаг - (j * 0.0002250) - (j * 0.0003100)
				CDpackIN.cam.lon = ((39.9585 - (j * 0.0003060)) * 0.017453292519943295769236907684886127134428718885417254560);
				if (j<=100){
				CDpackIN.cam.ht = 15.;		// Высота			[м]
				}
				else {
					CDpackIN.cam.ht = 15. + (j - 100)*5;
				}
				//if (j > 1000) {
				//	CDpackIN.cam.ht = 4000.;//+j*0.4;		//10 м/c скорость набора высоты
				//}
				//сделать наклон камеры с 1000 метров(Для вертикального обзора)
				//CDpackIN.cam.tet = -1.570796326794896619231321691639751442098584699687552910487;
				CDpackIN.cam.tet = 0.;// Угол Tetta	[рад]
				CDpackIN.cam.psi = 1.9;			// Угол Psi  	[рад]
				CDpackIN.cam.gam = 0.;//iii;			// Угол Gamma [рад]
				send2Sivo();
				Sleep(40);//25гц
			}
				//Тест - полет по кругу бесконечный
					
					TcamPos StartFP;//стартовая точка полета после взлета start FlyPoint
					StartFP.lat = CDpackIN.cam.lat;
					StartFP.lon = CDpackIN.cam.lon;
					StartFP.ht = CDpackIN.cam.ht;
					StartFP.tet = CDpackIN.cam.tet;
					StartFP.psi = CDpackIN.cam.psi;
					StartFP.gam = CDpackIN.cam.gam;
					while(TRUE)
					{
						for (int z = 0; z <= 1000; z++) {
							if ((z < 300) && (z >= 0)) {
								CDpackIN.cam.gam = StartFP.gam;
								CDpackIN.cam.psi = CDpackIN.cam.psi - 0.01;
							}
							
							if ((z < 400) && (z >= 300)) {
								
								CDpackIN.cam.tet = CDpackIN.cam.tet + 0.01;
							}
							if ((z < 500) && (z >= 400)) {
								CDpackIN.cam.tet = CDpackIN.cam.tet - 0.01;
							}

							if ((z < 600) && (z >= 500)) {
								CDpackIN.cam.tet = StartFP.tet;
								CDpackIN.cam.gam = CDpackIN.cam.gam + 0.01;
							}
							if ((z < 700) && (z >= 600)) {
								CDpackIN.cam.tet = StartFP.tet;
								CDpackIN.cam.gam = CDpackIN.cam.gam - 0.01;
							}
							if ((z < 750) && (z >= 700)) {
								CDpackIN.cam.tet = StartFP.tet;
								CDpackIN.cam.gam = CDpackIN.cam.gam - 0.01;
								CDpackIN.cam.psi = CDpackIN.cam.psi - 0.01;
							}
							if ((z < 800) && (z >= 750)) {
								CDpackIN.cam.tet = StartFP.tet;
								CDpackIN.cam.gam = CDpackIN.cam.gam + 0.01;
								CDpackIN.cam.psi = CDpackIN.cam.psi + 0.01;
							}
							if ((z < 900) && (z >= 800)) {
								CDpackIN.cam.tet = StartFP.tet;
								CDpackIN.cam.ht = CDpackIN.cam.ht + 10;
		
							}
							if ((z < 1000) && (z >= 900)) {
								CDpackIN.cam.tet = StartFP.tet;
								CDpackIN.cam.ht = CDpackIN.cam.ht - 10;
							
							}
							CDpackIN.cam.lat = StartFP.lat + (z * 0.00001050*0.005);
							CDpackIN.cam.lon = StartFP.lon + (z * 0.00003060*0.005);
							if (z == 1000)
							{
								CDpackIN.cam.lat = StartFP.lat;
								CDpackIN.cam.lon = StartFP.lon;
								CDpackIN.cam.ht = StartFP.ht;
								CDpackIN.cam.tet = StartFP.tet;
								CDpackIN.cam.psi = StartFP.psi;
								CDpackIN.cam.gam = StartFP.gam;
							}


							send2Sivo();
							Sleep(40);//25гц
						}
						}
			
				
			
		
	}
	catch (std::exception & ex)
	{
		std::cout << ex.what();
	}
	char c;
	std::cin >> c;
}