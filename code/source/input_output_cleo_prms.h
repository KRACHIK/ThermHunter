#ifndef C_INPUT_OUTPUT_CLEO_PRMS_H
#define C_INPUT_OUTPUT_CLEO_PRMS_H


#include <memory.h>
#include <thread>
#include "def.h"
 

void Init_UDP_Client();


extern "C" __declspec(dllexport) void  Public_Exit_DLL();  

extern "C" __declspec(dllexport) void Init_Client_backgraund_Thr(); // CALL :A007 
 
extern "C" __declspec(dllexport) void DLL_PLUS(); // CALL :A007 
  
extern "C" __declspec(dllexport) void Public_Get_Next_Therm_Baloon(
	/* x */ float* A1,
	/* y */ float* A2,
	/* z */ float* A3,
	/* Hight */ float* A4,
	/* Radius */ float* A5
);
  
extern "C" __declspec(dllexport) void Publicl_Is_Self_Pos_In_Thermik(
	/* x */IN float* A1,
	/* y */IN float* A2,
	/* z */IN float* A3,
	/* Design */OUT float* A4 
);


 
#endif  
