#include "ImageReader.h"

void ImageReader::Read(std::string path, int Readindex){
    //vector to save the path of all image.
    std::vector<std::string> images;
    //read the path of all image in this path(path).
    cv::glob(path + "*.jpeg", images, false);
    unsigned int Imageindex = 0;
    ImageType* newImage = new ImageType();
    extern int Work;
    while (Work){
        std::string ImagePath = images.at(Imageindex);
        //split the imagePath to get the ImageName(TS of image).
        std::string ImageName = ImagePath;
        ImageName.erase(0, path.length());
        ImageName.erase((ImageName.length()-5), ImageName.length());
        std::time_t ImageTime = std::stod(ImageName); //String to tmie_t
        CheckTS: 
        if(Readindex == 1){ //if the Readindex equal 1 that means read FrontImage, wirte to DataStore directly.
            cv::Mat ImageData = cv::imread(ImagePath); //read the NewImage.
            newImage->setTimeStamp(ImageTime);
            newImage->setData(ImageData);
            DS->Write(newImage, Readindex);
            usleep(14000);
            Imageindex++;
            if(Imageindex == images.size()){ //if read all image, finish the read.
                goto finish;
            }
        } else if((CM->getTS() >= ImageTime)){ //if the TS of the newImage less than TS of front image, write NewImage to DataStore, else goto CheckTS.
            cv::Mat ImageData = cv::imread(ImagePath); //read the NewImage.
            newImage->setTimeStamp(ImageTime);
            newImage->setData(ImageData);
            DS->Write(newImage, Readindex);
            usleep(14000);
            Imageindex++;
            if(Imageindex == images.size()){ //if read all image, finish the read.
                goto finish;
            }
        } else{
            goto CheckTS;
        }
    }
    finish:;
}