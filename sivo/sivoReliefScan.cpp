// sivoReliefScan.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "boost/asio.hpp"
#include "sivoCameraProtocol.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// пакет, передаваемый в визуализацию КД
//
// sizeof(PacketHeader) == 19
	CDpackIN.hdrPack.wSync = 0xCDEF;		// синхрослово = 0xCDEF
	CDpackIN.hdrPack.bProtocolVersion = 0X04;			// версия протокола (0х04)
	CDpackIN.hdrPack.wLength = 19 + 33;		// Длина пакета (общая, включая заголовок)
	CDpackIN.hdrPack.packet_type = 0x03;				// Тип пакета
	CDpackIN.hdrPack.packet_number = 0;//iii;			// Последовательный номер пакета
	CDpackIN.hdrPack.flag = 0;				//  Флаги = 0
	CDpackIN.hdrPack.dwRes = 0;				// резерв, пока не используется = 0
	//
	// sizeof(RecordHeader) == 4
	CDpackIN.hdrRec.wRecordType = 0x01;		// Тип записи
	CDpackIN.hdrRec.wRecordSize = 33;			// Размер данных в записи
	//
	// sizeof(NPR_CameraAbs) == 33
	
	CDpackIN.cam.lat		= 0.6;		// Широта			[рад]
	CDpackIN.cam.lon		=	0.8;		// Долгота		[рад]
	CDpackIN.cam.ht		= 500.;		// Высота			[м]
	CDpackIN.cam.tet		= 0.;			// Угол Tetta	[рад]
	CDpackIN.cam.psi		= 0.;			// Угол Psi  	[рад]
	CDpackIN.cam.gam		= 0.;//iii;			// Угол Gamma [рад]
	
	CDpackIN.cam.flag = 1;			// 1
	//
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//TNetVisCD_In Inbuf[128];
	//auto mutable_buffer = boost::asio::buffer(Inbuf);
	//char* p1 = boost::asio::buffer_cast<char*>(mutable_buffer);
	//const int max_length = 128;

	using boost::asio::ip::udp;
	try
	{
		//if (argc != 3)
		//{
			//std::cerr << "Usage: blocking_udp_echo_client <host> <port>\n";
			//return 1;
		//}

		boost::asio::io_context io_context;

		//udp::socket s(io_context, udp::endpoint(udp::v4(192.168.1.52), 7011));
		boost::asio::io_service io_service;
		udp::resolver resolver(io_context);
		udp::resolver::results_type endpointsSend = resolver.resolve(udp::v4(), "192.168.1.255", "3060");
		udp::socket s(io_service, udp::endpoint(udp::v4(), 3060));
		
		char *buffer = (char*)malloc(sizeof(CDpackIN));
		memcpy(buffer, (const char*)& CDpackIN, sizeof(CDpackIN));
		boost::asio::buffer_cast<char*>(mutable_buffer);

		s.send_to(boost::asio::buffer(buffer, sizeof(buffer)), endpointsSend.begin());
		free(buffer);
		int i;
		for (i = 0; i < sizeof(CDpackIN); i++)
			printf("%02X", buffer[i]);
		printf("\n");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
