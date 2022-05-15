typedef uint8_t BYTE;
typedef unsigned short WORD;
typedef uint32_t DWORD;
typedef unsigned char UCHAR;
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#pragma pack(push, 1)

struct PacketHeader					// sizeof(PacketHeader) == 19
{
	WORD	 wSync;							// ����������� = 0xCDEF
	BYTE	 bProtocolVersion;	// ������ ��������� (0�04)
	WORD	 wLength;						// ����� ������ (�����, ������� ���������)
	WORD	 packet_type;				// ��� ������
	DWORD	 packet_number;			// ���������������� ����� ������
	DWORD	 flag;						  //  ����� = 0
	DWORD	 dwRes;							// ������, ���� �� ������������ = 0
};
struct RecordHeader			// sizeof(RecordHeader) == 4
{
	WORD	wRecordType;		// ��� ������
	WORD	wRecordSize;		// ������ ������ � ������
};

struct NPR_CameraAbs			// sizeof(CameraAbs) == 33
{
	double		lat;		// ������			[���]
	double		lon;		// �������		[���]
	float			ht;			// ������			[�]
	float			tet;		// ���� Tetta	[���]
	float			psi;		// ���� Psi  	[���]
	float			gam;		// ���� Gamma [���]
	UCHAR			flag;		// 1
};
struct TNetVisCD_In			// ��������� ������, ������������� � ������������ ��
{
	PacketHeader		hdrPack;
	RecordHeader		hdrRec;
	NPR_CameraAbs		cam;
} CDpackIN;

#pragma pack(pop)