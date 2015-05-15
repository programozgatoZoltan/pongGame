#include "debug.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <ctime>
using namespace std;
using namespace myDebugger;
Debug::Debug(){
    // a pontos idõt és dátumot elõállítjuk
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    std::time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime(buffer,80,"%Y. %m. %d.", timeinfo);
    myfile.open("debug.log");
    myfile << "Log date [" << buffer << "]" << endl;
    printf("Log date [%s]\n", buffer);
    myfile << "time" << '\t' <<"type" << '\t' << 'x' << '\t' << 'y' << '\t' <<"vx" << '\t' <<"vy" << '\t' <<"vel"<< endl;
    printf("time\ttype\tx\ty\tvx\tvy\tvel\n");
}
ostream& operator<<(ostream& os, Ball b){ // egy labda objektum paramétereit képes kiírni
    char* time = new char[8];
    time = Debug::timeStamp();
    os.precision(4);
    os << time << '\t' << "b\t" << b.getX() << '\t' << b.getY() << '\t' <<  b.getVX() << '\t' << b.getVY() << '\t' <<  b.getVelocity();
    return os;
}
ostream& operator<<(ostream& os, Tray& t){ // egy ütõ objektum paramétereit képes kiírni
    os.precision(4);
    char* time = new char[8];
    time = Debug::timeStamp();
    os << time << '\t' << "t\t" << t.getX() << '\t' << t.getY() << '\t' << t.getWidth() << '\t' << t.getHeight();
    return os;
}
ostream& operator<<(ostream& os, Area& a){ // egy pálya objektum paramétereit képes kiírni
    os.precision(4);
    char* time = new char[8];
    time = Debug::timeStamp();
    os << time << '\t' << "a\t" << a.getWidth()<< '\t' << a.getHeight();
    return os;
}
// kiírja az idõt és a kapott szöveges értéket
void Debug::Info(char* info){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    std::time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer, 80, "%H:%M:%S", timeinfo);
    myfile << "[" << buffer << "] " << info << endl;
    printf("[%s] %s\n", buffer,  info);
}
void Debug::print(Ball b){
    cout << b << endl;
    if(myfile.is_open())
        myfile << b << endl;
}
void Debug::print(Tray t){
    cout << t << endl;
    if(myfile.is_open())
        myfile << t << endl;
}
void Debug::print(Area a){
    cout << a << endl;
    if(myfile.is_open())
        myfile << a << endl;
}
// visszaadja az aktuális idõt
char* Debug::timeStamp(){
    time_t rawtime;
    struct tm * timeinfo;
    char* buffer = new char[8];
    std::time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer, 80, "%H:%M:%S", timeinfo);
    sprintf(buffer, "%s", buffer);
    return buffer;
}
Debug::~Debug(){
    myfile.close();
}
