#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <exception>
#include <map>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "ball.h"
#include "tray.h"
#include "area.h"
#include "score.h"
#include "debug.h"
#include "mouse.h"
#include "myvector.h"
#include "myGUI.h"
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

int xGlobalMouse, yGlobalMouse; // egér pozíciója
enum states {BEGIN_WINDOW, SETTINGS, IN_GAME}state; // játék állapota
int BALL_NUMBERS = 3;
int MACHINE_TRAY_WIDTH = 20;
int PLAYER_TRAY_WIDTH = 40;

void CallBackFunc(int event, int x, int y, int flags, void* userdata){
    xGlobalMouse = x;
    yGlobalMouse = y;
    if(event == EVENT_LBUTTONUP){
        printf("x:%d, y:%d\n",x,y);
        if(state == BEGIN_WINDOW){
            if(x > 40 && x < 170 &&
               y > 150 && y < 180)
                state = IN_GAME;
            if(x > 40 && x < 170 &&
               y > 220 && y < 250)
                state = SETTINGS;
            if(x > 40 && x < 170 &&
               y > 290 && y < 320)
                exit(0);
        }
        if(state == SETTINGS){
            if(x > 250 && x < 280 &&
                y > 80 && y < 95){
                    if(BALL_NUMBERS < 50)
                        BALL_NUMBERS++;
                }
            if(x > 265 && x < 280 &&
                y > 95 && y < 110){
                    if(BALL_NUMBERS > 1)
                        BALL_NUMBERS--;
                }
            if(x > 250 && x < 280 &&
                y > 160 && y < 175){
                    if(MACHINE_TRAY_WIDTH < 100)
                        MACHINE_TRAY_WIDTH++;
                }
            if(x > 265 && x < 280 &&
                y > 175 && y < 190){
                    if(MACHINE_TRAY_WIDTH > 1)
                        MACHINE_TRAY_WIDTH--;
                }
            if(x > 250 && x < 280 &&
                y > 240 && y < 255){
                    if(PLAYER_TRAY_WIDTH < 100)
                        PLAYER_TRAY_WIDTH++;
                }
            if(x > 265 && x < 280 &&
                y > 255 && y < 270){
                    if(PLAYER_TRAY_WIDTH > 1)
                        PLAYER_TRAY_WIDTH--;
                }
            if(x > 40 && x < 170 &&
               y > 290 && y < 320)
                state = BEGIN_WINDOW;
        }
    }
}

