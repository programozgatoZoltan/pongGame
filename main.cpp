#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "ball.h"
#include "tray.h"
#include "area.h"
#include "score.h"
#include "debug.h"
#include "mouse.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <windows.h>
#include <conio.h>
#include <exception>
#include "myvector.h"
#define UPKEY 2490368
#define DOWNKEY 2621440
#define LEFTKEY 2424832
#define RIGHTKEY 2555904
#define ESC 27
#define PAUSE 32
#define ALT 100
#define ENTER 13
using namespace cv;
using namespace std;
using namespace myDebugger;

int xGlobalMouse, yGlobalMouse;

void CallBackFunc(int event, int x, int y, int flags, void* userdata){
    //printf("\nx : %d\ty : %d", x, y);
    xGlobalMouse = x;
    yGlobalMouse = y;
    Mouse* m = static_cast<Mouse *>(userdata);
    m->event = event;
    m->x = x;
    m->y = y;
    m->flags = flags;

    if(m->event == m->EVENT_LBUTTONUP&&m->x > 98 &&
                                    m->x < 193 &&
                                    m->y > 146 &&
                                    m->y < 180){

        cout << m->x <<", " <<m->y<<endl;
    }
}

int main()
{
    try{
        srand (time(NULL));
        Displayable::setImage(Mat::zeros(600, 300, CV_8UC3));
        Mouse mouse;
        // pálya létrehozás
        Area Palya;
        Ball Labda(150, 300); //Labda a 150, 300 koordinátán
        myvector<Ball> balls; // a labdák tárolója
        for(int i=0;i<1;i++){
            balls.push_back((new Ball(150,300)));
        }
        Tray t1(150,2,50,4); // gép ütője
        Tray t2(150,Palya.getHeight()-2,50,4); // alsó ütő
        Score score; // pontokat számító
        Debug debug;
        Displayable::setImage(imread("background.jpg", CV_LOAD_IMAGE_COLOR)); // kezdő képernyő betöltés
        score.Read(); // eddigi pontszámok betöltése fájlból



        imshow("Pong Game", Displayable::getImage()); // kezdő képernyő megjelenítés
        setMouseCallback("Pong Game", CallBackFunc, &mouse); //elsö imshow() után kell tenni

        int pressedKey = 0; // leütött billentyű
        while(pressedKey != ENTER) // várunk az enter billentyűre
            pressedKey = waitKey(0);
        Palya.Draw(); // kirajzolunk mindent
        //balls.Draw();//Labda.Draw();
        //for(int i=0; i < balls.size(); i++) balls[i].Draw();
        balls.allDraw();
        //balls[0].DrawDirection();//Labda.DrawDirection();
        //for(int i=0; i < balls.size(); i++) balls[i].DrawDirection();
        balls.allDrawdirection();
        t1.Draw();
        t2.Draw();
        score.Start(); // elindítjuk az eredményjelzőt

        imshow("Pong Game", Displayable::getImage()); // megjelenítünk
        //int pr = waitKey(0);
        //printf("\n%d\n", pr);

        debug.print(Labda); // kiírjuk a labda paramétereit

        while(1){
            pressedKey = waitKey(10); //
            if(pressedKey == ESC) break; // kilépési feltétel
            Palya.Draw();
            //balls[0].Compute(t2,t1);//Labda.Compute(t2,t1);
            //for(int i=0; i < balls.size(); i++) balls[i].Compute(t2,t1);
            balls.allCompute(t2,t1);
            //debug.print(Labda);
            t1.Compute(balls[0]);//t1.Compute(Labda);
            // alsó ütőt az egérrel mozgathatjuk
            t2.setX(xGlobalMouse);
            t1.Draw();

            t2.Draw();

            score.Draw();
            //balls[0].DrawDirection();//Labda.DrawDirection();
            //for(int i=0; i < balls.size(); i++) balls[i].DrawDirection();
            balls.allDrawdirection();
            //balls[0].Draw();//Labda.Draw();
            //for(int i=0; i < balls.size(); i++) balls[i].Draw();
            balls.allDraw();
            imshow("Pong Game",  Displayable::getImage());
            if(balls[0].isOut()){//Labda.isOut()){
                Palya.Draw();
                cout << "Pontszerzes" << endl;
                if(balls[0].getY() < 10){//if(Labda.getY() < 10){
                    if(score.getPlayerPoint() == 10){

                        score.Draw();
                        score.win();

                        imshow("Pong Game",  Displayable::getImage());
                        waitKey(0);
                        break;
                    }
                    score.PlayerPointInc();
                    score.Draw();
                    imshow("Pong Game",  Displayable::getImage());
                    waitKey(0);
                }else{
                    score.MachinePointInc();
                    if(score.getMachinePoint() == 10){
                        printf("\nGame Over! Sorry!");
                        score.Draw();
                        score.gameOver();
                        imshow("Pong Game",  Displayable::getImage());
                        waitKey(0);
                        break;
                    }
                }
                score.setHealth(-1);
                score.resetScore();
                //for(int i=0; i < balls.size(); i++) balls[i].setDirectionRandom();//Labda.setDirectionRandom();
                balls.allsetDirectionRandom();
                //for(int i=0; i < balls.size(); i++) balls[i].randomizeVelocity();//Labda.randomizeVelocity();
                balls.allrandomizeVelocity();
                //for(int i=0; i < balls.size(); i++) balls[i].setXY(150, 300);//Labda.setXY(150, 300);
                balls.allsetXY(150,300);
                score.Draw();
                //for(int i=0; i < balls.size(); i++) balls[i].Draw();
                balls.allDraw();
                t1.Draw();
                t2.Draw();
                score.Start();
                imshow("Pong Game",  Displayable::getImage());
                waitKey(0);
            }
            if(balls[0].hitWall()){//if(Labda.hitWall()){
                score.Inc(9 + ((rand()%2)));
            }
        }
        score.Save();
    }catch(const myexception& e){
        cerr << "Exception: " << e.what() << endl;
    }catch(...){
        cerr << "Undefined Exception!" << endl;
    }
    return 0;
}

