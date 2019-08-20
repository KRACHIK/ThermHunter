
#pragma once

#ifndef C_THERM_DEAMON_H
#define C_THERM_DEAMON_H

#include <memory.h>

#include "def.h"				// base class
#include "MyUtiles.h"			// log
#include "BaseDequeObject.h" 	// my container

class CDebugCreateTEstTherm
{

public:
	static CDequeObjectContainer<CThermBaloon> GetTherm()
	{
		CDequeObjectContainer<CThermBaloon> _Therm;

		CPoint3D CurPos(0.0, 0.0, 0.0);
		float	 fRadius = 20.0f;
		float	 fHight = 10.0f;
		int		 Count = 51;

		CThermBaloon StartBaloon(
			/* Spawn*/ CPoint3D(1.0, 2.0, 3.0)
			, CurPos
			, fRadius
			, fHight
			/*temperature*/, 37.0f
		);

		float  X_Offset = 4 * fRadius + 3.0f;
		float  Y_Offset = fRadius + 3.0f;

		for (int i = 0; i < Count; i++)
		{
			CurPos.AddOffset(X_Offset, Y_Offset, fHight);
			StartBaloon.SetCurPos(CurPos);
			_Therm.Push_back(StartBaloon);
		}

		return _Therm;
	}
};


class CThermDeamon
{
public:
	CThermDeamon()
	{
		_Therm = CDebugCreateTEstTherm::GetTherm();
	}


#if 0
	static void GetNextThermBoolon(
		/* x */ float* A1,
		/* y */ float* A2,
		/* z */ float* A3,
		/* Hight */ float* A4,
		/* Radius */ float* A5)
	{
		CThermBaloon Tmp(
			CPoint3D(1.0, 2.0, 3.0)
			, CPoint3D(3.0, 4.0, 5.0)
			, 10.0f
			, 39.0f
		);

		Tmp.InitForCleo(A1, A2, A3, A4, A5);
	}
#endif

	void GetNextThermBoolon(float* A1, float* A2, float* A3, float* A4, float* A5)
	{
		CThermBaloon object = _Therm.GetNextObject();
		object.InitForCleo(A1, A2, A3, A4, A5);
		object.DebugPrint();
	}

	void Is_Self_Pos_In_Thermik(const CObject ActorPos, OUT float *Design)
	{
		for (size_t i = 0; i < _Therm.Size(); i++)
		{
			if (_IsSelfPosInThermik(_Therm.GetObjectIndex(i), ActorPos.GetPos()))
				*Design = 1.0f;

			*Design = 0.0f;
		}
	}



private:

	/**
	* IsSelfPosInThermik
	* Клео скрипт передаст в dll корды хз кокого объекта
	* а этот метод скажет попали ли мы в термик
	*/
	bool _IsSelfPosInThermik(const CThermBaloon & ThermBaloon, const CPoint3D ActorPos)
	{
		float d = CMath::GetDistance2D(ThermBaloon.GetPos(), ActorPos);

		if (d <= ThermBaloon.GetRadius())
		{

			if (
				true
				//ActorPos.GetZ() >= ThermBaloon.GetPos().GetZ()
				//&& ActorPos.GetZ() <= ThermBaloon.GetPos().GetZ() + ThermBaloon.GetHight()
				)
			{
				return true;
			}
		}

		return false;
	}

private:
	CDequeObjectContainer<CThermBaloon> _Therm;
};


#endif  






