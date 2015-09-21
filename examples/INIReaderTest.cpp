// Example that shows simple usage of the INIReader class

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <inicpp/INIReader.hpp>
using namespace inicpp;

int main(int argc, char* argv[])
{
    INIReader reader("test.ini");

    if (reader.ParseError() < 0) {
        cout << "Can't load 'test.ini'\n";
        return 1;
    }

    cout << "Config loaded from 'test.ini'..." << endl
         << "version = " << reader.Get<int>("protocol", "version", -1) << endl
         << "name    = " << reader.Get<string>("user", "name", "UNKNOWN") << endl
         << "email   = " << reader.Get<string>("user", "email", "UNKNOWN") << endl
         << "active  = " << reader.Get<bool>("user", "active", true) << endl
         << "phones  = " << endl;

    vector<string> phones = reader.GetList<string>("user", "phones");

    for (auto& p : phones)
        cout << p << endl;

    return 0;
}
