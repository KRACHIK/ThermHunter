/* Created by Philzon @ github.com/philzon
*
*  This code is released under the Unilicense (Public Domain)
*/

#ifndef __ENGINE_INI_MANAGER_H__
#define	__ENGINE_INI_MANAGER_H__

#include <memory.h>

#include "INI_Reader_impl.h"
#include "INI_Writer_impl.hpp"

class EngineINIManager
{
public:
	EngineINIManager(const std::string& path, bool overrideNames = true);

	EngineINIManager();

	void insert(const std::string& Section, const std::string& sName,
		const std::string& sValue = "", bool bOverride = true);

	void Save(const std::string& sPath);

	// Return the result of ini_parse(), i.e., 0 on success, line number of
	// first error on parse error, or -1 on file open error.
	int ParseError() const;

	// Get a string value from INI file, returning default_value if not found.
	std::string Get(const std::string& section, const std::string& name,
		const std::string& default_value) const;

	// Get a string value from INI file, returning default_value if not found,
	// empty, or contains only whitespace.
	std::string GetString(const std::string& section, const std::string& name, 
		const std::string& default_value) const;

	// Get an integer (long) value from INI file, returning default_value if
	// not found or not a valid integer (decimal "1234", "-1234", or hex "0x4d2").
	long GetInteger(const std::string& section, const std::string& name,
		long default_value) const;

	// Get a real (floating point double) value from INI file, returning
	// default_value if not found or not a valid floating point value
	// according to strtod().
	double GetReal(const std::string& section, const std::string& name,
		double default_value) const;

	// Get a boolean value from INI file, returning default_value if not found or if
	// not a valid true/false value. Valid true values are "true", "yes", "on", "1",
	// and valid false values are "false", "no", "off", "0" (not case sensitive).
	
	bool GetBoolean(const std::string& section, const std::string& name,
		bool default_value) const;
	// Return true if the given section exists (section must contain at least
	// one name=value pair).
	
	bool HasSection(const std::string& section) const;

	// Return true if a value exists with the given section and field names.
	bool HasValue(const std::string& section, const std::string& name) const;

private:
	std::shared_ptr<CWriteINI_Impl> _pINIDocument;
	std::shared_ptr<CReaderINI_Impl> _pINIReader;

	std::string _sFileName;
};

#endif // __ENGINE_INI_MANAGER_H__ 