int main()
{
    srand (time(NULL));
    Displayable::setImage(Mat::zeros(600, 300, CV_8UC3));
    Mouse mouse;
    // pálya létrehozás
    Area Palya;
    myvector<Ball> balls; // a labdák tárolója
    Score score; // pontokat számító
    Debug debug; // konzolra írás
    bool first = true;
        int pressedKey = 0; // leütött billentyű
        map<string, Tray*> tray;
    try{ // tedd vagy ne tedd, de sose próbáld!
        state = BEGIN_WINDOW;
        tray["machine"] =  new Tray(150,2,50,4); // gép ütője
        tray["player"] = new Tray(150,Palya.getHeight()-2,100,4); // alsó ütő
        while(1){
            pressedKey = waitKey(10); //

            if(state == BEGIN_WINDOW) {
                if(pressedKey == ESC) exit(0); // kilépési feltétel
                Displayable::setImage(imread("background.jpg", CV_LOAD_IMAGE_COLOR)); // kezdő képernyő betöltés
                score.Read(); // eddigi pontszámok betöltése fájlból
                // takaró négyszög
                rectangle(Displayable::getImage(), Point(40,175), Point(270,220), Scalar(232,217,154),-1);
                //menü gombok rajzolása
                Scalar buttonBackColor = Scalar(20, 58, 238);
                Scalar buttonTextColor = Scalar(44, 38, 11);
                createmyButton(Displayable::getImage(), "Play", 40, 150, buttonBackColor, buttonTextColor);
                createmyButton(Displayable::getImage(), "Settings", 40, 220, buttonBackColor, buttonTextColor);
                createmyButton(Displayable::getImage(), "Exit", 40, 290, buttonBackColor, buttonTextColor);

                imshow("Pong Game", Displayable::getImage()); // kezdő képernyő megjelenítés
                setMouseCallback("Pong Game", CallBackFunc, &state); //elsö imshow() után kell tenni
            }
            if(state == SETTINGS){
                first = true;
                Mat& img = Displayable::getImage();
                Scalar backColor = Scalar(222, 197, 103);
                img.setTo(backColor);
                Scalar buttonBackColor = Scalar(20, 58, 238);
                Scalar buttonTextColor = Scalar(44, 38, 11);
                createmyLabel(Displayable::getImage(), "Ball numbers:", 10, 40, buttonTextColor);
                createmyCounter(Displayable::getImage(), BALL_NUMBERS, 200, 80, buttonBackColor, buttonTextColor);

                createmyLabel(Displayable::getImage(), "Machine tray width:", 10, 120, buttonTextColor);
                createmyCounter(Displayable::getImage(), MACHINE_TRAY_WIDTH, 200, 160, buttonBackColor, buttonTextColor);

                createmyLabel(Displayable::getImage(), "Player tray width:", 10, 200, buttonTextColor);
                createmyCounter(Displayable::getImage(), PLAYER_TRAY_WIDTH, 200, 240, buttonBackColor, buttonTextColor);
                createmyButton(Displayable::getImage(), "Back", 40, 290, buttonBackColor, buttonTextColor);
                imshow("Pong Game", Displayable::getImage()); // kezdő képernyő megjelenítés
            }
            if(state == IN_GAME){
                if(first){ // ez csak egyszer fut le
                    balls.clear();
                    for(int i=0; i<BALL_NUMBERS; i++){ // beteszünk n db labdát a tárolóba
                        balls.push_back(new Ball(150, 300));
                    }
                    tray["machine"]->setWidth(300*MACHINE_TRAY_WIDTH/100);
                    tray["player"]->setWidth(300*PLAYER_TRAY_WIDTH/100);
                    first = false;
                }
                if(pressedKey == ESC) state = BEGIN_WINDOW;
                balls.allCompute(*tray["player"], *tray["machine"]);
                tray["machine"]->Compute(balls); // gép ütője helyezkedik

                // alsó ütőt az egérrel mozgathatjuk
                tray["player"]->setX(xGlobalMouse);
                // kirajzoló fv-ek.
                Palya.Draw();
                tray["machine"]->Draw();
                tray["player"]->Draw();
                score.Draw();
                //balls.allDrawdirection();
                balls.allDraw();
                imshow("Pong Game",  Displayable::getImage());
                if(balls.isOut()){
                    Palya.Draw();
                    cout << "Pontszerzes" << endl;
                    if(balls.mingetY() < 10){ // a a képernyő tetején ment ki
                        score.PlayerPointInc(); // növeljük a játékos pontjait
                        if(score.getPlayerPoint() == 10){ // ha elértük a 10-et, akkor megnyertük a meccset
                            score.Draw(); // pontok kirajzolása
                            score.win(); // a "win!" felirat kiírása
                            score.resetScore();
                            imshow("Pong Game",  Displayable::getImage()); //
                            waitKey(0);
                            state = BEGIN_WINDOW; // kilépünk a kezdőképernyőre
                        }
                    }else{ // különben a gép szerzett ellenünk pontot
                        score.MachinePointInc(); // növeljük a gép pontjait
                        if(score.getMachinePoint() == 10){ // ha elérte a 10-et akkor vesztettük a meccset
                            printf("\nGame Over! Sorry!"); // konzolra írás
                            score.Draw(); // pontok kirajzolása
                            score.gameOver(); // "game over!" felirat kiírása
                            score.resetScore();
                            imshow("Pong Game",  Displayable::getImage()); // megjelenítünk
                            waitKey(0);
                            state = BEGIN_WINDOW; // kilépünk a kezdőképernyőre
                        }
                    }
                    balls.allsetXY(150,300); // labdák alaphelyzetbe állítása
                    balls.allsetDirectionRandom(); // irányvektor random meghatározása
                    balls.allrandomizeVelocity(); // sebesség random értékü lesz
                    score.Draw(); // pontok kirajzolása
                    balls.allDraw(); // labdák kirajzolása
                    tray["machine"]->Draw();// ütők kirajzolása
                    tray["player"]->Draw();
                    score.Start(); // "Press key!" felirat kirajzolása
                    imshow("Pong Game",  Displayable::getImage()); // megjelenítünk
                    pressedKey = waitKey(0); // várunk a leütött billentyűre
                    if(pressedKey == ESC) state = BEGIN_WINDOW; // kilépési feltétel
                }
                if(balls[0].hitWall()){
                    score.Inc(9 + ((rand()%2))); // kapsz egy kis pontot random, ha szereted gyűjteni
                }
            }
        }
        score.Save(); // elmentjük a megszerzett pontjaid
    }catch(const myexception& e){ // nemvárt kivételeket(hibákat) kezelünk
        cerr << "myException: " << e.what() << endl; // kiírjuk a felhasználónak. úgyse tud vele mit kezdeni
        score.Save(); // mentjük ami menthető
    }catch(exception& e){
        cerr << "Exception: " << e.what() << endl;
        score.Save();
    }catch(...){
        cerr << "Undefined Exception!" << endl;
        score.Save();
    }
    printf("Destroy windows");
    destroyAllWindows();
    return 0;
}
