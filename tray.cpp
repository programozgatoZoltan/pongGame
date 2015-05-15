#include "opencv2/core/core.hpp"
#include "tray.h"
using namespace cv;
//Mat Displayable::image;
Tray::Tray(int x, int y, int width, int height):Displayable(), y(y), x(x){
    this->width = width;
    this->height = height;
    x_MAX = 300;
    color = new cv::Scalar(0,0,0); // fekete
}
bool Tray::setX(int x){
    if(x > width/2 && x < x_MAX-width/2){
        this->x = x;
        return true;
    }
    return false;
}
bool Tray::setWidth(int width){
    this->width = width;
    return true;
}
bool Tray::setHeight(int height){
    this->height = height;
    return true;
}
void Tray::Draw(){
    rectangle(Displayable::image, Point(x-width/2, y+height/2), Point( x+width/2, y-height/2), *color,-1,8 );
}
using namespace std;
// a g�p �t�j�t be�ll�t� fv.
// jelenleg nincs implement�lva mesters�ges intelligencia
// �gy a g�p gyakorlatilag verhetetlen
void Tray::Compute(Ball& b){
    // megvizsg�ljuk hogy a labda az �t� fel� j�n e
    // ha a labda ir�nyvektora az esetleges pontszerz�s ter�lete fel� mutat, akkor
    // a g�p �t�j�t a labda fel� mozgatja
    if(b.getVY() != 0 && (
       (b.getVX() < 0 && atan(abs(b.getVX())/abs(b.getVY())) < atan(abs(b.getX())/abs(b.getY()))+0.17632698 && b.getVY()<0) ||
       (b.getVX() > 0 && atan(abs(b.getVX())/abs(b.getVY())) < atan(abs((x_MAX-b.getX()))/abs(b.getY()))+0.17632698 && b.getVY()<0)
        )){
        *color = Scalar(0,255,0);
        setX(b.getX());
    }else{
        *color = Scalar(0,0,0);
        // enyhe mozg�s
        setX(150 + (b.getX()-150)/5);
    }
}
Tray::~Tray(){
    delete color;
}