#include "ImageReader.h"

void ImageReader::Read(std::string path, int Readindex){
    std::vector<std::string> images;
    cv::glob(path + "*.jpeg", images, false);
    unsigned int Imageindex = 0;
    ImageType* newImage = new ImageType();
    extern int Work;
    while (Work){
        std::string ImagePath = images.at(Imageindex);
        std::string ImageName = ImagePath;
        ImageName.erase(0, path.length());
        ImageName.erase((ImageName.length()-5), ImageName.length());
        std::time_t ImageTime = std::stod(ImageName);
        if(Readindex == 1){
            cv::Mat ImageData = cv::imread(ImagePath);
            newImage->setTimeStamp(ImageTime);
            newImage->setData(ImageData);
            DS->Write(newImage, Readindex);
            Imageindex++;
            if(Imageindex == images.size()){
                goto finish;
            }
        } else if((CM->getTS() >= ImageTime)){
            cv::Mat ImageData = cv::imread(ImagePath);
            newImage->setTimeStamp(ImageTime);
            newImage->setData(ImageData);
            DS->Write(newImage, Readindex);
            Imageindex++;
            if(Imageindex == images.size()){
                goto finish;
            }
        }
    }
    finish:;
}