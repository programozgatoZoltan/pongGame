#ifndef SCORE_H
#define SCORE_H
#include "opencv2/core/core.hpp"
#include "displayable.h"
#include "area.h"
class Score:public Displayable{
private:
    unsigned int level;
    unsigned int score;
    unsigned int health;
    unsigned int bonus;
    unsigned int Ppoint; //j�t�kos pont
    unsigned int Mpoint; //g�p pontsz�m
protected:
    Mat Displayable::image;
public:
    Score();
    void LevelInc(); // level szint n�vel�s
    void Inc(int value); //pontsz�m n�vel�s
    void setHealth(int value);
    void setBonus(int value);
    void PlayerPointInc();
    void MachinePointInc();
    void resetScore(); //score null�z�sa
    // get fv.-ek
    int getLevel()const{return level;}
    int getScore()const{return score;}
    int getHelath()const{return health;}
    int getBonus()const{return bonus;}
    int getMachinePoint()const{return Mpoint;}
    int getPlayerPoint()const{return Ppoint;}
    void Draw();
    void gameOver();
    void win();
    void Start();
    void Save();
    void Read();
};
#endif // SCORE_H
