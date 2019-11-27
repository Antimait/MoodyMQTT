/**
 * Moody by Antima.in
 * 
 * Example of sketch for a Sensor Node based on the HC-SR04 
 * controlled by an ESP-8266 using the MoodyMQTT.h library.
 * 
 */

#include <MoodyMQTT.h>

#define WIFI         ""
#define PASSW        ""
#define BROKERADDR   ""

#define TYPE         "sensor"
#define GROUP        "movement"
#define DATATYPES    "['int']"

#define REFRESH      30000 //30 sec
#define EQUAL_THRESH 20

const int trigger = 0;
const int echo = 2;
const int room = 1;
int lastRefresh = 0;

long durata, distanza, lastdistanza;

NodeData nodeInfo = {TYPE, GROUP, DATATYPES};
MoodySensor sensor(&nodeInfo, room);

bool almostEquals(long x, long y) { 
  return abs(x-y) < EQUAL_THRESH;
}

void setup() {
  Serial.begin(9600);
  sensor.begin(WIFI, PASSW, BROKERADDR);
  
  //settiamo il funzionamento dei pin
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  //metto a LOW l'ingresso del PIN echo e del PIN trigger
  digitalWrite(echo, LOW);
  digitalWrite(trigger, LOW);

  //inizializzo le variabili
  durata = 0;
  distanza = 0;
  lastdistanza = 0;
}

void loop() {
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  durata = pulseIn(echo, HIGH);
  distanza = durata / 29 / 2;


  if(!almostEquals(distanza, lastdistanza)){
    Serial.print("Durata : ");
    Serial.print(durata);
    Serial.print(" - Distanza : "); 
    Serial.println(distanza);
    sensor.send(distanza);
    lastdistanza = distanza;
  }
  sensor.loop();
  delay(50);
}