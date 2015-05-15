#include "opencv2/core/core.hpp"
#include "area.h"
using namespace cv;

Mat Displayable::image;
Area::Area():Displayable(){
        width = Displayable::image.cols;
        height = Displayable::image.rows;
    }
void Area::Draw(){
    rectangle(Displayable::image, Point( 0, 0), Point( width-2, height-2), *gray, -1, 8 ); //szürke pálya alap
    rectangle(Displayable::image, Point( 0, 0), Point( width-2, height-2), *white, 4, 8 ); //fehér körvonal
    line(Displayable::image, Point( 0, height/2 ), Point( width, height/2), *white,  2, 8 ); //középvonal
    circle(Displayable::image, Point(width/2,height/2), 80, *white, 2, 8, 0); //fehér kör
}
Area::~Area(){
    delete gray;
    delete white;
}
