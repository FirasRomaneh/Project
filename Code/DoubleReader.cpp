#include "DoubleReader.h"

void DoubleReader::Read(std::string path, int Readindex){
    std::ifstream ReadFile(path);
    std::string Read;
    std::getline(ReadFile, Read);
    DoubleType newdouble = DoubleType();
    std::time_t newTime = 0;
    newdouble.setTimeStamp(newTime);
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
                newdouble.setTimeStamp(newTime);
                newdouble.setData(std::stod(split.at(1)));
            } else{
                goto finish;
            }
        }
        if(CM->getTS() >= newTime){
            DS->Write(newdouble, Readindex);
            Write = true;
        } else{
            Write = false;
        }
    }
    finish:
    ReadFile.close();
}

void DoubleReader::start(){
    std::thread DoubleRead(&DoubleReader::Read, this);
    DoubleRead.join();
}