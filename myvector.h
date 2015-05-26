#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <vector>
#include "ball.h"
//#include "Tray.h"
using namespace std;
class Tray;
template<class T> class myvector{
private:
    vector<T*> v; // vektort tároló osztály
public:
    // biztosítani kell az interface-eket
    myvector<T>();
    void push_back(T*);
    void clear();
    T& pop_back();
    T & operator [](unsigned int position);
    size_t size();
    void allDraw();
    void allDrawdirection();
    void allsetDirectionRandom();
    void allrandomizeVelocity();
    void allsetXY(double,double );
    void allCompute(Tray&, Tray&);
    double mingetY();
    bool isOut();
    ~myvector();
    void Draw();
};

template<class T> myvector<T>::myvector(){}

template<class T> void myvector<T>::push_back(T* element){
    v.push_back(element);
}
template<class T> void myvector<T>::clear(){
    v.clear();
}
template<class T> T& myvector<T>::operator [](unsigned int position){
    return *(v.at(position));
}
template<class T> size_t myvector<T>::size(){
    return v.size();

}
template<class T> myvector<T>::~myvector(){
    for(int i=0; i < v.size(); i++)
        delete v[i];

}
template<class T>void myvector<T>::allDraw(){
    for(int i=0; i < v.size(); i++)
        (v.at(i))->Draw();
}
template<class T>void myvector<T>::allDrawdirection(){
    for(int i=0; i < v.size(); i++)
        (v.at(i))->DrawDirection();
}

template<class T>void myvector<T>::allsetDirectionRandom(){
    for(int i=0; i < v.size(); i++)
        (v.at(i))->setDirectionRandom();
}
template<class T>void myvector<T>::allrandomizeVelocity(){
    printf("allrandomizevelocity()\n");
    for(int i=0; i < v.size(); i++)
        (v.at(i))->randomizeVelocity();
}
template<class T>void myvector<T>::allsetXY(double x, double y){
    for(int i=0; i < v.size(); i++)
        (v.at(i))->setXY(x,y);
}
template<class T>void myvector<T>::allCompute(Tray& t1,Tray& t2){
    for(int i=0; i < v.size(); i++)
        (v.at(i))->Compute(t1, t2);
}
template<class T> bool myvector<T>::isOut(){
    for(int i=0; i < v.size(); i++){
        if((v.at(i))->isOut())
            return true;
    }
    return false;
}
template<class T> double myvector<T>::mingetY(){
    double minimal = (v.at(0))->getY();
    for(int i = 0; i< v.size(); i++){
        if((v.at(i))->getY() < minimal)
            minimal = (v.at(i))->getY();
    }
    return minimal;
}
#endif // MYVECTOR_H
