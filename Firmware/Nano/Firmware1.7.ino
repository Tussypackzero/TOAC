#define Firmware 1.7
#define stepperspeed 1200
#define speedtime 1000

#include <AccelStepper.h>
#include <EEPROM.h>
//              1/4 umdrehung = stepper.move(800);

#define pin12 12      //  Relais / Stepper pin   SHCP  / Pul
#define pin11 11      //  Relais / Stepper pin   STCP  / Dir        L
#define pin10 10      //  Relais / Stepper pin   SER   / Ena 

#define pin9 9        //  Relais / Stepper pin   SHCP  / Pul
#define pin8 8        //  Relais / Stepper pin   STCP  / Dir        C1
#define pin7 7        //  Relais / Stepper pin   SER   / Ena 

#define pin6 6        //  Relais / Stepper pin   SHCP  / Pul
#define pin5 5        //  Relais / Stepper pin   STCP  / Dir        C2
#define pin4 4        //  Relais / Stepper pin   SER   / Ena 

#define pin3 3        //  Servo   PWM-Signal  
#define pin2 2        //  Relais  Reset Relais

#define motorInterfaceType 1

int Serialport = 0;
int C1 = 1;
int C2 = 1;
int L = 1;
int CONN = 0;

int MotorL = 0;
int MotorC = 0;

unsigned long Lnew = 0;
unsigned long Lstep = 0;
unsigned long C1step = 0;
unsigned long C1new = 0;
unsigned long C2step = 0;
unsigned long C2new = 0;

unsigned long position = 0;
#define pos_ition 50

unsigned long verbindung = 0;
#define verb_indung 2000

AccelStepper stepperL = AccelStepper(motorInterfaceType, pin12, pin11, pin10);
AccelStepper stepperC1 = AccelStepper(motorInterfaceType, pin9, pin8, pin7);
AccelStepper stepperC2 = AccelStepper(motorInterfaceType, pin6, pin5, pin4);

