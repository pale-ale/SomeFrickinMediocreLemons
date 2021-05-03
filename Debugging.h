#pragma once
#include "Settings.h"
#include <iostream>
#include <fstream>
using namespace std;

namespace Debugging{
    static void log(const string &origin, const string &message, const string &fileLocation = std::string(Settings::programDir) + std::string(Settings::logFileName)){
        ofstream fileStream(fileLocation, std::ios_base::app);
        if(fileStream.good()){
            fileStream << origin << ": " <<  message << "\n";
            cout << origin << ": " <<  message << "\n";
            fileStream.close();
        }
        else{
			cout << "Could not log to file " << fileLocation << "\n"; 
        }
    }
};
