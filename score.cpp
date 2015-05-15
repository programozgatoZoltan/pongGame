#include "score.h"
#include <iostream>
#include <fstream>
#include <exception>
#include "displayable.h"
using namespace std;
Score::Score(){
    level = 1;
    score = 0;
    health = 3;
    bonus = 0;
    Ppoint=0, Mpoint = 0;
}
void Score::LevelInc(){
    level++;
}
void Score::Inc(int value){
    score += value;
    if(score>=100)bonus++;
}
void Score::setHealth(int value){
    health += value;
    if(health <= 0) health = 0;
}
void Score::setBonus(int value){
    bonus += value;
}
void Score::resetScore(){
    score = 0;
}
void Score::PlayerPointInc(){Ppoint++;}
void Score::MachinePointInc(){Mpoint++;}
// kiírjuk a képernyõre apontszámokat
void Score::Draw(){
    char* s = new char[20];
    char* l = new char[20];
    char* h = new char[20];
    char* b = new char[20];
    char* p = new char[20];
    char* m = new char[20];
    sprintf(s,"score : %d", score);
    sprintf(l,"level : %d", level);
    sprintf(h,"health : %d", health);
    sprintf(b,"bonus : %d", bonus);
    sprintf(p,"%d", Ppoint);
    sprintf(m,"%d", Mpoint);
    putText(Displayable::image, s, cvPoint(30,30),
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_8UC3);
    putText(Displayable::image, l, cvPoint(30,50),
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_8UC3);
    putText(Displayable::image, h, cvPoint(30,70),
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_8UC3);
    putText(Displayable::image, b, cvPoint(30,90),
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_8UC3);

    putText(Displayable::image, p, cvPoint(30,290),
    FONT_HERSHEY_COMPLEX_SMALL, 2, cvScalar(0,0,0), 2, CV_8UC3);
    putText(Displayable::image, m, cvPoint(30,340),
    FONT_HERSHEY_COMPLEX_SMALL, 2, cvScalar(0,0,0), 2, CV_8UC3);
    delete s;
    delete l;
    delete h;
    delete b;
    delete p;
    delete m;
}
void Score::gameOver(){
    putText(Displayable::image, "GAME OVER", cvPoint(68, 500),
    FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(2,2,255), 1, CV_8UC3);
}
void Score::win(){
    putText(Displayable::image, "WIN!", cvPoint(90, 500),
    FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(2,2,255), 1, CV_8UC3);
}
void Score::Start(){
    int baseline=0;
    // megnézzük milyen széles a szöveg, amit majd ki fogunk írni
    Size textSize = getTextSize( "Press key for start!", FONT_HERSHEY_COMPLEX_SMALL, 0.9, 1, &baseline);
    // így a képernyõ közepére tudjuk rendezni
    putText(Displayable::image, "Press key for start!", cvPoint(150-(textSize.width/2), 400),
    FONT_HERSHEY_COMPLEX_SMALL, 0.9, cvScalar(2,200,2), 1, CV_8UC3);
}
// az elért score-t elmenti file-ba
// megnyitás után megvizsgálja, hogy nagyobb e a jelenleg elért,
// mint az elõzõ, és csak akkor menti el
void Score::Save() {
    fstream myfile;
    unsigned int tmpscore = 0;
    myfile.open("hiscore.sav", ios::in | ios::out);
    if(myfile.is_open()){
        myfile >> tmpscore;
        myfile.clear();
        myfile.seekg(0); // a fájl pointert visszaálítjuk íráshoz
        if(score > tmpscore)
            myfile << score;
    }
    else
        throw myexception("Exception: a fajl nem nyithato meg");
    myfile.close();
    cout << tmpscore << endl;
}
// Pontszámok beolvasása file-ból
void Score::Read(){
    ifstream file;
    unsigned int savedScore;
    file.open("hiscore.sav", ios::in);
    if(file.is_open()){
        file >> savedScore;

        char* s = new char[20];
        sprintf(s, "Hi %d", savedScore);
        // szöveg hosszának meghatározása
        Size textSize = getTextSize(s, FONT_HERSHEY_COMPLEX_SMALL, 0.9, 1, 0);
        // szöveg kiírása
        putText(Displayable::image, s, cvPoint(150 - (textSize.width / 2), 500),
        FONT_HERSHEY_COMPLEX_SMALL, 0.9, cvScalar(10, 10, 12), 1, CV_8UC3);
        delete s;
    } else
        throw;
}
