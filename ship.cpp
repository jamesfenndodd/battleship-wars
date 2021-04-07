#include <iostream>
#include <string>
#include <stdlib.h>

class Ship{
  private:

  public:
    int shipleng;
    int shiplife;
    std::string shipName;
// will fill the ship with relervant information
  void Shipint(int leng, std::string name){
    shipleng = leng;
    shiplife = leng;
    shipName = name;
  };
//hit will remove one of the ships lifes
  void hit(){
    shiplife = shiplife-1;
  };

};