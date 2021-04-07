#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <time.h>  
#include <stdlib.h>
#include "libarys/ini.h"
#include "libarys/random.hpp"
#include "board.cpp"
#include "ship.cpp"
mINI::INIFile file("adaship_config.ini");
mINI::INIStructure config;

// the board x height
int boardx;
//the board y width
int boardy;
// hold for x 
int x;
// hold for the x pos to fire upon 
int xf;
// the num of ship we are looking at
int shipnum;
// the string hold for a y cord
std::string y;
// the string for a y cord to be fired upon
std::string yf;
// the int to hold the player currently making a move
int player;
// the hold for what direction the ship will face
char direc;
// the life count or slavo count for player
int salvocount;
// the life count or slavo count for player
int salvocount1;
// the string to hold who the winner is
std::string winner;

void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
};

// beneath is the code to fire upon a ship 
// the boradhit will be the board that will be fired upon 
// the ship it is the array of the ships on the board 
// x1 is the cord to fire upon
// y1 is the y cordinate to fire upon 
// playernum is the num of the player to fire the shot so i know who to take the points from 
Board fire(Board boardhit, Ship it[], int x1, std::string y1, int playernum) {
  int arynum;
  arynum = boardhit.cordout(x1,y1);
  if(0<=arynum&&arynum<=4){
    it[arynum].hit();
    std::cout<<"Hit 🎉\n";
    boardhit.cordchng(x1,y1,5);
  }else{
    std::cout<<"Miss 😞\n";
    }
  if(it[arynum].shiplife==0&&playernum==1){
      salvocount--;
    }else if(it[arynum].shiplife==0&&playernum==2){
      salvocount1--;
    }else{
    }
  return boardhit;
};



int random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
};


