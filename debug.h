#ifndef DEBUG_H
#define DEBUG_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "ball.h"
#include "tray.h"
#include "area.h"
using namespace std;
class Ball;
class Tray;
class Area;
namespace myDebugger{
    class Debug{
    private:
        ofstream myfile;
    public:
        Debug();
        void Info(char* info);
        static char* timeStamp();
        // operator << túlterhelés
        friend ostream& operator<<(ostream& os, Ball& b);
        friend ostream& operator<<(ostream& os, Tray& t);
        friend ostream& operator<<(ostream& os, Area& a);
        // kiíró fv-ek
        void print(Ball b);
        void print(Tray t);
        void print(Area a);
        ~Debug();
    };
    /*ostream& operator<<(ostream& os, Ball& b);
    ostream& operator<<(ostream& os, Tray& t);
    ostream& operator<<(ostream& os, Area& a);*/
}
#endif // DEBUG_H
