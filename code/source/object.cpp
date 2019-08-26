#include "object.h"

CThermikINI::CThermikINI(const std::string &sPath)
	: IEngineINIModel(sPath)
{
	/* if file not created*/
	if (IsExits())
		Save(); // created
}

bool CThermikINI::Load()
{
	Dump();

	EngineINIManager doc(GetFilePath());

	_fRadius = doc.GetReal("Thermik", "fRadius", -1.0f);
	_Count = doc.GetInteger("Thermik", "Count", -1);

	_x = doc.GetReal("Thermik", "x", -1.0f);
	_y = doc.GetReal("Thermik", "y", -1.0f);
	_z = doc.GetReal("Thermik", "z", -1.0f);

	return true;
}

bool CThermikINI::Save()
{
	EngineINIManager doc(GetFilePath());

	doc.insert("Thermik", "fRadius", std::to_string(_fRadius));
	doc.insert("Thermik", "Count", std::to_string(_Count));
	doc.insert("Thermik", "x", std::to_string(_x));
	doc.insert("Thermik", "y", std::to_string(_y));
	doc.insert("Thermik", "z", std::to_string(_z));

	Dump();

	doc.Save(GetFilePath());
	return true;
}
void CThermikINI::Dump()
{ 
	Log("[CThermikINI::Dump] : pos [%f %f %f] C%d  R%f"
		, _x
		, _y
		, _z
		, _Count
		, _fRadius
	);
}

