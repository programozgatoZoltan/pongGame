#include "opencv2/core/core.hpp"
#include "tray.h"
using namespace cv;
//Mat Displayable::image;
Tray::Tray():y(0){
    this->width = 100;
    this->height = 2;
    x_MAX = 300;
    color = new cv::Scalar(0,0,0); // fekete
}
Tray::Tray(int x, int y, int width, int height):Displayable(), y(y), x(x){
    this->width = width;
    this->height = height;
    x_MAX = 300;
    color = new cv::Scalar(0,0,0); // fekete
}
Tray::Tray(const Tray& t):y(t.getY()){
    this->x = t.x;
    this->width = t.width;
    this->height = t.height;
    this->x_MAX = t.x_MAX;
    this->y_MAX = t.y_MAX;
    this->color = new Scalar(*(t.color));
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
// a gép ütõjét beállító fv.
// jelenleg nincs implementálva mesterséges intelligencia
// így a gép gyakorlatilag verhetetlen
void Tray::Compute(Ball& b){
    // megvizsgáljuk hogy a labda az ütõ felé jön e
    // ha a labda irányvektora az esetleges pontszerzés területe felé mutat, akkor
    // a gép ütõjét a labda felé mozgatja
    if(b.getVY() != 0 && (
       (b.getVX() < 0 && atan(abs(b.getVX())/abs(b.getVY())) < atan(abs(b.getX())/abs(b.getY()))+0.17632698 && b.getVY()<0) ||
       (b.getVX() > 0 && atan(abs(b.getVX())/abs(b.getVY())) < atan(abs((x_MAX-b.getX()))/abs(b.getY()))+0.17632698 && b.getVY()<0)
        )){
        *color = Scalar(0,255,0);
        setX(b.getX());
    }else{
        *color = Scalar(0,0,0);
        // enyhe mozgás
        setX(150 + (b.getX()-150)/5);
    }
}
void Tray::Compute(myvector<Ball>& b){
    double ymin = (b[0]).getY();
    int minindex;
    for(int i=0; i < b.size(); i++){
        if((b[i]).getY() <= ymin){
            ymin = (b[i]).getY();
            minindex = i;
        }
    }
    Compute(b[minindex]);
}
Tray& Tray::operator=(const Tray& rhs){
    Tray* b = new Tray(rhs);
    return *b;
}
Tray::~Tray(){
    delete color;
}
