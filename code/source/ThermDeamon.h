
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

		CPoint3D CurPos(700.0, 700.0, 0.0);
		float	 fRadius = 40.0f;
		float	 fHight = 20.0f;
		int		 Count = 10;

		CThermBaloon StartBaloon( /* Spawn*/ CPoint3D(1000.0, 1000.0, 1.0) , CurPos , fRadius , fHight /*temperature*/, 37.0f );

		float  X_Offset = 2.0f * fRadius;
		float  Y_Offset = 0; //fRadius + 3.0f;

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
	}

	void Is_Self_Pos_In_Thermik(const CObject ActorPos, OUT float *Design)
	{
		for (size_t i = 0; i < _Therm.Size(); i++)
		{
			if (_IsSelfPosInThermik(_Therm.GetObjectIndex(i), ActorPos.GetPos(), "ThermBaloon" + std::to_string(i)))
			{
				*Design = 1.0f;

				return;
			}
		}

		*Design = 0.0f;
	}



private:

	/**
	* IsSelfPosInThermik
	* Клео скрипт передаст в dll корды хз кокого объекта
	* а этот метод скажет попали ли мы в термик
	*/
	bool _IsSelfPosInThermik(const CThermBaloon & ThermBaloon, const CPoint3D ActorPos
		, const std::string DbgMsg)
	{
		float d = CMath::GetDistance2D(ThermBaloon.GetPos(), ActorPos);
		float dNew = CMath::GetDistance2DNew(ThermBaloon.GetPos(), ActorPos);
		
		Log(
			"[CThermDeamon::_IsSelfPosInThermik] : [old] [%s] Distance d=%f, [ActorPos: %s], [ThermPos %s]  GetRadius=%f"
			, DbgMsg.c_str()
			, d
			, ActorPos.GetDbgStr().c_str()
			, ThermBaloon.GetPos().GetDbgStr().c_str()
			, ThermBaloon.GetRadius()
		);

		Log(
			"[CThermDeamon::_IsSelfPosInThermik] : [New] [%s] Distance d=%f, [ActorPos: %s], [ThermPos %s]  GetRadius=%f"
			, DbgMsg.c_str()
			, dNew
			, ActorPos.GetDbgStr().c_str()
			, ThermBaloon.GetPos().GetDbgStr().c_str()
			, ThermBaloon.GetRadius()
		);


		 
		if (dNew <= ThermBaloon.GetRadius())
		{
			return true;
		}
		return false; 

	}

private:
	CDequeObjectContainer<CThermBaloon> _Therm;
};


#endif  






