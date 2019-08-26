
#pragma once

#ifndef C_CORE_H
#define C_CORE_H

#include <cstdio>

#include "BaseDequeObject.h"	
#include "ThermDeamon.h"
#include "MyUtiles.h"
#include "object.h"

 
class CEngineSingletonMap
{

private:
	CEngineSingletonMap() {
	}

	~CEngineSingletonMap() {}
	CEngineSingletonMap(CEngineSingletonMap const&) = delete;
	CEngineSingletonMap& operator= (CEngineSingletonMap const&) = delete;

public:

	static CEngineSingletonMap& Instance()
	{
		// согласно стандарту, этот код ленивый и потокобезопасный
		static CEngineSingletonMap s;
		return s;
	}

	void Public_Get_Next_Therm_Baloon(
		/* x */ float* A1,
		/* y */ float* A2,
		/* z */ float* A3,
		/* Hight */ float* A4,
		/* Radius */ float* A5)
	{
		printf("[CEngineSingletonMap::Public_Get_Next_Therm_Baloon] : THIS_PTR %x \n", this);

		_ThermDeamon.GetNextThermBoolon(A1, A2, A3, A4, A5);
	}

	void DbgPrint()
	{
		printf("[CEngineSingletonMap::DbgPrint] : THIS_PTR %x \n", this);
	}

	void Public_Set_Object_Pos(
		/* x */IN float* A1,
		/* y */IN float* A2,
		/* z */IN float* A3,
		/* Design */OUT float* A4
	)
	{
		printf("[CEngineSingletonMap::Public_Set_Object_Pos] : THIS_PTR %x \n", this);

		_LastObjectPos.Set(A1, A2, A3);

		_ThermDeamon.Is_Self_Pos_In_Thermik(_LastObjectPos, A4);
	}


	void Public_Get_Object_Pos(
		/* x */IN float* A1,
		/* y */IN float* A2,
		/* z */IN float* A3,
		/* Design */OUT float* A4
	)
	{
		printf("[CEngineSingletonMap::Public_Get_Object_Pos] : THIS_PTR %x \n", this);
		_LastObjectPos.Get(A1, A2, A3);
	}

	bool IsNotCloseDLL() const
	{
		return _bIsExitApp;
	}


	void  Exit_DLL()
	{
		_bIsExitApp = true;
	}


	void IsFirstStartCreateINI()
	{
		CThermikINI Threshold("ThermDLL.ini");
	}

private:
	CThermDeamon _ThermDeamon;
	CObject		 _LastObjectPos;
	bool		 _bIsExitApp = false;
};

#endif  






