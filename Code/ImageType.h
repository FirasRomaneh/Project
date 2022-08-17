#ifndef IMAGETYPE_H
#define IMAGETYPE_H

#include "local.h"
#include <opencv2/opencv.hpp>


class ImageType : public Type{
    public:
        ImageType(){
            
        }
        ImageType(std::time_t TimeStamp, cv::Mat data): Type(TimeStamp){
            this->data = data;
        }
        void setData(cv::Mat data){
            this->data = data;
        }
        cv::Mat getData(){
            return this->data;
        }
    private:
        cv::Mat data;
};

#endif