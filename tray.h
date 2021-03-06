#ifndef TRAY_H
#define TRAY_H
#include "opencv2/core/core.hpp"
#include "displayable.h"
#include "area.h"
#include "ball.h"
#include "myvector.h"
using namespace cv;
class Area;
class Ball;
class Tray: public Displayable{
private:
    int x;
    const int y; // az �t� y ir�nyban nem v�ltozik ez�rt konstans
    int width, height;
    int x_MAX, y_MAX;
    Scalar* color;
protected:
    Mat Displayable::image;
public:
    Tray();
    Tray(int x, int y, int width, int height);
    Tray(const Tray&);
    int getX()const{return x;}
    int getY()const{return y;}
    int getWidth()const{return width;}
    int getHeight()const{return height;}
    bool setX(int);
    bool setWidth(int);
    bool setHeight(int);
    void Draw();
    void Compute(Ball& b);
    void Compute(myvector<Ball>& balls);
    Tray& operator=(const Tray& rhs);
    ~Tray();
};
#endif // TRAY_H

