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
        for(int i=0; i<5; i++){
            balls.push_back((new Ball(150,300)));
        }
        map<string, Tray*> tray;
        tray["machine"] =  new Tray(150,2,50,4); // gép ütője
        tray["player"] = new Tray(150,Palya.getHeight()-2,100,4); // alsó ütő
        Score score; // pontokat számító
        Debug debug; // konzolra írás
        Displayable::setImage(imread("background.jpg", CV_LOAD_IMAGE_COLOR)); // kezdő képernyő betöltés
        score.Read(); // eddigi pontszámok betöltése fájlból

        imshow("Pong Game", Displayable::getImage()); // kezdő képernyő megjelenítés
        setMouseCallback("Pong Game", CallBackFunc, &mouse); //elsö imshow() után kell tenni

        int pressedKey = 0; // leütött billentyű
        while(pressedKey != ENTER) // várunk az enter billentyűre
            pressedKey = waitKey(0);
        while(1){
            pressedKey = waitKey(10); //
            if(pressedKey == ESC) break; // kilépési feltétel

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
                        imshow("Pong Game",  Displayable::getImage()); //
                        break; // kilépünk a ciklusból, majd bezáródik a program
                    }
                }else{ // különben a gép szerzett ellenünk pontot
                    score.MachinePointInc(); // növeljük a gép pontjait
                    if(score.getMachinePoint() == 10){ // ha elérte a 10-et akkor vesztettük a meccset
                        printf("\nGame Over! Sorry!"); // konzolra írás
                        score.Draw(); // pontok kirajzolása
                        score.gameOver(); // "game over!" felirat kiírása
                        imshow("Pong Game",  Displayable::getImage()); // megjelenítünk
                        break; // kilépünk a ciklusból, majd bezáródik a program
                    }
                }
                balls.allsetXY(150,300); // labdák alaphelyzetbe állítása
                balls.allsetDirectionRandom(); // irányvektor random meghatározása
                balls.allrandomizeVelocity(); // sebesség random értékü lesz
                score.Draw(); // pontok kirajzolása
                balls.allDraw(); // labdák kirajzolása
                tray["machine"]->Draw();// ütők kirajzolása
                tray["player"]->Draw();
                score.Start(); // "Press key for start!" felirat kirajzolása
                imshow("Pong Game",  Displayable::getImage()); // megjelenítünk
                pressedKey = waitKey(0); // várunk a leütött billentyűre
                if(pressedKey == ESC) break; // kilépési feltétel
            }
            if(balls[0].hitWall()){
                score.Inc(9 + ((rand()%2))); // kapsz egy kis pontot random, ha szereted gyűjteni
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
    return 0;
}
