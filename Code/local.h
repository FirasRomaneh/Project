#include <iostream>
#include <mutex>
#include <ctime>
#include <vector>
#include <thread>
#include <sstream>
#include <fstream>
#include "Type.h"


enum index{
    Left_image = 0,
    Front_image,
    Rigth_image,
    Back_image,
    GPS,
    Speed,
    Steering,
    Break,
    Throttle,
};
