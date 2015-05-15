#include "ball.h"
#include "tray.h"
#include "opencv2/core/core.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <exception>
#include <iostream>
# define M_PI           3.14159265358979323846  /* pi */

using namespace std;
using namespace cv;
Ball::Ball(double x, double y) : Displayable() {
    r = 5; // radius
    //  pálya méretei
    x_MAX = 300;
    y_MAX = 600;
    // koordináták beállítása
    setX(x);
    setY(y);
    velocity = 20; // sebesség
    hWall = false; // kezdetben nem érinti a falat
    color = new cv::Scalar(0,0,255); //piros
    setDirectionRandom(); // irányvektor beállítás
    setVelocity((double)((rand()%2000)+2000)/1000); //labda gyorsaság random
}
Ball::Ball(const Ball& theOther){
    this->r = theOther.r;
    this->coordinate = theOther.coordinate;
    this->color = new Scalar;
    *(this->color) = *(theOther.color);
    this->velocity = theOther.velocity;
    this->vx = theOther.vx;
    this->vy = theOther.vy;
    this->x_MAX = theOther.x_MAX;
    this->y_MAX = theOther.y_MAX;
    this->hWall = theOther.hWall;

}
// Egy kitöltött kört rajzol
void Ball::Draw() {
    circle(Displayable::image, coordinate, (int)r, *color, -1,8,0);
}
// az irányvektort rajzolja ki a képernyőre
void Ball::DrawDirection() {
    line(Displayable::image, Point(150, 500), Point(150, 500), *color,  3, 8 );
    line(Displayable::image, Point(150, 500), Point(150+vx*velocity*10, 500+vy*velocity*10), *color,  1, 8 );
}
void Ball::setX(double x) {
    if(x < x_MAX-r && x > r)
        coordinate.x = x;
    else
        throw myexception("Ball::x invalid value");
}
void Ball::setY(double y) {
    // megakadályozzuk, hogy az oldalfalakon kívülre próbáljon rajzolni
    if(y < y_MAX-r && y > r)
        coordinate.y = y;
    else
        throw myexception("Ball::y invalid value");
}
// set fv-ek
void Ball::setXY(double x, double y) {
    coordinate.x = x;
    coordinate.y = y;
}
void Ball::setR(double r) {
    if(r<0)
        throw new myexception("Ball::r negative value!");
    this->r = r;
}
void Ball::setVelocity(Velocity v) {
    if(v<0)
        throw new myexception("Ball::v negative value!");
    velocity = v;
}
void Ball::setVelocityRel(Velocity v) {
    velocity += v;
}
void Ball::setDirection(double x, double y) {
    vx = x;
    vy = y;
}
void Ball::setDirectionRandom() {
    //random szög
    //random elõjel x, y
    double degree = (double)((rand() % 45000) + 45000) / 1000; //kezdeti szög 45-90fok között
    //printf("\ndeg: %lf\n",degree);
    degree *= M_PI / 180; //convert to radian
    //printf("radian: %lf\n", degree);
    vx = cos(degree); //make vector
    vy = sin(degree);
    //printf("vx = %lf, vy = %lf\n", vx, vy);
    int direction = rand() % 4;
    //printf("direction : %d\n", direction);
    switch(direction) {
    case 0:
        break;
    case 1:
        vx = -vx;
        break;
    case 2:
        vy = -vy;
        break;
    case 3:
        vx = -vx;
        vy = -vy;
        break;
    }
}
void Ball::Compute(Tray& t1, Tray& t2) {
    // következő koordináta számítása
    coordinate.x += vx * velocity;
    coordinate.y += vy * velocity;
    // oldalfalról való visszapattanás
    if( (coordinate.x >= x_MAX - 2 * r - 0.1 && vx > 0) ||
        (coordinate.x <= 2 * r + 0.1 && vx < 0)){
        vx = - vx;
    }
    // az ütőkről való visszapattanás
    // ha pálya széléhez értünk és az ütő két széle között vagyunk
    if((coordinate.y >= y_MAX - 2 - 2 * r && coordinate.x > t1.getX() - t1.getWidth() / 2 - 2 &&
         coordinate.x < t1.getX() + t1.getWidth() / 2 + 2 && vy > 0)) {
        hWall = true; //pontgyűjtéshez
        vy = - vy;
        Compute(t1, t2);
    }
    if((coordinate.y <= 2 * r + 2 && coordinate.x > t2.getX() - t2.getWidth() / 2 - 2 &&
         coordinate.x < t2.getX() + t2.getWidth() / 2 + 2 && vy < 0)) {
        vy = - vy;
        Compute(t1, t2);
    }
    // ha érintettük a falat, akkor randomizálunk
    if(hWall) {
        randomizeDirection();
        randomizeVelocity();
    }
}
bool Ball::hitWall() {
    if(hWall) {
        hWall = false;
        return true;
    }
    return false;
}
bool Ball::isOut() {
    // kiment e a labda
    if(coordinate.y > y_MAX || coordinate.y < 0)
        return true;
    return false;
}
void Ball::randomizeDirection() {// +/- 5fokot változtat
        vx = vx * (double)((rand()%200)+900)/1000;
        vy = vy * (double)((rand()%600)+700)/1000;
}
void Ball::randomizeVelocity() { // sebsség beállítása véletlen értékkel
    setVelocity((double)((rand()%3000)+4000)/1000);
}
Ball& Ball::operator=( const Ball& rhs ){
    Ball* b = new Ball(rhs);
    return *b;
}
Ball::~Ball(){
    delete color;
}

