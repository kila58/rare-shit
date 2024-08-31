#include "AntiLeak.h"
#include "crc32.h"

bool cAL::Verified()
{
	//DONT TOUCH THIS!
	DWORD nSize; DWORD nSize2; int nSize3; DWORD lVolSerialNbr = 0;
	char cUsername[255] = ""; char cComputername[255] = ""; char cComputerhost[255] = ""; char sHDSerial[255] = "";
	nSize = sizeof(cUsername); nSize2 = sizeof(cComputername); nSize3 = sizeof(cComputerhost);

	GetUserName(cUsername, &nSize);
	GetComputerName(cComputername, &nSize2);

	GetVolumeInformation("C:\\", 0, 0, &lVolSerialNbr, 0, 0, 0, 0);
	ultoa(lVolSerialNbr, sHDSerial, 10);


	DWORD crcComputerName = gCRC.crc32(cComputername);
	DWORD crcUserName = gCRC.crc32(cUsername);
	DWORD crcHDSer = gCRC.crc32(sHDSerial);
	DWORD HardWareID = crcComputerName + crcUserName + crcHDSer;


#define AddUser( HWID , Name )									\
	if (HardWareID == HWID)										\
	{															\
	return true;												\
	}

	//-------------------------
	//ADD HWIDS BELOW THIS LINE

	AddUser(1533875218, Kelse);
	AddUser(2091501520, CaptainJuanBlackmore)
	AddUser(63525992, Frost)
	AddUser(4010010290, Rionxe)
	AddUser(3576469471, Atomic)
	AddUser(393126059, Drayk)

		//AddUser( PUT HWID HERE, PUT ALIAS/NAME HERE );


		return false;
}