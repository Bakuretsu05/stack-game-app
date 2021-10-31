#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <cstdlib>
using namespace std;
enum direction{LEFT, RIGHT};

bool gameover, kbHit;
int x, y, prevX;
vector<vector<int>> boxXY;
direction dir;

// playfield
const int width = 25;
const int height = 36;

// box height and width
int boxWidth = 5;
int boxHeight = 3;

// data of placed box is stored here (3 dimensional)
vector<vector<vector<int>>> dataXY;

// function to get the individual  box's O's coordinates
vector<vector<int>> getBoxC(int xPos, int yPos){
    vector<vector<int>> output(boxWidth*boxHeight);
    int ite = 0;
    for(int YPos = boxHeight-1; YPos >= 0; YPos--){
        for(int XPos = 0; XPos < boxWidth; XPos++){
            output[ite].push_back(XPos + xPos);
            output[ite].push_back(YPos + yPos);
            ite++;
        }
    }
    return output;
}

void setup(){
    gameover = false;
    dir = LEFT;
    x = 1;
    y = 1;
    prevX = 0;
    boxXY = getBoxC(x, y);
    kbHit = false;
}

void draw(){
    system("cls");
    for(int iY = 0; iY <= height+1; iY++){
        for(int iX = 0; iX <= width; iX++){
            if(iX == 0 || iX == width || iY == 0 || iY == height+1) cout << "X"; // border

            else{
                bool printed = false;
                for(int i = 0; i < boxXY.size(); i++){
                    if(iX == boxXY[i][0] && iY == boxXY[i][1]){
                        cout << "O";
                        printed = true;
                        break;
                    }
                }
                for(int i = 0; i < dataXY.size(); i++){
                    for(int j = 0; j < dataXY[i].size(); j++){
                        if(iX == dataXY[i][j][0] && iY == dataXY[i][j][1]){
                            cout << "O";
                            printed = true;
                            break;
                        }   
                    }
                }
                if(!printed) cout << " ";
            }
        }
        cout << endl;
    }
}

void input(){
    if(_kbhit()){
        kbHit = true;
        _getch(); // to reset _kbhit()
    }
}

void logic(){
    if(kbHit){
        if(!dataXY.empty()) boxWidth -= abs(x - prevX);

        if(prevX > x){
            x += prevX - x;
            boxXY = getBoxC(x, y);
        }
        else boxXY = getBoxC(x, y);

        dataXY.push_back(boxXY);
        prevX = x;
        y += boxHeight;
        kbHit = false;
    }

    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }

    if(boxWidth <= 0) gameover = true;
    if(y >= height) gameover = true;
    if(x <= 1) dir = RIGHT;
    else if(x+boxWidth >= width) dir = LEFT;

    boxXY = getBoxC(x, y);
}

int main(){
    setup();
    while(!gameover){
        draw();
        input();
        logic();
        Sleep(100);
    }
    cout << "You Won!!!" << endl;
    system("pause");
}