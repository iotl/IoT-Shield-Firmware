#ifndef ClassTrafficLights_h
#define ClassTrafficLights_h

#include <ParkingShield.h>

class ClassTrafficLights
{
    public: 

              enum Alphabet {tick, reset};
              typedef Alphabet Alphabet;                        //EingabeAlphabet

              ClassTrafficLights(ParkingShield &shield)
              {
                  this->Zustand = S0;         //Startzustand
                  this->_shield = shield;
                  _shield.setLed(ParkingShield::RED_LED,true);
                  _shield.sevenSeg.showNumber(1);
              }
              
              void Prozess(Alphabet Ereignis);


    private: 
              enum Zustandsmenge {S0,S1,S2,S3,S4};
              typedef Zustandsmenge Zustandsmenge;              //endliche Zustandsmenge


              Zustandsmenge Zustand;
              ParkingShield _shield;


              Zustandsmenge Ueberfuehrungsfunktion[5][2] =      //Zustandsüberführungsfunktion
              {{S1,S0}, //S0  (reset)
              {S2,S0},  //S1
              {S3,S0},  //S2
              {S4,S0}, //S3 (neu)
              {S1,S0}}; //S4 (verschoben, vorher S3)


      
};

#endif
