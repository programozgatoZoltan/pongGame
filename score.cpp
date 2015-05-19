#include "score.h"
#include <iostream>
#include <fstream>
#include <exception>
#include "displayable.h"
using namespace std;
Score::Score(){
    level = 1;
    score = 0;
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
void Score::setBonus(int value){
    bonus += value;
}
void Score::resetScore(){
    score = 0;
}
void Score::PlayerPointInc(){Ppoint++;}
void Score::MachinePointInc(){Mpoint++;}
// ki�rjuk a k�perny�re apontsz�mokat
void Score::Draw(){
    char s[20];
    char l[20];
    char b[20];
    char p[3];
    char m[3];
    sprintf(s,"score : %d", score);
    sprintf(l,"level : %d", level);
    sprintf(b,"bonus : %d", bonus);
    sprintf(p,"%d", Ppoint);
    sprintf(m,"%d", Mpoint);
    putText(Displayable::image, s, cvPoint(30,30),
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_8UC3);
    putText(Displayable::image, l, cvPoint(30,50),
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_8UC3);
    putText(Displayable::image, b, cvPoint(30,70),
    FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_8UC3);

    putText(Displayable::image, m, cvPoint(30,290),
    FONT_HERSHEY_PLAIN, 2.3, cvScalar(0,0,0), 2, CV_8UC3);
    putText(Displayable::image, p, cvPoint(30,340),
    FONT_HERSHEY_PLAIN, 2.3, cvScalar(0,0,0), 2, CV_8UC3);
}
void Score::gameOver(){
    string gameover = "GAME OVER!";
    Size textSize = getTextSize( gameover, FONT_HERSHEY_COMPLEX_SMALL, 1.2, 1, 0);
    putText(Displayable::image, gameover, cvPoint(150-textSize.width/2, 500),
    FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(2,2,255), 1, CV_8UC3);
}
void Score::win(){
    string win = "WIN!";
    Size textSize = getTextSize( win, FONT_HERSHEY_COMPLEX_SMALL, 1.2, 1, 0);
    putText(Displayable::image, win, cvPoint(150-textSize.width/2, 500),
    FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(2,2,255), 1, CV_8UC3);
}
void Score::Start(){
    int baseline=0;
    // megn�zz�k milyen sz�les a sz�veg, amit majd ki fogunk �rni
    Size textSize = getTextSize( "Press key for start!", FONT_HERSHEY_COMPLEX_SMALL, 0.9, 1, &baseline);
    // �gy a k�perny� k�zep�re tudjuk rendezni
    putText(Displayable::image, "Press key for start!", cvPoint(150-(textSize.width/2), 400),
    FONT_HERSHEY_COMPLEX_SMALL, 0.9, cvScalar(2,200,2), 1, CV_8UC3);
}
// az el�rt score-t elmenti file-ba
// megnyit�s ut�n megvizsg�lja, hogy nagyobb e a jelenleg el�rt,
// mint az el�z�, �s csak akkor menti el
void Score::Save() {
    fstream myfile;
    unsigned int tmpscore = 0;
    myfile.open("hiscore.sav", ios::in | ios::out);
    if(myfile.is_open()){
        myfile >> tmpscore;
        myfile.clear();
        myfile.seekg(0); // a f�jl pointert vissza�l�tjuk �r�shoz
        if(score > tmpscore)
            myfile << score;
    }
    else
        throw myexception("Exception: a fajl nem nyithato meg");
    myfile.close();
    cout << tmpscore << endl;
}
// Pontsz�mok beolvas�sa file-b�l
void Score::Read(){
    ifstream file;
    unsigned int savedScore;
    file.open("hiscore.sav", ios::in);
    if(file.is_open()){
        file >> savedScore;

        char* s = new char[20];
        sprintf(s, "Hi %d", savedScore);
        // sz�veg hossz�nak meghat�roz�sa
        Size textSize = getTextSize(s, FONT_HERSHEY_COMPLEX_SMALL, 0.9, 1, 0);
        // sz�veg ki�r�sa
        putText(Displayable::image, s, cvPoint(150 - (textSize.width / 2), 500),
        FONT_HERSHEY_COMPLEX_SMALL, 0.9, cvScalar(10, 10, 12), 1, CV_8UC3);
        delete s;
    } else
        throw;
}
