#include <ParkingShield.h>
ParkingShield shield;

/*
 * @brief Dies ist eine Neuimplementierung der Ampelschaltung für das Arduino UNO - Parking Schiled der Uni-Leipzig
 * Der Zustandsautomat liegt als grafische Übersicht bei. Dieser bildet die Spezifikation.
 * @author Michael Krause (1ux)
 *
*/

/*  Deklaration & Definition des Zustandsautomaten  */
enum Zustandsmenge {S0,S1,S2,S3};
typedef Zustandsmenge Zustandsmenge;                  //endliche Zustandsmenge

enum Alphabet {tick, reset};
typedef Alphabet Alphabet;                            //EingabeAlphabet

Zustandsmenge Ueberfuehrungsfunktion[4][2] =         //Zustandsüberführungsfunktion
  {{S1,S0},
  {S2,S0},
  {S3,S0},
  {S0,S0}};

Zustandsmenge Zustand = S0;                         //Startzustand


void Prozess(Alphabet Ereignis)
{
  Zustand = Ueberfuehrungsfunktion[Zustand][Ereignis];
}

void setup() 
{
  shield.setRepeatInterval(250);
}

void loop() 
{
  if(shield.buttonS1Pressed()) Prozess(tick);
  if(shield.buttonS2Pressed()) Prozess(reset);

  switch(Zustand)
  {
    case S0: 
              shield.setLed(ParkingShield::RED_LED,true);
              shield.setLed(ParkingShield::YELLOW_LED,false);
              shield.setLed(ParkingShield::GREEN_LED,false);
              break;

    case S1: 
              shield.setLed(ParkingShield::RED_LED,true);
              shield.setLed(ParkingShield::YELLOW_LED,true);
              shield.setLed(ParkingShield::GREEN_LED,false);
              break;

    case S2: 
              shield.setLed(ParkingShield::RED_LED,false);
              shield.setLed(ParkingShield::YELLOW_LED,false);
              shield.setLed(ParkingShield::GREEN_LED,true);
              break;

    case S3: 
              shield.setLed(ParkingShield::RED_LED,false);
              shield.setLed(ParkingShield::YELLOW_LED,true);
              shield.setLed(ParkingShield::GREEN_LED,false);
              break;
  }
}
