#ifndef ClassTrafficLights_h
#define ClassTrafficLights_h

#include <ParkingShield.h>

class ClassTrafficLights
{
    public: 

              enum Zustandsmenge {S0,S1,S2,S3};
              typedef Zustandsmenge Zustandsmenge;              //endliche Zustandsmenge

              enum Alphabet {tick, reset};
              typedef Alphabet Alphabet;                        //EingabeAlphabet

              ClassTrafficLights(ParkingShield &shield)
              {
                  this->Zustand = S0;         //Startzustand
                  this->_shield = shield;
                  _shield.setLed(ParkingShield::RED_LED,true);
              }
              
              void Prozess(Alphabet Ereignis);


    private: 

              Zustandsmenge Zustand;
              ParkingShield _shield;

              Zustandsmenge Ueberfuehrungsfunktion[4][2] =      //Zustandsüberführungsfunktion
              {{S1,S0},
              {S2,S0},
              {S3,S0},
              {S0,S0}};

      
};

#endif
