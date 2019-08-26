/* Created by Philzon @ github.com/philzon
*
*  This code is released under the Unilicense (Public Domain)
*/

#ifndef __INI_WRITER_IMPL_H__
#define	__INI_WRITER_IMPL_H__

// C++ includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// C includes
#include <cstring>
#include <cctype>
#include <cstdlib>


class CWriteINI_Impl
{
public:
	CWriteINI_Impl();

	CWriteINI_Impl(const std::string& path, bool overrideNames = true);

	~CWriteINI_Impl();

	void insert(const std::string& section, const std::string& name, const std::string& value = "", bool override = true);

	void clear() { m_valueList.clear(); }

	bool load(const std::string& path, bool clear = true);

	// Parse data directly from a char pointer - size will automatically be determined if default value is 0
	bool parse(const char* data, unsigned int size = 0, bool clear = true);

	bool isOpen() { return m_bIsOpen; }

	void close() { clear(); m_bIsOpen = false; }

	void save(const std::string& path);

	void dump();

	unsigned int size();

	void overrideNames(bool status) { m_bOverrideNames = status; }

private:

	bool m_bOverrideNames;
	bool m_bIsOpen;
	struct CValue { std::string name; std::string value; };
	std::vector<std::pair<std::string, std::vector<CValue> > > m_valueList;
};


#endif //__INI_WRITER_IMPL_H__

