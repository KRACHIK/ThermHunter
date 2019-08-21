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






#if 0
extern "C" __declspec(dllexport) void Public_InPutDimByCLEO(
	float* A1,
	int iPrms1, int iPrms2,
	float* A2, float* A3, float* A4, float* A5, float* A6, float* A7, float* A8, float* A9, float* A10)
{
}

extern "C" __declspec(dllexport) void Public_OUTPUT_DimByCLEO(
	float* A1, float* A2, float* A3, float* A4, float* A5,
	float* A6, float* A7, float* A8, float* A9, float* A10)
{
	// read stack Box package
	*A1 = 0; *A2 = 0; *A3 = 0; *A4 = 0; *A5 = 0;
	*A6 = 0; *A7 = 0; *A8 = 0; *A9 = 0; *A10 = 0;


	Log(" ");
	Log("[extern void Public_OUTPUT_DimByCLEO] 1=%f", *A1);
	Log("[extern void Public_OUTPUT_DimByCLEO] 2=%f", *A2);
	Log("[extern void Public_OUTPUT_DimByCLEO] 3=%f", *A3);
	Log("[extern void Public_OUTPUT_DimByCLEO] 4=%f", *A4);
	Log("[extern void Public_OUTPUT_DimByCLEO] 5=%f", *A5);
	Log("[extern void Public_OUTPUT_DimByCLEO] 6=%f", *A6);
	Log("[extern void Public_OUTPUT_DimByCLEO] 7=%f", *A7);
	Log("[extern void Public_OUTPUT_DimByCLEO] 8=%f", *A8);
	Log("[extern void Public_OUTPUT_DimByCLEO] 9=%f", *A9);
	Log("[extern void Public_OUTPUT_DimByCLEO] 10=%f", *A10);
}

#endif  










