#pragma once
#include "Settings.h"
#include <iostream>
#include <fstream>
using namespace std;

class Logger{
public: 
    static void log(const string & origin, const string & message, const string & filelocation = std::string(Settings::programDir) + std::string(Settings::logfilename)){
		cout << filelocation << endl;
        ofstream filestream(filelocation, std::ios_base::app);
        if(filestream.good()){
            filestream << origin: << " "<< message << "\n";
            filestream.close();
        }
        else{
			cout << "Could not log to file" << filelocation << endl; 
        }
    }
};
