#include <windows.h>
#include <fstream>

#include "input_output_cleo_prms.h"
#include "MyUtiles.h"
#include "core.h"

#include <chrono>
#include <thread>

//static std::shared_ptr<GameCore> glMyCLEO_Core;

void Init_UDP_Client()
{
	Log("[void Init_UDP_Client] :");

	CEngineSingletonMap::Instance().DbgPrint();

	Beep(1000, 1000);
	// for glMyCLEO_Core not deatch
	while (CEngineSingletonMap::Instance().IsNotCloseDLL())
	{
		Log("[void Init_UDP_Client] : [while]  ");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	}
}
 
extern "C" __declspec(dllexport) void  Public_Exit_DLL()
{
	Log("[Public_Exit_DLL] : ");
	CEngineSingletonMap::Instance().Exit_DLL();
}
  
extern "C" __declspec(dllexport) void DLL_PLUS()   // CALL :A007 
{
	CEngineSingletonMap::Instance().DbgPrint();

	Log("[DLL_PLUS] : ");
}


extern "C" __declspec(dllexport) void Init_Client_backgraund_Thr() // Sanny Builder CALL :A007
{
	Log("[void Init_Client_backgraund_Thr]");

	CEngineSingletonMap &glMyCLEO_Core = CEngineSingletonMap::Instance();
	glMyCLEO_Core.DbgPrint();

	glMyCLEO_Core.IsFirstStartCreateINI();
	 
	std::thread t1(Init_UDP_Client);
	t1.detach();
}


extern "C" __declspec(dllexport) void Public_Get_Next_Therm_Baloon(
	/* x */ float* A1,
	/* y */ float* A2,
	/* z */ float* A3,
	/* Hight */ float* A4,
	/* Radius */ float* A5
)
{
	Log("[void Public_Get_Next_Therm_Baloon] %f %f %f %f %f",
		*A1,
		*A2,
		*A3,
		*A4,
		*A5
		);
	  
	CEngineSingletonMap &glMyCLEO_Core = CEngineSingletonMap::Instance();
	glMyCLEO_Core.Public_Get_Next_Therm_Baloon(
		A1,
		A2,
		A3,
		A4,
		A5
	);
}


extern "C" __declspec(dllexport) void Publicl_Is_Self_Pos_In_Thermik(
	/* x */IN float* A1,
	/* y */IN float* A2,
	/* z */IN float* A3,
	/* Design */OUT float* A4
)
{ 
	Log("[Publicl_Is_Self_Pos_In_Thermik] : %f %f %F %f"
		,*A1
		,*A2
		,*A3
		,*A4
		);

	CEngineSingletonMap &glMyCLEO_Core = CEngineSingletonMap::Instance();

	glMyCLEO_Core.Public_Set_Object_Pos(A1, A2, A3, A4);
}

 









