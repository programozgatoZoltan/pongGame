#ifndef MYVECTOR_H
#define MYVECTOR
#include <vector>
#include "ball.h"
template<class T> class myvector{
private:
    vector<T*> v; // vektort tároló osztály
public:
    // biztosítani kell az interface-eket
    myvector<T>();
    void push_back(T*);
    T& pop_back();
    T & operator [](unsigned int position);
    size_t size();
    void allDraw();
    void allDrawdirection();
    void allsetDirectionRandom();
    void allrandomizeVelocity();
    void allsetXY(double,double );
    void allCompute(Tray&,Tray&);
    ~myvector();
    void Draw();
};
#endif // MYVECTOR_H
template<class T> myvector<T>::myvector(){}

template<class T> void myvector<T>::push_back(T* element){
    v.push_back(element);
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
    for(int i=0; i < v.size(); i++)
        (v.at(i))->randomizeVelocity();
}
template<class T>void myvector<T>::allsetXY(double x, double y){
    for(int i=0; i < v.size(); i++)
        (v.at(i))->setXY(x,y);
}
template<class T>void myvector<T>::allCompute(Tray& t1,Tray& t2){
    for(int i=0; i < v.size(); i++)
        (v.at(i))->Compute(t1,t2);
}
