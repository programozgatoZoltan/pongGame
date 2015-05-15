#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
#include "opencv2/core/core.hpp"
class myexception : public std::exception
{
   std::string s;
   public:
   myexception(std::string ss) : s(ss) {}
   ~myexception() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};
using namespace cv;
// "Megjelen�thet�" �soszt�ly, ebb�l sz�rmaztatjuk a k�l�nf�le grafikus elemeket
class Displayable {
protected:
    // Itt k�sz�l el az aktu�lis k�perny�k�p
    static Mat image;
public:
    // k�perny�k�p lek�r�se
    static Mat & getImage() {
        return image;
    }
    // k�perny�k�p be�ll�t�sa
    static void setImage(Mat i) {
        image = i;
    }
    virtual void Draw() = 0;
    virtual ~Displayable(){}
};
#endif // DISPLAYABLE_H

