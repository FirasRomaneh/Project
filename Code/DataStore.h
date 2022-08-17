#ifndef DATASTORE_H
#define DATASTORE_H

#include "local.h"

class DataStore{
    public:
        static DataStore* getInstance();
        void Write(Type, int);
        std::vector <Type> Read();
        static DataStore* instance;
    private:
        DataStore();
        std::vector <Type> AllData;
        std::mutex AllData_Mutex;
};

#endif