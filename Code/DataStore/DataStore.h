#ifndef DATASTORE_H
#define DATASTORE_H

#include "Code/local/local.h"

class DataStore{
    public:
        static DataStore* getInstance();
        void Write(Type*, int);
        Type* Read(int);
        static DataStore* instance;
    private:
        DataStore(){
            AllData.push_back(nullptr);
            AllData.push_back(nullptr);
            AllData.push_back(nullptr);
            AllData.push_back(nullptr);
            AllData.push_back(nullptr);
            AllData.push_back(nullptr);
            AllData.push_back(nullptr);
            AllData.push_back(nullptr);
            AllData.push_back(nullptr);
        };
        std::vector <Type*> AllData;
        std::mutex AllData_Mutex;
};

#endif