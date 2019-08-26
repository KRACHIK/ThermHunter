#include "INI_Writer_impl.hpp"


CWriteINI_Impl::CWriteINI_Impl()
{
	m_bOverrideNames = true;
	m_bIsOpen = false;
}

CWriteINI_Impl::CWriteINI_Impl(const std::string& path, bool overrideNames /*= true*/)
{
	m_bOverrideNames = overrideNames;
	m_bIsOpen = false;
	load(path);
}

CWriteINI_Impl::~CWriteINI_Impl()
{
	close();
}

void CWriteINI_Impl::insert(const std::string& section, const std::string& name, const std::string& value /*= ""*/, bool override /*= true*/)
{
	CValue val = { name, value };

	// Insert if section already exists
	for (int i = 0; i < m_valueList.size(); i++)
	{
		if (section == m_valueList[i].first)
		{
			// If override is true, we have to check if an existing name is present in the list and
			// replace its value with the new one
			if (override)
			{
				for (int j = 0; j < m_valueList[i].second.size(); j++)
				{
					// Replace the value
					if (m_valueList[i].second[j].name == name)
					{
						m_valueList[i].second[j].value = value;
						return;
					}
				}
			}

			// Create a new name and value to the list
			m_valueList[i].second.push_back(val);
			return;
		}
	}

	// Insert new section along with name and value
	m_valueList.push_back(std::pair<std::string, std::vector<CValue> >(section, std::vector<CValue>()));
	m_valueList[m_valueList.size() - 1].second.push_back(val);
}

bool CWriteINI_Impl::load(const std::string& path, bool clear /*= true*/)
{
	std::string data = "";
	std::ifstream stream(path.c_str());

	if (stream.is_open())
	{
		while (stream.good())
			data += stream.get();

		// Return status of parse
		return parse(data.c_str(), data.size(), clear);
	}

	std::cout << "ini::IniDocumentImpl::load(...) : file not found " << path << std::endl;

	return false;
}

bool CWriteINI_Impl::parse(const char* data, unsigned int size /*= 0*/, bool clear /*= true*/)
{
	// Clear current value list if it has been open (or has values in the list) and
	// clear set to true to force  it to be cleared for new values
	if ((isOpen() || m_valueList.size() > 0) && clear == true)
		close();

	unsigned int dataSize = size;

	// If size is zero, automatically determine its size from char pointer if possible
	if (dataSize < 1)
	{
		dataSize = strlen(data);

		if (dataSize < 1)
		{
			std::cout << "ini::IniDocumentImpl::parse(...) : size of data is zero!" << std::endl;
			return false;
		}
	}

	// Setup states and current state
	enum STATE { SECTION, NAME, VALUE };
	int state = SECTION;

	// To build content on
	std::string section = "";
	std::string name = "";
	std::string value = "";

	bool sectionInitiate = false;
	bool valueInitiate = false;
	bool comment = false;

	for (unsigned int index = 0; index <= dataSize; index++)
	{
		// Ignore rest of line when comment appears - if value is not empty (assume that the value already has been parsed) then the character
		// will become a part of the value itself
		if ((data[index] == '#' || data[index] == ';') && state != VALUE)
			comment = true;

		if (comment)
		{
			if (data[index] == '\n' || data[index] == '\r')
				comment = false;

			continue;
		}

		// Parser state machine
		switch (state)
		{
		case SECTION:
			if (!sectionInitiate)
			{
				if (data[index] == '[')
				{
					sectionInitiate = true;
					section = "";
				}
				else
				{
					if (!isspace(data[index]))
					{
						state = NAME;
						index--;
					}
				}
			}
			else
			{
				if (data[index] == ']')
					state = NAME;
				else
					section += data[index];
			}
			break;
		case NAME:
			// Do not parse data if space is present and no name has been read
			if (isspace(data[index]))
			{
				if (name.empty())
					continue;
				else
					state = VALUE;
			}
			else
			{
				if (data[index] == '=')
				{
					state = VALUE;
					valueInitiate = true;
				}
				else
					name += data[index];
			}
			break;
		case VALUE:
			if (!valueInitiate)
			{
				if (data[index] == '=')
					valueInitiate = true;
			}
			else
			{
				// Insert values to list when reaching a new line or EOF
				if ((data[index] == '\n' || data[index] == '\r') || index == dataSize)
				{
					// Insert value to list
					insert(section, name, value, m_bOverrideNames);

					state = SECTION;
					valueInitiate = false;
					sectionInitiate = false;

					// Clear temp buffers
					name.clear();
					value.clear();
				}
				else
					value += data[index];
			}
			break;
		}
	}
	m_bIsOpen = true;

	return true;
}

void CWriteINI_Impl::save(const std::string& path)
{
	std::ofstream stream;
	stream.open(path.c_str());

	for (int i = 0; i < m_valueList.size(); i++)
	{
		// Global section should never be written
		if (!m_valueList[i].first.empty())
			stream << '[' << m_valueList[i].first << ']' << std::endl;

		for (int j = 0; j < m_valueList[i].second.size(); j++)
			stream << m_valueList[i].second[j].name << '=' << m_valueList[i].second[j].value << std::endl;
	}
	stream.close();
}

void CWriteINI_Impl::dump()
{
	for (int i = 0; i < m_valueList.size(); i++)
	{
		if (!m_valueList[i].first.empty())
			std::cout << '[' << m_valueList[i].first << ']' << std::endl;

		for (int j = 0; j < m_valueList[i].second.size(); j++)
			std::cout << m_valueList[i].second[j].name << '=' << m_valueList[i].second[j].value << std::endl;
	}
}

unsigned int CWriteINI_Impl::size()
{
	unsigned int count = 0;
	for (int i = 0; i < m_valueList.size(); i++)
		count += m_valueList[i].second.size();

	return count;
}
