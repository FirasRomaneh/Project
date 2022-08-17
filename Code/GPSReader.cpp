#include "GPSReader.h"

void GPSReader::Read(std::string path, int Readindex){
    std::ifstream ReadFile(path);
    std::string Read;
    std::getline(ReadFile, Read);
    GPSType newGPS = GPSType();
    std::time_t newTime = 0;
    newGPS.setTimeStamp(newTime);
    bool Write = true;
    while (true){
        if(Write){
            std::getline(ReadFile, Read);
            if(!ReadFile.eof()){
                std::vector<std::string> split;
                std::stringstream tempString(Read);
                std::string temp;
                while (std::getline(tempString, temp, ',')){
                    split.push_back(temp);
                }
                newTime = std::stod(split.at(0));
                newGPS.setTimeStamp(newTime);
                std::pair<double, double> newData;
                newData.first = std::stod(split.at(1));
                newData.second = std::stod(split.at(2));
                newGPS.setData(newData);
            } else{
                goto finish;
            }
        }
        if(CM->getTS() >= newTime){
            DS->Write(newGPS, Readindex);
            Write = true;
        } else{
            Write = false;
        }
    }
    finish:
    ReadFile.close();
}

void GPSReader::start(){
    std::thread GPSRead(&GPSReader::Read, this);
    GPSRead.join();
}