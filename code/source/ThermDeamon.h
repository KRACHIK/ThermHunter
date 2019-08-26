
#pragma once

#ifndef C_THERM_DEAMON_H
#define C_THERM_DEAMON_H

#include <memory.h>

#include "object.h"				
#include "MyUtiles.h"			 
#include "BaseDequeObject.h" 	 

class CDebugCreateTEstTherm
{

public:
	static int GetCountBallon();  // from iniFile 
	static CDequeObjectContainer<CThermBaloon> GetTherm(); 
};


class CThermDeamon
{
public:
	CThermDeamon()
	{
		_Therm = CDebugCreateTEstTherm::GetTherm();
	}

	/*for render */
	void GetNextThermBoolon(float* A1, float* A2, float* A3, float* A4, float* A5)
	{
		CThermBaloon object = _Therm.GetNextObject();
		object.InitForCleo(A1, A2, A3, A4, A5);
	}

	/**
	* IsSelfPosInThermik
	* Клео скрипт передаст в dll корды хз кокого объекта
	* а этот метод скажет попали ли мы в термик
	*/
	void Is_Self_Pos_In_Thermik(const CObject ActorPos, OUT float *Design); 

private:

	bool _IsSelfPosInThermik(const CThermBaloon & ThermBaloon, const CPoint3D ActorPos
		, const std::string DbgMsg); 

private:
	CDequeObjectContainer<CThermBaloon> _Therm;
};


#endif  






