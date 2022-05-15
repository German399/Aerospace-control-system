#pragma once
struct TcamPos	// sizeof(CameraAbs) == 32
{
	double		lat;		// ������			[���]
	double		lon;		// �������		[���]
	float			ht;			// ������			[�]
	float			tet;		// ���� Tetta	[���]
	float			psi;		// ���� Psi  	[���]
	float			gam;		// ���� Gamma [���]
};
struct MSKBO2SIVO		// ��������� ������, ������������� � ������������ �� �� ������ ����
{
	TcamPos		camPos;
} MSKBOcam;

#pragma pack(pop)