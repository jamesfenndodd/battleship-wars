#include <iostream>
#include <string>
#include <time.h>  
#include <stdlib.h>
#include "libarys/random.hpp"

using Random = effolkronium::random_static;
// this is the class to contatian the board this will hold all the info of the 2d array and then also provided the cord on the edges 
class Board{
  private:
    double boardx;
    double boardy;

  public:
   int board[80][80];
   double cord;
   int count=1;
   std::string aLine;
   std::string randomalp[9];
   int randomnum[9];

   Board(int x, int y){

     boardx = x;
     boardy = y;
   };
  // bordinit will fill the array full of 6 which is the number for water
   void boardinit(){
     char k;
      int l;
      for (int i=0; i<boardx; ++i){
        for(int j=0; j<boardy; ++j){
          board[i][j] = 6;
          // count = count + 1;
        }
      }
      for(k='A', l=0;l<boardx; ++k, ++l){
        std::string temp;
        randomalp[l] += k;
      }
      for (int i=0; i<boardy; ++i){
        cord=01;
          randomnum[i]=cord;
          cord++;
    }}; 

  // board print will output the board to the terminal 
   void boardprint(){
      aLine="";
      cord=01;
      char k;
      int l;
      for(k='A', l=0;l<boardx; ++k, ++l){
        std::string temp;
        temp += "\t";
        temp += k;
        aLine +=temp;
      }
      std::cout<<aLine<<"\n";
        for (int i=0; i<boardy; ++i){
          std::cout<<cord<<"\t";
          cord++;
          for(int j=0; j<boardx; ++j){
            if(board[i][j]==6){
              std::cout<<"⎚\t";
            }else if(board[i][j]==0){
              std::cout<<"🛩\t";
            }else if(board[i][j]==1){
              std::cout<<"🚢\t";
            }else if(board[i][j]==2){
              std::cout<<"⛴\t";
            }else if(board[i][j]==3){
              std::cout<<"🚋\t";
            }else if(board[i][j]==4){
              std::cout<<"🚤\t";
            }else if(board[i][j]==5){
              std::cout<<"💥\t";
            }else{std::cout<<board[i][j]<<"\t";}
          }
          std::cout<<"\n";
        }
  };
  //aplhtoindex is borrowed from mike and converts the letters to an array index
  int alphToIndex(std::string colref) {
    if(colref.length() == 1) {//deal with single letter value (A = 0, B = 2 .. Z = 25)
      return toupper(int(colref[0])) - 65; // 65 represents ASCII 'A' 'A' - 65 = 0
    } else if(colref.length() == 2) {//deal with pair values (AA = 26, BA = 52, CA = 78 .. ZZ = 701)
      return ((toupper(int(colref[1])) - 65) + (toupper(int(colref[0])) - 64) * 26); // -64 to get base 1 thus avoiding 0 * n = 0 issue
    }
    return -1; //no match 
  };
// cord out will output the current number in the place it asks for
  int cordout(int x, std::string y){
    int x1 = x-1;
    int y1;
    y1 = alphToIndex(y);
    return (board[x1][y1]);
  };
//cord chng will change the cord for a user
  bool cordchng(int x, std::string y, int num){
    int x1 = x-1;
    int y1;
    y1 = alphToIndex(y);
    board[x1][y1]=num;
    return true;
  };
//grid height will give me the height of the board
  int gridheight(){
    return boardx;
  };
//grid width will give me the width of the board
  int gridwidth(){
    return boardy;
  };
// wil give a random x number
  int ranx(){
    int a1;
    auto* a = Random::get( randomnum );
    a1 = *a;
    std::cout<<"randomnum"<<a1;
    return a1;
  };
//will give a random y num
  std::string rany(){
    srand((unsigned) time(0)); //initialize the random seed
    int RandIndex = rand() % 11;
    return randomalp[RandIndex];
  };
//place boat will place the boat for the user 
  bool placeboat(int x, std::string y, int boatid, int leng, int orientation){
    int y1 = alphToIndex(y);
    if (x>gridheight()|| y1>gridwidth()||x<0||y1<0){
      std::cout<<"invalid coordinate placement";
      return(false);
    }
    if(cordout(x,y)!=6){
      return (false);
    }
    if ((toupper(orientation))=='V'){
      int x1=x;
      int x2=x;
      for(int i=0; (i<leng); i++, x1++){
        if (cordout(x1,y)!=6){
          std::cout<<"invalid placment there is a ship in the way or your ship goes off the map";
          return (false);
        }
      };
      for(int i=0; i<leng; i++, x2++){
        if (cordout(x2,y)==6){
          cordchng(x2, y, boatid);
        };
      };
    };

    if ((toupper(orientation))=='H'){
      int x1=x;
      for(int i=0, k1=y[0]; i<leng; i++, k1++){
        std::string l1(1,k1);
        if (cordout(x,l1)!=6){
          std::cout<<"invalid placment there is a ship in the way or your ship goes off the map";
          return (false);
        }
      };
      for(int i=0, k1=y[0]; i<leng; i++, k1++){
        std::string l1(1,k1);
        if (cordout(x,l1)==6){
          cordchng(x, l1, boatid);
        };
      };
    };
    return (true);
  };
};