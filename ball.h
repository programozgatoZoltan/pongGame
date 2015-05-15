#ifndef BALL_H
#define BALL_H
#include "opencv2/core/core.hpp" // open cv
#include "displayable.h"
#include "tray.h"
#include "area.h"

using namespace cv;
// labda sebessége
typedef double Velocity;
// elő deklarációk
class Tray;
class Area;
class Ball: public Displayable {
private:
    cv::Point_<double> coordinate;// coordinates
    double r; // ball radius
    double vx, vy; //iranyvektor
    cv::Scalar* color; //szín
    Velocity velocity; //sebesség

    int x_MAX, y_MAX; // pálya limit
    // elérte e a falat?
    bool hWall;
    // az irányvektort kb. 5%-os tartományban véletlenszerűen megváltoztatja
    void randomizeDirection();
protected:
    // ősosztályból örökölt képernyőkép deklarálása
    Mat Displayable::image;
public:
    // x, y koordinátával létrehozható konstruktor
    Ball(double, double);
    // másoló konstruktor
    Ball(const Ball&);
    // a képernyőre rajzoló tagfüggvény
    void Draw();
    // Fejlesztést segítő fv.
    // A labda irányvektorát rajzolja a képernyőre
    void DrawDirection();
    // get fv.-ek a tagváltozókhoz
    double getX()const {
        return coordinate.x;
    }
    double getY()const {
        return coordinate.y;
    }
    double getVX()const {
        return vx;
    }
    double getVY()const {
        return vy;
    }
    double getR()const {
        return r;
    }
    double getVelocity()const {
        return velocity;
    }
    // set fv.-ek a tagváltozókhoz
    void setX(double);
    void setY(double);
    void setXY(double, double);
    void setR(double);
    // sebesség beállítása
    void setVelocity(Velocity);
    // sebesség beállítása(az érték hozzáadódik a jelenlegihez)
    void setVelocityRel(Velocity);
    // sebesség nagyságának módosítása véletlen számmal
    void randomizeVelocity();
    void setDirection(double, double);
    // kezdeti irányvektor beállítás
    void setDirectionRandom();
    // gondoskodik a falról, és ütőkről való visszapattanásról
    void Compute(Tray&, Tray&);
    // megállapítja, hogy a pályán kívül van e a labda
    bool isOut();
    // érintetük e a falat. Véletlen faktorok hozzáadásához szükséges
    bool hitWall();
    // értékadás operátor
    Ball& operator=( const Ball& rhs );
    ~Ball();
};
#endif // BALL_H

