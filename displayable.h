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
// "Megjeleníthetõ" õsosztály, ebbõl származtatjuk a különféle grafikus elemeket
class Displayable {
protected:
    // Itt készül el az aktuális képernyõkép
    static Mat image;
public:
    // képernyõkép lekérése
    static Mat & getImage() {
        return image;
    }
    // képernyõkép beállítása
    static void setImage(Mat i) {
        image = i;
    }
    virtual void Draw() = 0;
    virtual ~Displayable(){}
};
#endif // DISPLAYABLE_H

