#ifndef AREA_H
#define AREA_H
#include "opencv2/core/core.hpp"
#include "displayable.h"
using namespace cv;
class Area: public Displayable{
private:
    int width, height; // pálya méretek
    const cv::Scalar* gray = new cv::Scalar( 140, 140, 140 ); // beépített szín típus
    const cv::Scalar* white = new cv::Scalar( 255, 255, 255 );
protected:
    Mat Displayable::image; // örökölt statikus kép
public:
    Area();
    int getWidth()const{return width;}
    int getHeight()const{return height;}
    Mat& getPalya(){return Displayable::image;}
    void Draw();
    ~Area();
};
#endif // AREA_H
