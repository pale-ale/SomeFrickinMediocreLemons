#pragma once
#include "Settings.h"
#include <iostream>
#include <fstream>
using namespace std;

namespace Debugging{
    enum logtype{
        Error,
        Info,
        Debug
    };
    static void log(const string &origin, const string &message, const string &fileLocation = std::string(Settings::programDir) + std::string(Settings::logFileName), const logtype &type = logtype::Info){
        ofstream fileStream(fileLocation, std::ios_base::app);
        if(fileStream.good()){
            fileStream << origin << ": " <<  message << "\n";
            fileStream.close();
        }
        else{
			cout << "Could not log to file " << fileLocation << "\n"; 
        }
        switch(type){
            case Error:  cout << origin << ":\033[1;31m " <<  message << "\033[0m\n"; break;
            case Info:  cout << origin << ": " <<  message << "\n"; break;
            case Debug:  cout << origin << ":\033[0;32m " <<  message << "\033[0m\n"; break;
        }
    }
};
