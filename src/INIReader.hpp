#ifndef __INIREADER_HPP__
#define __INIREADER_HPP__

#include <map>
#include <string>
#include <vector>

namespace inicpp {

class INIReader
{
public:
    INIReader(const std::string &filename);
    INIReader(void);

    /**
     * Parse INI config file.
     */
    void Parse(const std::string &filename);

    /**
     * Return the result of ini_parse().
     *
     * @return 0 on success, line number of first error on parse error, or
     *         -1 on file open error
     */
    int ParseError(void) const;

    /**
     * If value exists in a given section.
     *
     * @param section INI section
     * @param name INI label within section
     *
     * @return true if value exists in given section
     */
    bool Has(const std::string &section, const std::string &name);

    /**
     * Get value from INI file.
     *
     * @param section INI section
     * @param name INI label within section
     * @param default_value Default value if section.name is not found.
     *
     * @return Value at section.name in INI file or default_value
     */
    template <typename T>
    T Get(const std::string &section, const std::string &name,
          const T &default_value);

    /**
     * Return list of values from a delimited string value.
     *
     * @param section INI section
     * @param name INI label within section
     * @param delim What character to parse list entries by
     *
     * @return List of values
     */
    template <typename T>
    std::vector<T> GetList(const std::string &section,
                           const std::string &name,
                           const char delim=DEFAULT_LIST_DELIM);

    /**
     * Return all sections from the INI file.
     *
     * @return List of sections
     */
    std::vector<std::string> GetSections(void) const;

    /**
     * Return all keys from an INI section.
     *
     * @return List of label names from given section
     */
    std::vector<std::string> GetKeys(const std::string& section) const;

private:
    const static char DEFAULT_LIST_DELIM;

    static std::string MakeKey(const std::string &section, const std::string &name);
    static int ValueHandler(void* user, const char* section, const char* name,
                            const char* value);
    static bool StringToBool(std::string value, bool default_value);

    int m_error;
    std::map<std::string, std::string> m_values;
    std::vector<std::string> m_sections;
};

};

#endif
