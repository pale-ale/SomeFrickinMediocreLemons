#pragma once
#include "Settings.h"
#include <iostream>
#include <fstream>
using namespace std;

class Logger{
public: 
    static bool logtofile(const string & message, const string & filelocation = Settings::logpath){
        ofstream filestream(filelocation, std::ios_base::app);
        if(filestream.good()){
            filestream << message << "\n";
            filestream.close();
            return true;
        }
        else{
            return false;
        }
    }
};
