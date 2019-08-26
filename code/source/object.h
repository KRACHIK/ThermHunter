
#pragma once

#ifndef C_OBJECT_H
#define C_OBJECT_H

#include "def.h"				// base class
#include "SrcIni\EngineINIManager.h"

class IEngineINIModel; /*interface*/
class CThermikINI; /* for IEngineINIModel*/
class CThermBaloon;

 
/* CThermBaloon
 * структура которая моделирует  "термический пузырь"
 */
class CThermBaloon
{
public:
	CThermBaloon() {
	}

	CThermBaloon(CPoint3D  SpawnPos, CPoint3D  CurPos, float  fRadius, float  fHight, float  fStartTemperature)
		: _SpawnPos(SpawnPos)
		, _CurPos(CurPos)
		, _fRadius(fRadius)
		, _fHight(fHight)
		, _fStartTemperature(fStartTemperature)
	{
	}

	void DebugPrint()
	{
		printf("[DebugPrint] : Pos[%f, %f, %f] : \n"
			, _CurPos.GetX()
			, _CurPos.GetY()
			, _CurPos.GetZ()
		);


		Log("[void DebugPrint]  Pos[%f, %f, %f] : \n"
			, _CurPos.GetX()
			, _CurPos.GetY()
			, _CurPos.GetZ()
		);
	}



	void InitForCleo(
		/* x */ float* A1,
		/* y */ float* A2,
		/* z */ float* A3,
		/* Hight */ float* A4,
		/* Radius */ float* A5)
	{
		*A1 = _CurPos.GetX();
		*A2 = _CurPos.GetY();
		*A3 = _CurPos.GetZ();
		*A4 = _fHight;
		*A5 = _fRadius;

		Log("[void InitForCleo]  Pos[%f, %f, %f] [%f, %f] : \n"
			, _CurPos.GetX()
			, _CurPos.GetY()
			, _CurPos.GetZ()
			, _fHight
			, _fRadius
		);
	}

	void SetCurPos(const  CPoint3D & Point) { _CurPos = Point; }
	CPoint3D  GetPos() const { return _CurPos; }

	float  GetRadius() const { return  _fRadius; }
	float  GetHight() const { return   _fHight; }

private:
	CPoint3D  _SpawnPos;          // Корды спавна 
	CPoint3D  _CurPos;	          // текущие корды
	float     _fRadius;	          // Радиус Термика
	float     _fHight; // Температура в точке отрыва?!
	float     _fStartTemperature; // Температура в точке отрыва?!
};

class CObject
{
public:

	CObject() {
	}

	void Set(
		/* x */ float* A1,
		/* y */ float* A2,
		/* z */ float* A3)
	{
		_CurPos.Set(A1, A2, A3);
	}

	void Get(
		/* x */ float* A1,
		/* y */ float* A2,
		/* z */ float* A3)
	{
		_CurPos.Get(A1, A2, A3);
	}

	CPoint3D  GetPos() const {
		return _CurPos;
	}

private:
	CPoint3D  _CurPos;	          // текущие корды
};

  
class IEngineINIModel
{
public:

	IEngineINIModel(const std::string &sPath)
		: _sFilePath(sPath) {
	}


	int IsExits() {
		EngineINIManager doc(GetFilePath());
		return doc.ParseError();
	}

	virtual ~IEngineINIModel() {}

	std::string GetFilePath() const { return _sFilePath; }

	void SetFileName(const  std::string &  FileName)
	{
		_sFilePath = FileName;
	}

protected:
	virtual bool Load(/*const std::string &sPath*/) = 0;
	virtual bool Save() = 0;

private:
	std::string  _sFilePath;
};

class CThermikINI : public IEngineINIModel
{
public:

	CThermikINI(const std::string &sPath);

	bool Load();

	void Dump();

	bool Save();
	 
	CThermBaloon GetThermBaloon()
	{
		CPoint3D CurPos(_x, _y, _z);

		CThermBaloon StartBaloon( /* Spawn*/ CPoint3D(0.0, 0.0, 0.0), CurPos, _fRadius, /*fHight */40.0f,/*temperature*/ 37.0f);
		return StartBaloon;
	}

	int GetCount() const
	{
		return _Count;
	}

private:
  
	float	_x = 800.0f;
	float	_y = 800.0f;
	float	_z = 40.0f;
	float	_fRadius = 40.0f;
	int		_Count = 10;
};
 
#endif