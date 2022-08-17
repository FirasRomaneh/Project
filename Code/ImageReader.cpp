#include "ImageReader.h"

void ImageReader::Read(std::string path, int Readindex){
    std::vector<std::string> images;
    cv::glob(path + "*.png", images, false);
    int Imageindex = 0;
    ImageType newImage = ImageType();
    while (true){
        std::string ImagePath = images.at(Imageindex);
        std::string ImageName = ImagePath;
        ImageName.erase(0, path.length());
        ImageName.erase((ImageName.length()-4), ImageName.length());
        std::time_t ImageTime = std::stod(ImageName);
        if(CM->getTS() >= ImageTime){
            cv::Mat ImageData = cv::imread(ImagePath);
            newImage.setTimeStamp(ImageTime);
            newImage.setData(ImageData);
            // ImageType newImage = ImageType(ImageTime, ImageData);
            DS->Write(newImage, Readindex);
            Imageindex++;
        }
    }
}

void ImageReader::start(){
    std::thread ImageRead(&ImageReader::Read, this);
    ImageRead.join();
}
