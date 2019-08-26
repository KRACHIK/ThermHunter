#include "EngineINIManager.h"


EngineINIManager::EngineINIManager(const std::string& path, bool overrideNames /*= true*/)
{
	_sFileName = path;
	/*1*/_pINIReader = std::make_shared<CReaderINI_Impl>(path);
	/*2*/_pINIDocument = std::make_shared<CWriteINI_Impl>(path, overrideNames);
}

EngineINIManager::EngineINIManager()
{
	_pINIDocument = std::make_shared<CWriteINI_Impl>();
}

void EngineINIManager::insert(const std::string& Section, const std::string& sName, const std::string& sValue /*= ""*/, bool bOverride /*= true*/)
{
	_pINIDocument->insert(Section, sName, sValue, bOverride);
}

void EngineINIManager::Save(const std::string& sPath)
{
	_sFileName = sPath;
	_pINIDocument->save(sPath);
	_pINIDocument->close();

	_pINIReader.reset();
	_pINIReader = std::make_shared<CReaderINI_Impl>(_sFileName);
}

int EngineINIManager::ParseError() const
{
	return _pINIReader.get()->ParseError();
}

std::string EngineINIManager::Get(const std::string& section, const std::string& name, const std::string& default_value) const
{
	return _pINIReader.get()->Get(section, name, default_value);
}

std::string EngineINIManager::GetString(const std::string& section, const std::string& name, const std::string& default_value) const
{
	return _pINIReader.get()->GetString(section, name, default_value);
}

long EngineINIManager::GetInteger(const std::string& section, const std::string& name, long default_value) const
{
	return _pINIReader.get()->GetInteger(section, name, default_value);
}

double EngineINIManager::GetReal(const std::string& section, const std::string& name, double default_value) const
{
	return _pINIReader.get()->GetReal(section, name, default_value);
}

bool EngineINIManager::GetBoolean(const std::string& section, const std::string& name, bool default_value) const
{
	return _pINIReader.get()->GetBoolean(section, name, default_value);
}

bool EngineINIManager::HasSection(const std::string& section) const
{
	return _pINIReader.get()->HasSection(section);
}

bool EngineINIManager::HasValue(const std::string& section, const std::string& name) const
{
	return _pINIReader->HasValue(section, name);
}
