#include "DoubleReader.h"

void DoubleReader::Read(std::string path, int Readindex){
    //open the file
    std::ifstream ReadFile(path);
    std::string Read;
    //read first line
    std::getline(ReadFile, Read);
    DoubleType* newdouble = new DoubleType();
    std::time_t newTime = 0;
    newdouble->setTimeStamp(newTime);
    bool Write = true;
    extern int Work;
    while (Work){
        if(Write){ //if the write data to DataStore, Read newData.
            std::getline(ReadFile, Read);
            if(!ReadFile.eof()){ //if the file still have data, read the new line.
                //split the read line to get the TS and The Data.
                std::vector<std::string> split;
                std::stringstream tempString(Read);
                std::string temp;
                while (std::getline(tempString, temp, ',')){
                    split.push_back(temp);
                }
                newTime = std::stod(split.at(0));
                newdouble->setTimeStamp(newTime);
                newdouble->setData(std::stod(split.at(1)));
            } else{ //if the file don't have newData, Finish the read.
                goto finish;
            }
        }
        if(CM->getTS() >= newTime){ //if the Time of the newData less than TS of Front, Write The NewData to DataStore.
            DS->Write(newdouble, Readindex);
            Write = true;
        } else{ //Set Write to false to wait to write the NewData to DataStore.
            Write = false;
        }
    }
    finish: //close the file.
    ReadFile.close();
}