//place boat is to place the boats 
//board is the board to place the boats on 
// ship it is the array of ships to place 
// ai is a simple tick to check weather it should do it itself or let the user so it.
Board placeboat(Board board, Ship it[], int ai){
  for(int i=0; i<5; i++){
    bool suc=false;
    int leng = it[i].shipleng;
    if (ai ==0){
    do{
        for (;;) {
      std::cout<<"enter x:\n";
      if (std::cin >> x && (0<x&&x<10)){
          break;
      } else {
          std::cout << "Please enter a number that is 1 - 10" << std::endl;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      std::cout<<"\nenter y:";
      std::cin>>y;
      std::cout<<"\nenter orientation V for vertical H for horisontal:";
      std::cin>>direc;
      if(board.placeboat(x,y, i, leng, direc)==true){
        suc=true;
      }else{
        std::cout<<"\n invalid placemeant of boat or cords were outside the map\n";
        board.boardprint();
      }
    }while(suc!=true);}else if(ai==1){
      do{
      int x = random(0, 10);
      int tempy=boardy+65;
      char tempy2 = (char)random(65,tempy);
      std::string y = "";
      y += tempy2;
      int ran=random(1,2);
      if (ran==1){
        direc='v';
      }else if(ran==2){direc='h';};
      if(board.placeboat(x,y, i, leng, direc)==true){
        suc=true;
      }else{
        std::cout<<"\n invalid placemeant of boat or cords were outside the map\n";
        board.boardprint();
      }
    }while(suc!=true);
    }
    board.boardprint();
  };
  return board;
};


int main() {
  bool game = true;
  srand (time(NULL));
  Ship bt[5];
  Ship bt2[5];
  salvocount=5;
  salvocount1=5;
  shipnum =0;
  file.read(config);
  std::string& xintake = config["board"]["sizex"];
  boardx = std::stoi(xintake);
  std::string& yintake = config["board"]["sizey"];
  boardy = std::stoi(yintake);
  Board board1(boardx,boardy);
  Board board2(boardx,boardy);
  if (config.has("boat")){
    auto& collection = config["boat"];
    for(auto const& it2 : collection){
      auto const& key = it2.first;
      auto const& value = it2.second;
      bt[shipnum].Shipint(std::stoi(value), key);
      bt2[shipnum].Shipint(std::stoi(value), key);
      shipnum = shipnum +1;
    }
  }
  for (;;) {
    std::cout<<"give me a number of players 1 PvAI or 2 PvP:\n";
    if (std::cin >> player && (player==1||player==2)){
        break;
    } else {
        std::cout << "Please enter a one or two" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
  if (player==1){
    clear();
    board1.boardinit();
    board2.boardinit();
    board1.boardprint();
    board1 =placeboat(board1, bt, 0);
    clear();
    std::cout<<"time for the computer to place thier ships";
    board2 =placeboat(board2,bt2,1);
    clear();
    board1.boardprint();
    board2.boardprint();
    do{
    std::cout<<"player 1 turn to fire\n";
    for (;;) {
    std::cout<<"x cordinate for fire:\n";
    if (std::cin >> xf){
        break;
    } else {
        std::cout << "Please enter a valid number" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    std::cout<<"y cordinate for fire";
    std::cin>>yf;
    board2=fire(board2,bt2,xf,yf,2);
    board1.boardprint();
    board2.boardprint();
    do 
    {
      std::cout << '\n' << "Press a key to continue...";
    } while (std::cin.get() != '\n');
    std::cout<<"player 2 turn to fire\n";
    int xf = random(0, 10);
    int tempy=boardy+65;
    char tempy2 = (char)random(65,tempy);
    std::string yf = "";
    yf += tempy2;
    clear();
    board1=fire(board1,bt,xf,yf,1);
    board1.boardprint();
    board2.boardprint();
    do 
    {
      std::cout << '\n' << "Press a key to continue...";
    } while (std::cin.get() != '\n');
    char quit;
    std::cout<<"press q to quit";
    std::cin>>quit;

    if(salvocount==0){
      game=false;
      winner ="computer";
    }else if(salvocount1==0){
      game=false;
      winner ="player 1";
    }else if(quit=='q'){
      game=false;
      winner="player you quit but still";
    }
    std::cout<<"this is your amount of avalabile ships:"<<salvocount<<"\n";}while(game!=false);
    std::cout<<"well done player:"<<winner<<"you won!\n";
  }else if(player==2){
    clear();
    board1.boardinit();
    board2.boardinit();
    board1.boardprint();
    board1 =placeboat(board1, bt, 0);
    clear();
    std::cout<<"time for player 2 to place thier ships";
    board2 =placeboat(board2,bt2,0);
    clear();
    board1.boardprint();
    board2.boardprint();
    do{
    std::cout<<"player 1 turn to fire\n";
    for (;;) {
    std::cout<<"x cordinate for fire:\n";
    if (std::cin >> xf){
        break;
    } else {
        std::cout << "Please enter a valid number" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    std::cout<<"y cordinate for fire";
    std::cin>>yf;
    board2=fire(board2,bt2,xf,yf,2);
    board1.boardprint();
    board2.boardprint();
    do 
    {
      std::cout << '\n' << "Press a key to continue...";
    } while (std::cin.get() != '\n');
    std::cout<<"player 2 turn to fire\n";
    for (;;) {
    std::cout<<"x cordinate for fire:\n";
    if (std::cin >> xf){
        break;
    } else {
        std::cout << "Please enter a valid number" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    std::cout<<"y cordinate for fire";
    std::cin>>yf;
    board1=fire(board1,bt,xf,yf,1);
    board1.boardprint();
    board2.boardprint();
    do 
    {
      std::cout << '\n' << "Press a key to continue...";
    } while (std::cin.get() != '\n');
    do 
    {
      std::cout << '\n' << "Press a key to continue...";
    } while (std::cin.get() != '\n');
    char quit;
    std::cout<<"press q to quit";
    std::cin>>quit;

    if(salvocount==0){
      game=false;
      winner ="player 2";
    }else if(salvocount1==0){
      game=false;
      winner ="player 1";
    }else if(quit=='q'){
      game=false;
      winner="player you quit but still";
    }
    std::cout<<"this is your amount of avalabile ships:"<<salvocount<<"\n";}while(game!=false);
    std::cout<<"well done player:"<<winner<<"you won!\n";
}};