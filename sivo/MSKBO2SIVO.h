#pragma once
struct TcamPos	// sizeof(CameraAbs) == 32
{
	double		lat;		// Широта			[рад]
	double		lon;		// Долгота		[рад]
	float			ht;			// Высота			[м]
	float			tet;		// Угол Tetta	[рад]
	float			psi;		// Угол Psi  	[рад]
	float			gam;		// Угол Gamma [рад]
};
struct MSKBO2SIVO		// структура пакета, передаваемого в визуализацию КД от модели мира
{
	TcamPos		camPos;
} MSKBOcam;

#pragma pack(pop)