void setup() {
  Serial.begin(4800);    // Selfport
  Serial.setTimeout(5);  // Selfport Timeout

  pinMode(12, OUTPUT);        //  Relais / Stepper pin
  pinMode(11, OUTPUT);        //  Relais / Stepper pin
  pinMode(10, OUTPUT);        //  Relais / Stepper pin

  pinMode(9, OUTPUT);         //  Relais / Stepper pin
  pinMode(8, OUTPUT);         //  Relais / Stepper pin
  pinMode(7, OUTPUT);         //  Relais / Stepper pin

  pinMode(6, OUTPUT);         //  Relais / Stepper pin
  pinMode(5, OUTPUT);         //  Relais / Stepper pin
  pinMode(4, OUTPUT);         //  Relais / Stepper pin

  pinMode(3, OUTPUT);         //  Servo    PWM Pin
  pinMode(2, OUTPUT);         //  Relais   Reset Pin

  pinMode(A0, OUTPUT);        //  Switch
  pinMode(A1, OUTPUT);        //  Switch
  pinMode(A2, INPUT_PULLUP);  //  Endschalter
  pinMode(A3, INPUT_PULLUP);  //  Endschalter
  pinMode(A4, INPUT_PULLUP);  //  EEprom
  pinMode(A5, INPUT_PULLUP);  //  EEprom
  pinMode(A6, INPUT_PULLUP);  //  PWR
  pinMode(A7, INPUT_PULLUP);  //  SWR
  
  stepperL.setMaxSpeed(stepperspeed);           // Geschwindigkeit pro Sekunde 
  stepperL.setAcceleration(speedtime);          // Beschleunigung in Schritten pro Sekunde.
  stepperC1.setMaxSpeed(stepperspeed);          // Geschwindigkeit pro Sekunde 
  stepperC1.setAcceleration(speedtime);         // Beschleunigung in Schritten pro Sekunde.
  stepperC2.setMaxSpeed(stepperspeed);          // Geschwindigkeit pro Sekunde 
  stepperC2.setAcceleration(speedtime);         // Beschleunigung in Schritten pro Sekunde.


  digitalWrite(10, HIGH);
  digitalWrite(7, HIGH);
  RS485();
}
void RS485() {
  if (Serial.available() > 0) {
    Serialport = Serial.read();
  }
  if (CONN == 0 & millis() - verbindung >= verb_indung) {  // Verbindungsaufbau
    verbindung = millis();
    millis();
    Serial.print('S');
    Serial.print(1);
    Serial.print('F');
  }
  if (Serialport == 'E') {
    Serialport = Serial.parseInt();
    if (Serial.read() == 'F') {
      if (Serialport == 0) {
        CONN = 1;
        delay(500);
        digitalWrite(10, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(4, HIGH);
        
        EEPROM.get(50, C1);
        EEPROM.get(60, C2);
        EEPROM.get(70, L);
        
        Serial.print('A');
        Serial.print(C1);
        Serial.print('F');
        delay(150);
        Serial.print('B');
        Serial.print(C2);
        Serial.print('F');
        delay(150);
        Serial.print('C');
        Serial.print(L);
        Serial.print('F');
        delay(150);
        Schrittmotor();  
        }
      if (Serialport == 1) {
        digitalWrite(10, LOW);
        digitalWrite(7, LOW);
        digitalWrite(4, LOW);
        Funktionstest();      
      }
    }
  }
  CONN = 0;
  RS485();
}

void Funktionstest() {
  delay(1000);
  stepperL.move(800);
  stepperL.runToPosition();
  delay(800);
  stepperL.move(-800);
  stepperL.runToPosition();
  delay(800);
  stepperC1.move(800);
  stepperC1.runToPosition();
  delay(800);
  stepperC1.move(-800);
  stepperC1.runToPosition();
  delay(800);
  stepperC2.move(800);
  stepperC2.runToPosition();
  delay(800);
  stepperC2.move(-800);
  stepperC2.runToPosition();
  delay(800);
  digitalWrite(10, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(4, HIGH);
  EEPROM.get(50, C1);
  EEPROM.get(60, C2);
  EEPROM.get(70, L);
  delay(100);
  Serial.print('A');
  Serial.print(C1);
  Serial.print('F');
  delay(100);
  Serial.print('B');
  Serial.print(C2);
  Serial.print('F');
  delay(100);
  Serial.print('C');
  Serial.print(L);
  Serial.print('F');
  Schrittmotor();
}

void Schrittmotor() {
  if (Serial.available() > 0) {
    Serialport = Serial.read();
  }
  if (Serialport == 'A') {  //      Stepper - C1
    Serialport = Serial.parseInt();
    if (Serial.read() == 'F') {
    if (C1 < Serialport) {
        C1++;
        digitalWrite(7, LOW);
        stepperC1.move(800);
        stepperC1.runToPosition();
        digitalWrite(7, HIGH);
        EEPROM.put(50, C1);
    }
    if (C1 > Serialport) {
        C1--;
        digitalWrite(7, LOW);
        stepperC1.move(-800);
        stepperC1.runToPosition();
        digitalWrite(7, HIGH);
        EEPROM.put(50, C1);
    }
      Serial.print('A');
      Serial.print(C1);
      Serial.print('F');
    }
  }
  if (Serialport == 'B') {  //      Stepper - C2
    Serialport = Serial.parseInt();
    if (Serial.read() == 'F') {
      if (C2 < Serialport) {
        C2++;
        delay(25);
        digitalWrite(4, LOW);
        stepperC2.move(800);
        stepperC2.runToPosition();
        digitalWrite(4, HIGH);
        EEPROM.put(60, C2);
    }
    if (C2 > Serialport) {
        C2--;
        delay(25);
        digitalWrite(4, LOW);
        stepperC2.move(-800);
        stepperC2.runToPosition();
        digitalWrite(4, HIGH);
        EEPROM.put(60, C2);
    }
      Serial.print('B');
      Serial.print(C2);
      Serial.print('F');
    }
  }
  if (Serialport == 'C') {  //      Stepper - L
    Serialport = Serial.parseInt();
    if (Serial.read() == 'F') {
      if (L < Serialport) {
        L++;
        digitalWrite(10, LOW);
        stepperL.move(800);
        stepperL.runToPosition();
        digitalWrite(10, HIGH);
        EEPROM.put(70, L);
      }
      if (L > Serialport) {
        L--;
        delay(25);        
        digitalWrite(10, LOW);
        stepperL.move(-800);
        stepperL.runToPosition();
        digitalWrite(10, HIGH);
        EEPROM.put(70, L);
      }
      Serial.print('C');
      Serial.print(L);
      Serial.print('F');
    }
  }

  if (Serialport == 'L') {  //      C1-Memory Stepp
    Serialport = Serial.parseInt();
    if (Serial.read() == 'F') {
      if (Serialport > C1) {
        C1new = C1 - Serialport;
        C1step = (800 * C1new);
        C1 = Serialport;
        delay(25);
        digitalWrite(7, LOW);
        stepperC1.move(-C1step);
        stepperC1.runToPosition();
        digitalWrite(7, HIGH);
        C1step = 0;
        C1new = 0;
        EEPROM.put(50, C1);
      }
      if (Serialport < C1) {
        C1new = Serialport - C1;
        C1step = 800 * C1new;
        C1 = Serialport;
        delay(15);
        digitalWrite(7, LOW);
        stepperC1.move(C1step);
        stepperC1.runToPosition();
        digitalWrite(7, HIGH);
        C1step = 0;
        C1new = 0;
        EEPROM.put(50, C1);
      }
      Serial.print('A');
      Serial.print(C1);
      Serial.print('F');
    }
  }
  if (Serialport == 'M') {  //      C2-Memory Stepp
    Serialport = Serial.parseInt();
    if (Serial.read() == 'F') {
      if (Serialport > C2) {
        C2new = C2 - Serialport;
        C2step = (800 * Lnew);
        C2 = Serialport;
        delay(25);
        digitalWrite(4, LOW);
        stepperC2.move(-Lstep);
        stepperC2.runToPosition();
        digitalWrite(4, HIGH);
        C2step = 0;
        C2new = 0;
        EEPROM.put(60, C2);
      }
      if (Serialport < C2) {
        C2new = Serialport - C2;
        C2step = 800 * C2new;
        C2 = Serialport;
        delay(25);
        digitalWrite(4, LOW);
        stepperC2.move(C2step);
        stepperC2.runToPosition();
        digitalWrite(4, HIGH);
        C2step = 0;
        C2new = 0;
        EEPROM.put(60, C2);
      }
      Serial.print('B');
      Serial.print(C2);
      Serial.print('F');
    }
  }
  if (Serialport == 'N') {  //      L-Memory Stepp
    Serialport = Serial.parseInt();
    if (Serial.read() == 'F') {
      if (Serialport > L) {
        Lnew = L - Serialport;
        Lstep = (800 * Lnew);
        L = Serialport;
        delay(25);
        digitalWrite(10, LOW);
        stepperL.move(-Lstep);
        stepperL.runToPosition();
        digitalWrite(10, HIGH);
        Lstep = 0;
        Lnew = 0;
        EEPROM.put(70, L);
      }
      if (Serialport < L) {
        Lnew = Serialport - L;
        Lstep = 800 * Lnew;
        L = Serialport;
        delay(15);
        digitalWrite(10, LOW);
        stepperL.move(Lstep);
        stepperL.runToPosition();
        digitalWrite(10, HIGH);
        Lstep = 0;
        Lnew = 0;
        EEPROM.put(70, L);
      }
      Serial.print('C');
      Serial.print(L);
      Serial.print('F');
    }
  }
  
  if (Serialport == 'P') {  //      C1 - 0 - Abgleich
    Serialport = Serial.parseInt();
    if (Serial.read() == 'F') {
      C1 =  Serialport;
      EEPROM.put(50, C1);
      Serial.print('A');
      Serial.print(C1);
      Serial.print('F');
    }
  }
  if (Serialport == 'Q') {  //      C2 - 0 - Abgleich
    Serialport = Serial.parseInt();
    if (Serial.read() == 'F') {
      C2 =  Serialport;
      EEPROM.put(60, C2);
      Serial.print('B');
      Serial.print(C2);
      Serial.print('F');
    }
  }
  if (Serialport == 'R') {  //      L - 0 - Abgleich
    Serialport = Serial.parseInt();
    if (Serial.read() == 'F') {
      L =  Serialport;
      EEPROM.put(70, L);
      Serial.print('C');
      Serial.print(L);
      Serial.print('F');
    }
  }

  if (Serialport == 'E') {
    Serialport = Serial.parseInt();
    if (Serial.read() == 'F') {
      if (Serialport == 9) {  // OK
        RS485();
      }
    }
  }
  Schrittmotor();
}

void Relais() {
  
  Relais();
}

void loop() {
  RS485();
}
