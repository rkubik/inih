#include <ini.h>
#include <INIReader.hpp>

#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

namespace inicpp {

INIReader::INIReader(const string &filename)
{
    Parse(filename);
}

INIReader::INIReader(void)
{
}

void INIReader::Parse(const string &filename)
{
    m_error = ini_parse(filename.c_str(), ValueHandler, this);
}

int INIReader::ParseError() const
{
    return m_error;
}

bool INIReader::Has(const string &section, const string &name)
{
    const string key = MakeKey(section, name);

    return m_values.count(key) > 0;
}

template int    INIReader::Get <int>    (const string &section, const string &name, const int    &default_value);
template float  INIReader::Get <float>  (const string &section, const string &name, const float  &default_value);
template double INIReader::Get <double> (const string &section, const string &name, const double &default_value);
template char   INIReader::Get <char>   (const string &section, const string &name, const char   &default_value);
template string INIReader::Get <string> (const string &section, const string &name, const string &default_value);
template <typename T>
T INIReader::Get(const string &section,
                 const string &name,
                 const T &default_value)
{
    T value;
    const string key = MakeKey(section, name);

    if (!m_values.count(key))
        return default_value;

    stringstream ss(m_values[key]);
    ss >> value;

    if (ss.fail())
        return default_value;

    return value;
}

template <>
bool INIReader::Get<bool>(const string &section,
                          const string &name,
                          const bool &default_value)
{
    const string valstr = Get<string>(section, name, "");

    return StringToBool(valstr, default_value);
}

template vector<int>    INIReader::GetList <int>    (const string &section, const string &name, const char delim);
template vector<float>  INIReader::GetList <float>  (const string &section, const string &name, const char delim);
template vector<double> INIReader::GetList <double> (const string &section, const string &name, const char delim);
template vector<char>   INIReader::GetList <char>   (const string &section, const string &name, const char delim);
template vector<string> INIReader::GetList <string> (const string &section, const string &name, const char delim);
template <typename T>
vector<T> INIReader::GetList(const string &section,
                             const string &name,
                             char delim)
{
    T value;
    const string key = MakeKey(section, name);
    vector<T> values;
    stringstream ss(m_values[key]);
    string token;

    while (ss.good()) {
        getline(ss, token, delim);
        stringstream tss(token);
        tss >> value;
        if (!tss.fail())
            values.push_back(value);
    }

    return values;
}

template<>
vector<bool> INIReader::GetList<bool>(const string &section,
                                      const string &name,
                                      const char delim)
{
    vector<bool> values;
    const vector<string> str_values = GetList<string>(section, name, delim);

    vector<string>::const_iterator beg = str_values.begin();
    vector<string>::const_iterator end = str_values.end();

    for (; beg != end; ++beg)
        values.push_back(StringToBool(*beg, false));

    return values;
}

vector<string> INIReader::GetSections(void) const
{
    return m_sections;
}

vector<string> INIReader::GetKeys(const string& section) const
{
    vector<string> keys;

    map<string, string>::const_iterator beg = m_values.begin();
    map<string, string>::const_iterator end = m_values.end();

    for (; beg != end; ++beg) {
        const string &c = (*beg).first;
        const size_t pos = c.find_first_of(".");

        if (section == c.substr(0, pos))
            keys.push_back(c.substr(pos + 1, c.size() - pos));
    }

    return keys;
}

string INIReader::MakeKey(const string &section, const string &name)
{
    string key = section + "." + name;

    transform(key.begin(), key.end(), key.begin(), ::tolower);

    return key;
}

int INIReader::ValueHandler(void* user, const char* section, const char* name,
                            const char* value)
{
    INIReader* reader = (INIReader*)user;
    const string key = MakeKey(section, name);

    if (reader->m_values[key].size() > 0)
        reader->m_values[key] += "\n";

    reader->m_values[MakeKey(section, name)] = value;

    vector<string>::const_iterator beg = reader->m_sections.begin();
    vector<string>::const_iterator end = reader->m_sections.end();

    if (find(beg, end, section) == end)
        reader->m_sections.push_back(section);

    return 1;
}

bool INIReader::StringToBool(string value, bool default_value)
{
    transform(value.begin(), value.end(), value.begin(), ::tolower);

    if (value == "true" || value == "yes" || value == "on" || value == "1")
        return true;
    else if (value == "false" || value == "no" || value == "off" || value == "0")
        return false;
    else
        return default_value;
}

const char INIReader::DEFAULT_LIST_DELIM = ',';

};
