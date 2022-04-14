// Einstellbare Variablen 
#define Call "DO4KGT"


#define Firmware_v  "1.7"
#define C1ref   300     //  Start Kapazität C1  X  pF
#define C1step  15      //  Stepp Kapazität C1  X  pF
#define C2ref   300     //  Start Kapazität C2  X  pF
#define C2step  15      //  Stepp Kapazität C2  X  pF
#define Lref    125    //  Anfangs Induktivität  0,25  µH
#define Lstep   125    //  Stepp Induktivität 0,125 µH

#define trx_adress  0x94   // TRX CI-V Adresse
#define pc_adress   0xE0   // Controller Adresse

#include <EEPROM.h>
#include <Nextion.h>

byte NexT[3] = {255,255,255};

NexButton a0 = NexButton(0, 3, "a0");           //  DEBUG
NexButton a1 = NexButton(0, 4, "a1");           //  Restart Tuner
//___________________________________________________________________________________Seite 1
NexButton b0 = NexButton(1, 1, "b0");           //  UP-C1
NexButton b1 = NexButton(1, 2, "b1");           //  Down-C1
NexButton b2 = NexButton(1, 3, "b2");           //  UP-L
NexButton b3 = NexButton(1, 4, "b3");           //  Down-L
NexButton b4 = NexButton(1, 5, "b4");           //  UP-C2
NexButton b5 = NexButton(1, 6, "b5");           //  Down-C2
NexButton b6 = NexButton(1, 22, "b6");          //  Config
NexButton b7 = NexButton(1, 24, "b7");          //  SAVE

NexDSButton bt0 = NexDSButton(1, 7, "bt0");      //  160m
NexDSButton bt1 = NexDSButton(1, 8, "bt1");      //  80m
NexDSButton bt2 = NexDSButton(1, 9, "bt2");      //  60m
NexDSButton bt3 = NexDSButton(1, 10, "bt3");     //  40m
NexDSButton bt4 = NexDSButton(1, 11, "bt4");     //  30m
NexDSButton bt5 = NexDSButton(1, 12, "bt5");     //  20m
NexDSButton bt6 = NexDSButton(1, 13, "bt6");     //  17m
NexDSButton bt7 = NexDSButton(1, 14, "bt7");     //  15m
NexDSButton bt8 = NexDSButton(1, 15, "bt8");     //  12m
NexDSButton bt9 = NexDSButton(1, 16, "bt9");     //  10m
NexDSButton bt10 = NexDSButton(1, 17, "bt10");   //  6m

NexDSButton bt11 = NexDSButton(1, 18, "bt11");   //  out of band
NexDSButton bt12 = NexDSButton(1, 20, "bt12");   //  Lock
NexDSButton bt13 = NexDSButton(1, 23, "bt13");   //  Auto/Manual
NexDSButton bt14 = NexDSButton(1, 25, "bt14");   //  High/LOW
//___________________________________________________________________________________Seite 2
NexButton c0 = NexButton(2, 1, "c0");           //  UP-C1
NexButton c1 = NexButton(2, 2, "c1");           //  Down-C1
NexButton c2 = NexButton(2, 3, "c2");           //  UP-L
NexButton c3 = NexButton(2, 4, "c3");           //  Down-L
NexButton c4 = NexButton(2, 5, "c4");           //  UP-C2
NexButton c5 = NexButton(2, 6, "c5");           //  Down-C2
NexButton c6 = NexButton(2, 34, "c6");          //  Config
NexButton c7 = NexButton(2, 26, "c7");          //  SAVE

NexDSButton ct0 = NexDSButton(2, 10, "ct0");     //  160m
NexDSButton ct1 = NexDSButton(2, 11, "ct1");     //  80m
NexDSButton ct2 = NexDSButton(2, 12, "ct2");     //  60m
NexDSButton ct3 = NexDSButton(2, 13, "ct3");     //  40m
NexDSButton ct4 = NexDSButton(2, 14, "ct4");     //  30m
NexDSButton ct5 = NexDSButton(2, 15, "ct5");     //  20m
NexDSButton ct6 = NexDSButton(2, 16, "ct6");     //  17m
NexDSButton ct7 = NexDSButton(2, 17, "ct7");     //  15m
NexDSButton ct8 = NexDSButton(2, 18, "ct8");     //  12m
NexDSButton ct9 = NexDSButton(2, 19, "ct9");     //  10m
NexDSButton ct10 = NexDSButton(2, 20, "ct10");   //  6m
NexDSButton ct11 = NexDSButton(2, 21, "ct11");   //  out of band

NexDSButton ct12 = NexDSButton(2, 23, "ct12");   //  Lock
NexDSButton ct13 = NexDSButton(2, 26, "ct13");   //  Auto/Manual
NexDSButton ct14 = NexDSButton(2, 28, "ct14");   //  High/LOW
//___________________________________________________________________________________Setup
NexDSButton bs0 = NexDSButton(3, 6, "bs0");      //  Baud
NexDSButton bs1 = NexDSButton(3, 7, "bs1");      //  Baud
NexDSButton bs2 = NexDSButton(3, 8, "bs2");      //  Baud
NexDSButton bs3 = NexDSButton(3, 9, "bs3");      //  Baud
NexDSButton bs4 = NexDSButton(3, 10, "bs4");     //  Baud
NexDSButton bs5 = NexDSButton(3, 11, "bs5");     //  Baud
NexDSButton bs6 = NexDSButton(3, 12, "bs6");     //  Baud
NexDSButton bs7 = NexDSButton(3, 13, "bs7");     //  Baud
NexDSButton bs8 = NexDSButton(3, 14, "bs8");     //  Baud
NexDSButton bs9 = NexDSButton(3, 15, "bs9");     //  Baud
NexDSButton bs10 = NexDSButton(3, 18, "bs10");   //  2 Bauteile
NexDSButton bs11 = NexDSButton(3, 19, "bs11");   //  3 Bauteile 
NexDSButton bs12 = NexDSButton(3, 20, "bs12");   //  Funktionstest Aktiviert
NexDSButton bs13 = NexDSButton(3, 21, "bs13");   //  Funktionstest Deaktiviert
//___________________________________________________________________________________Config
NexButton q0 = NexButton(3,  1, "q0");           //  Back Tuner
NexButton q1 = NexButton(3, 16, "q1");           //  Tuner Abgleich
NexButton q3 = NexButton(4,  1, "q3");           //  Tuner Abgleich

NexButton n0 = NexButton(4, 4, "n0");            //  C1 Abgleich
NexButton n1 = NexButton(4, 5, "n1");            //  C2 Abgleich
NexButton n2 = NexButton(4, 6, "n2");            //  L 0 Abgleoch
NexButton n3 = NexButton(4, 7, "n3");            //  Eeprom Löschen
NexButton n4 = NexButton(4, 8, "n4");            //  Eeprom Löschen
NexButton n5 = NexButton(4, 9, "n5");            //  Reset Tuner

NexTouch *nex_listen_Display1[] = {
  &a0, &a1,
  &b0, &b1, &b2, &b3, &b4, &b5, &b6, &b7,
  &bt0, &bt1, &bt2, &bt3, &bt4, &bt5, &bt6, &bt7, &bt8, &bt9, &bt10, &bt11, &bt12, &bt13, &bt14, 
  NULL  // String terminated
};

NexTouch *nex_listen_Display2[] = {
  &a0, &a1, 
  &c0, &c1, &c2, &c3, &c4, &c5, &c6, &c7, 
  &ct0, &ct1, &ct2, &ct3, &ct4, &ct5, &ct6, &ct7, &ct8, &ct9, &ct10, &ct11, &ct12, &ct13, &ct14,
  NULL  // String terminated
};

NexTouch *nex_listen_Config[] = {
  &bs0, &bs1, &bs2, &bs3, &bs4, &bs5, &bs6, &bs7, &bs8, &bs9, &bs10, &bs11, &bs12, &bs13,
  &n0, &n1, &n2, &n3, &n4, &n5, 
  &q0, &q1, &q3,
  NULL  // String terminated
};

NexTouch *nex_lock_list[] = {
  &bt12,
  &ct12,
  NULL  // String terminated
};

unsigned long Tunerrestart = 0;
#define Tuner_delay 2500

unsigned long Tunerdelay = 0;
#define Tuner_restart 1000

unsigned long Bandtrx = 0;
#define Band_trx 500

unsigned long Catfre = 0;
#define Cat_fre 400

unsigned long reset = 0;
#define re_set 10000

// Kommunikation
int Serialport0;      // Selfport
int Serialport1;      // Display
int TRXCAT[10];       // TRX
int Serialport3;      // Tuner
int i;                // 
int tv; // Tunerverbindung
int cv; // Catverbindung
int tm; // Tuner Model
int ft; // Funktionstest
int bm; // Bauteil Menge
int unsigned long MHZ = 0;
int unsigned long KHZ = 0;
int unsigned long HZ = 0;
int unsigned long QRG = 0;
int unsigned long QRGcomp = 0;
int unsigned long Banddec = 0;
int unsigned long FREQWechsel = 0;

// Variablen
int C1 = 1;         //  Variable Kapazität
int C2 = 1;         //  Variable Kapazität
int  L = 1;         //  Variable Induktivität 
int  Z = 0;         //  High/Low Umschaltung

int unsigned long  LD = 0;        //  Errechnete Induktivität 
int unsigned long CD1 = 0;        //  Errechnete Kapazität
int unsigned long CD2 = 0;        //  Errechnete Kapazität

int Lock = 0;       //  Sperrung Display

int      Ptt = 0;        //  Sende/Empfangs umschaltung 
int     Auto = 0;       //  Auto einstellung
int   Manual = 1;     //  Manual-Automatik Umschaltung  
int     Band = 0;       //  Banddekoder 
int Diagnose = 1;   //  Diagnoseport
int    Setup = 0;
int  Restart = 0;

void setup() {
 
  tv = EEPROM.read(900);    // tv Tunerverbindung
  cv = EEPROM.read(902);    // cv Catverbindung
  tm = EEPROM.read(904);    // tm Tuner Model

  Serial.begin(9600);       // Selfport
  Serial1.begin(57600);     // Display
  Serial2.begin(9600);      // TRX
  Serial3.begin(4800);      // Tuner
  Serial3.setTimeout(5);


  pinMode(A12, OUTPUT);     //  Buzzer Out
  pinMode(A13, INPUT);
  pinMode(A14, INPUT);
  pinMode(A15, INPUT);


  pinMode(2, OUTPUT);        //  PTT Out
  pinMode(5, OUTPUT);        //  Reset
  pinMode(6, INPUT_PULLUP);  //  PTT IN
  pinMode(7, OUTPUT);        //  PTT IN

  digitalWrite(2, LOW);      //  PTT OUT
  digitalWrite(5, LOW);      //  Reset OUT
  digitalWrite(7, LOW);      //  PTT IN

  a0.attachPop(a0PopCallback);
  a1.attachPop(a1PopCallback);

  b0.attachPop(b0PopCallback);
  b1.attachPop(b1PopCallback);
  b2.attachPop(b2PopCallback);
  b3.attachPop(b3PopCallback);
  b4.attachPop(b4PopCallback);
  b5.attachPop(b5PopCallback);
  b6.attachPop(b6PopCallback);
  b7.attachPop(b7PopCallback);

  c0.attachPop(b0PopCallback);
  c1.attachPop(b1PopCallback);
  c2.attachPop(b2PopCallback);
  c3.attachPop(b3PopCallback);
  c4.attachPop(b4PopCallback);
  c5.attachPop(b5PopCallback);
  c6.attachPop(b6PopCallback);
  c7.attachPop(b7PopCallback);

  ct0.attachPop(bt0PopCallback);
  ct1.attachPop(bt1PopCallback);
  ct2.attachPop(bt2PopCallback);
  ct3.attachPop(bt3PopCallback);
  ct4.attachPop(bt4PopCallback);
  ct5.attachPop(bt5PopCallback);
  ct6.attachPop(bt6PopCallback);
  ct7.attachPop(bt7PopCallback);
  ct8.attachPop(bt8PopCallback);
  ct9.attachPop(bt9PopCallback);
  ct10.attachPop(bt10PopCallback);
  ct11.attachPop(bt11PopCallback);
  ct12.attachPop(bt12PopCallback);
  ct13.attachPop(bt13PopCallback);
  ct14.attachPop(bt14PopCallback);

  bt0.attachPop(bt0PopCallback);
  bt1.attachPop(bt1PopCallback);
  bt2.attachPop(bt2PopCallback);
  bt3.attachPop(bt3PopCallback);
  bt4.attachPop(bt4PopCallback);
  bt5.attachPop(bt5PopCallback);
  bt6.attachPop(bt6PopCallback);
  bt7.attachPop(bt7PopCallback);
  bt8.attachPop(bt8PopCallback);
  bt9.attachPop(bt9PopCallback);
  bt10.attachPop(bt10PopCallback);
  bt11.attachPop(bt11PopCallback);
  bt12.attachPop(bt12PopCallback);
  bt13.attachPop(bt13PopCallback);
  bt14.attachPop(bt14PopCallback);

  bs0.attachPop(bs0PopCallback);
  bs1.attachPop(bs1PopCallback);

  bs2.attachPop(bs2PopCallback);
  bs3.attachPop(bs3PopCallback);
  bs4.attachPop(bs4PopCallback);
  bs5.attachPop(bs5PopCallback);
  bs6.attachPop(bs6PopCallback);
  bs7.attachPop(bs7PopCallback);
  bs8.attachPop(bs8PopCallback);
  bs9.attachPop(bs9PopCallback);
  bs10.attachPop(bs10PopCallback);
  bs11.attachPop(bs11PopCallback);
  bs12.attachPop(bs12PopCallback);
  bs13.attachPop(bs13PopCallback);

  q0.attachPop(q0PopCallback);
  q1.attachPop(q1PopCallback);
  q3.attachPop(q0PopCallback);

  n0.attachPop(n0PopCallback);
  n1.attachPop(n1PopCallback);
  n2.attachPop(n2PopCallback);
  n3.attachPop(n3PopCallback);
  n4.attachPop(n4PopCallback);
  n5.attachPop(n5PopCallback);

  
  Serial1.print("page 0");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);   
  Serial1.print("t0.txt=");
  Serial1.write(0x22);
  Serial1.print(Call);
  Serial1.print("   Tuner");
  Serial1.write(0x22);
  Serial1.write(NexT, 3);

  Serial1.print("t2.txt=");
  Serial1.write(0x22);
  Serial1.print("Firmware ");
  Serial1.print(Firmware_v);
  Serial1.write(0x22);
  Serial1.write(NexT, 3);
  Restart = 0;
  RS485();
}

void RS485() {
  ft = EEPROM.read(906);    // Funtionstest
  bm = EEPROM.read(908);    // Bauteile
  if (Serial.available()  > 0) {              //    Diagnose-Serial
    Serialport0 = Serial.read();
    //Serial.print(Serialport0);
  }
  if (Serial1.available() > 0) {              //    Display-Serial
    char Serialport1 = Serial1.read();
    //Serial.print(Serialport1);
  }
  for (i = 0; i < 8; i++) {                   //    TRX-Serial
    if (Serial2.available() > 0) {
      TRXCAT[i] = Serial2.read();
    }
  }
  if (Serial3.available() > 0) {              //    Tuner-Serial
    Serialport3 = Serial3.read();
    Serial.print(Serialport3);
  }
  if (millis() - reset >= re_set) {  // Verbindungsaufbau
    reset = millis();
    millis();
    Serial3.print('E');
    Serial3.print(8);
    Serial3.println('F');
  }
  if (Serialport3 == 'S') { //    L
    Serialport3 = Serial3.parseInt();
    if (Serial3.read() == 'F') {
      if (Serialport3 == 1) {
        Serial1.print("t1.txt=");
        Serial1.write(0x22);
        Serial1.print("Verbindung OK");
        Serial1.write(0x22);
        Serial1.write(NexT, 3);
        delay(2000);
        if (bm == 0) {         //    2 Bauteile
          if (ft == 0) {
            Serial3.print('E');
            Serial3.print(0);
            Serial3.print('F');
            Serial1.print("page 1");
            Serial1.write(0xff);
            Serial1.write(0xff);
            Serial1.write(0xff);
            Serial1.print("t0.txt=");
            Serial1.write(0x22);
            Serial1.print(C1);
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Serial1.print("t1.txt=");
            Serial1.write(0x22);
            Serial1.print(L);
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Display();
          } else {
            Serial1.print("t0.txt=");
            Serial1.write(0x22);
            Serial1.print("  Selbsttest  ");
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Serial1.print("t1.txt=");
            Serial1.write(0x22);
            Serial1.print("L Motor   /   C Motor ");
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Serial3.print('E');
            Serial3.print(0);
            Serial3.print('F');

            delay(11000);

            Serial1.print("page 1");
            Serial1.write(0xff);
            Serial1.write(0xff);
            Serial1.write(0xff);
            Serial1.print("t0.txt=");
            Serial1.write(0x22);
            Serial1.print(C1);
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Serial1.print("t1.txt=");
            Serial1.write(0x22);
            Serial1.print(L);
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Display();
          }
        }
        else if (bm == 1) {   //    3 Bauteile
          if (ft == 0) {
            Serial3.print('E');
            Serial3.print(0);
            Serial3.print('F');
            Serial1.print("page 2");
            Serial1.write(0xff);
            Serial1.write(0xff);
            Serial1.write(0xff);
            Serial1.print("t0.txt=");
            Serial1.write(0x22);
            Serial1.print(C1);
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Serial1.print("t1.txt=");
            Serial1.write(0x22);
            Serial1.print(L);
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Serial1.print("t2.txt=");
            Serial1.write(0x22);
            Serial1.print(C2);
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Display();
          } else {
            Serial1.print("t0.txt=");
            Serial1.write(0x22);
            Serial1.print("  Selbsttest  ");
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Serial1.print("t1.txt=");
            Serial1.write(0x22);
            Serial1.print("C Motor / L Motor / C Motor");
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Serial3.print('E');
            Serial3.print(0);
            Serial3.print('F');

            delay(5000);

            Serial1.print("page 2");
            Serial1.write(0xff);
            Serial1.write(0xff);
            Serial1.write(0xff);
            Serial1.print("t0.txt=");
            Serial1.write(0x22);
            Serial1.print(C1);
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Serial1.print("t1.txt=");
            Serial1.write(0x22);
            Serial1.print(L);
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Serial1.print("t2.txt=");
            Serial1.write(0x22);
            Serial1.print(C2);
            Serial1.write(0x22);
            Serial1.write(NexT, 3);
            Display();
          }
        }
        else if (bm >= 2) {
          Serial1.print("page 3");
          Serial1.write(0xff);
          Serial1.write(0xff);
          Serial1.write(0xff);

          Serial1.print("t0.txt=");
          Serial1.write(0x22);
          Serial1.print(Call);
          Serial1.print("   Tuner   Setup");
          Serial1.write(0x22);
          Serial1.write(NexT, 3);

          Serial1.print("t2.txt=");
          Serial1.write(0x22);
          Serial1.print("Firmware ");
          Serial1.print(Firmware_v);
          Serial1.write(0x22);
          Serial1.write(NexT, 3);
          delay(150);

          Setup = 1;

          Config();
        }
      }
    }
  }
  if (millis() - Tunerrestart >= Tuner_restart) {         //    Tuner Restart,
    Tunerrestart = millis();
    millis();
    Serial3.print('E');
    Serial3.print(9);
    Serial3.print('F');
  }
  nexLoop(nex_listen_Display1);
  RS485();
}

void Display() {
  ft = EEPROM.read(906);    // Funtionstest
  bm = EEPROM.read(908);    // Bauteile
  FREQWechsel = QRGcomp;
  Auto = 0;  
  if (Serial.available()  > 0) {              //    Diagnose-Serial
    Serialport0 = Serial.read();
    //Serial.print(Serialport0);
  }
  if (Serial1.available() > 0) {              //    Display-Serial
    char Serialport1 = Serial1.read();
    //Serial.print(Serialport1);
  }
  for (i = 0; i < 8; i++) {                   //    TRX-Serial
    if (Serial2.available() > 0) {
      TRXCAT[i] = Serial2.read();
    }
  }
  if (Serial3.available() > 0) {              //    Tuner-Serial
    Serialport3 = Serial3.read();
    Serial.print(Serialport3);
  }
  if (Serialport3 == 'A') {                   //    Abgleich C1
    Serialport3 = Serial3.parseInt();
    if (Serial3.read() == 'F') {
      C1 = Serialport3;
      Serial1.print("t0.txt=");
      Serial1.write(0x22);
      Serial1.print(C1);
      Serial1.write(0x22);
      Serial1.write(NexT, 3);

      CD1 = (C1ref + C1 * C1step);
      Serial1.print("t8.txt=");
      Serial1.write(0x22);
      Serial1.print(CD1 / 10);
      Serial1.print(".");
      Serial1.print(CD1 % 10);
      Serial1.print(" pF");
      Serial1.write(0x22);
      Serial1.write(NexT, 3);
    }
  }
  if (Serialport3 == 'B') {                   //    Abgleich C2
    Serialport3 = Serial3.parseInt();
    if (Serial3.read() == 'F') {
      C2 = Serialport3;
      Serial1.print("t2.txt=");
      Serial1.write(0x22);
      Serial1.print(C2);
      Serial1.write(0x22);
      Serial1.write(NexT, 3);

      CD2 = (C2ref + C2 * C2step);
      
      Serial1.print("t10.txt=");
      Serial1.write(0x22);
      Serial1.print(CD2 / 10);
      Serial1.print(".");
      Serial1.print(CD2 % 10);
      Serial1.print(" pF");
      Serial1.write(0x22);
      Serial1.write(NexT, 3);
    }
  }
  if (Serialport3 == 'C') {                   //    Abgleich L
    Serialport3 = Serial3.parseInt();
    if (Serial3.read() == 'F') {
      L = Serialport3;
      Serial1.print("t1.txt=");
      Serial1.write(0x22);
      Serial1.print(L);
      Serial1.write(0x22);
      Serial1.write(NexT, 3);

      LD = (Lref + L * Lstep);
      Serial1.print("t6.txt=");
      Serial1.write(0x22);
      Serial1.print(LD / 1000);
      Serial1.print(".");
      Serial1.print(LD % 1000);
      Serial1.print(" uH");
      Serial1.write(0x22);
      Serial1.write(NexT, 3); 

    
    }
  }
  if (Serialport3 == 'S') {                   //    Restart Tuner
    Serialport3 = Serial3.parseInt();
    if (Serial3.read() == 'F') {
      if (Serialport3 == 1) {
        
        Restart ++;

        if (Restart >= 3) {
        Serial1.print("page 5");
        Serial1.write(0xff);
        Serial1.write(0xff);
        Serial1.write(0xff);
    
        Serial1.print("t2.txt=");
        Serial1.write(0x22);
        Serial1.print("Firmware ");
        Serial1.print(Firmware_v);
        Serial1.write(0x22);
        Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
        }
      }
    }
  }
  if (digitalRead(6) == LOW) {                //    PTT-Switch
        digitalWrite(2, HIGH);
        Serial1.print("t10.bco=63488"); 
        Serial1.write(NexT, 3);
		
    } else if  (digitalRead(6) == HIGH) {
        digitalWrite(2, LOW);
        Serial1.print("t10.bco=0"); 
        Serial1.write(NexT, 3);   
  }  
  if (millis() - Catfre >= Cat_fre) {         //    TRX-CAT Freq,
    Catfre = millis();
    millis();
    listen:
    Serial2.write(0xFE);
    Serial2.write(0xFE);
    Serial2.write(trx_adress);
    Serial2.write(0xE0);
    Serial2.write(0x03);
    Serial2.write(0xFD);

      Serial.print(	TRXCAT[0]	, HEX);
      Serial.print(	"/");
      Serial.print(	TRXCAT[1]	, HEX);
      Serial.print(	"/");	
      Serial.print(	TRXCAT[2]	, HEX);
      Serial.print(	"/");	
      Serial.print(	TRXCAT[3]	, HEX);
      Serial.print(	"/");	
      Serial.print(	TRXCAT[4]	, HEX);
      Serial.print(	"/");	
      Serial.print(	TRXCAT[5]	, HEX);
      Serial.print(	"/");	
      Serial.print(	TRXCAT[6]	, HEX);
      Serial.print(	"/");	
      Serial.print(	TRXCAT[8]	, HEX);
      Serial.print(	"/");	
      Serial.print(	TRXCAT[9]	, HEX);
      Serial.print(	"/");	
      Serial.print(	TRXCAT[10]	, HEX);
      Serial.println(	"/");	
  }
  if (TRXCAT[0] == 253) {                     //    Cat-Freq/Mode

    if (TRXCAT[2] == 3) {
      MHZ = TRXCAT[6];
      MHZ = MHZ - (((MHZ / 16) * 6));
      if (MHZ >= 100) goto listen;

      KHZ = TRXCAT[5];
      KHZ = KHZ - (((KHZ / 16) * 6));
      if (KHZ >= 100) goto listen;

      HZ = TRXCAT[4];
      HZ = HZ - (((HZ / 16) * 6));
      if (HZ >= 100) goto listen;

      QRG = ((MHZ * 10000) + (KHZ * 100) + (HZ * 1));
      if (QRG <= 10000) goto listen;
      }
      QRGcomp = QRG;
      Banddec = QRGcomp;
      Banddec = Banddec /10;
      QRGcomp = QRGcomp / 10;
      
      Serial1.print("t3.txt=");
      Serial1.write(0x22);
      Serial1.print(QRG / 10000, DEC);
      Serial1.print(".");
      if (QRG%10000 < 1000 ) Serial1.print("0");
      if (QRG%10000 < 100 ) Serial1.print("0");
      if (QRG%10000 < 10 ) Serial1.print("0");
      Serial1.print(QRG%10000 / 10,DEC);
      Serial1.print(" MHz");
      Serial1.write(0x22);
      Serial1.write(NexT, 3);
  }
  if (QRGcomp != FREQWechsel) {               //    Frequenz Wechsel Decoder
    Auto = 1;
    } else if (FREQWechsel != QRGcomp) {
    Auto = 1;
  }
  if (Manual == 0 && Auto == 1 & millis() - Bandtrx >= Band_trx) {
    Bandtrx = millis();
    millis();					
	  if	        (Banddec	>=	0	    &&	Banddec	<=	1809)	{	//	Banddecoder			
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	1810	&&	Banddec	<=	2000)	{	//	160m
			Serial1.print("bt0.val=1");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=0");	//outofband										
			Serial1.write(NexT,	3);								
		}	else	if	(Banddec	>=	2001	&&	Banddec	<=	3499)	{		
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	3500	&&	Banddec	<=	3800)	{	//	80m
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=1");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=0");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	3801	&&	Banddec	<=	5349)	{		
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	5350	&&	Banddec	<=	5367)	{	//	60m
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=1");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=0");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	5368	&&	Banddec	<=	6999)	{		
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	7000	&&	Banddec	<=	7200)	{	//	40m
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=1");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=0");	//outofband										
			Serial1.write(NexT,	3);																					
		}	else	if	(Banddec	>=	7201	&&	Banddec	<=	10099)	{		
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	10100	&&	Banddec	<=	10150)	{	//	30m
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=1");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=0");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	10151	&&	Banddec	<=	13999)	{		
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	14000	&&	Banddec	<=	14350)	{	//	20m
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=1");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=0");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	14351	&&	Banddec	<=	18067)	{		
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	18068	&&	Banddec	<=	18168)	{	//	17m
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=1");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=0");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	18169	&&	Banddec	<=	20999)	{		
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	21000	&&	Banddec	<=	21450)	{	//	15m
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=1");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=0");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	21451	&&	Banddec	<=	24889)	{		
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	24890	&&	Banddec	<=	24990)	{	//	12m
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=1");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=0");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	24991	&&	Banddec	<=	27999)	{		
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	28000	&&	Banddec	<=	29700)	{	//	10m
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=1");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=0");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	29701	&&	Banddec	<=	49999)	{		
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	50000	&&	Banddec	<=	52000)	{	//	6m
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=1");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=0");	//outofband										
			Serial1.write(NexT,	3);										
		}	else	if	(Banddec	>=	52000	&&	Banddec	<=	99999)	{		
			Serial1.print("bt0.val=0");	//160										
			Serial1.write(NexT,	3);										
			Serial1.print("bt1.val=0");	//80										
			Serial1.write(NexT,	3);										
			Serial1.print("bt2.val=0");	//60										
			Serial1.write(NexT,	3);										
			Serial1.print("bt3.val=0");	//40										
			Serial1.write(NexT,	3);										
			Serial1.print("bt4.val=0");	//30										
			Serial1.write(NexT,	3);										
			Serial1.print("bt5.val=0");	//20										
			Serial1.write(NexT,	3);										
			Serial1.print("bt6.val=0");	//17										
			Serial1.write(NexT,	3);										
			Serial1.print("bt7.val=0");	//15										
			Serial1.write(NexT,	3);										
			Serial1.print("bt8.val=0");	//12										
			Serial1.write(NexT,	3);										
			Serial1.print("bt9.val=0");	//10										
			Serial1.write(NexT,	3);										
			Serial1.print("bt10.val=0");	//6										
			Serial1.write(NexT,	3);										
			Serial1.print("bt11.val=1");	//outofband										
			Serial1.write(NexT,	3);										
	  }
    if				(QRGcomp >=	1810	&&	QRGcomp <=	1839	) {L = EEPROM.read	(	1	);	 C1 = EEPROM.read	(	200	);	 C2 = EEPROM.read	(	400	);	 Z = EEPROM.read(	600	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");   Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if     (QRGcomp >=	1840	&&	QRGcomp <=	1869	) {L = EEPROM.read	(	2	);	 C1 = EEPROM.read	(	201	);	 C2 = EEPROM.read	(	401	);	 Z = EEPROM.read(	601	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	1870	&&	QRGcomp <=	1899	) {L = EEPROM.read	(	3	);	 C1 = EEPROM.read	(	202	);	 C2 = EEPROM.read	(	402	);	 Z = EEPROM.read(	602	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	1900	&&	QRGcomp <=	1929	) {L = EEPROM.read	(	4	);	 C1 = EEPROM.read	(	203	);	 C2 = EEPROM.read	(	403	);	 Z = EEPROM.read(	603	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	1930	&&	QRGcomp <=	1959	) {L = EEPROM.read	(	5	);	 C1 = EEPROM.read	(	204	);	 C2 = EEPROM.read	(	404	);	 Z = EEPROM.read(	604	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	1960	&&	QRGcomp <=	1989	) {L = EEPROM.read	(	6	);	 C1 = EEPROM.read	(	205	);	 C2 = EEPROM.read	(	405	);	 Z = EEPROM.read(	605	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	1990	&&	QRGcomp <=	2000	) {L = EEPROM.read	(	7	);	 C1 = EEPROM.read	(	206	);	 C2 = EEPROM.read	(	406	);	 Z = EEPROM.read(	606	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	3500	&&	QRGcomp <=	3529	) {L = EEPROM.read	(	8	);	 C1 = EEPROM.read	(	207	);	 C2 = EEPROM.read	(	407	);	 Z = EEPROM.read(	607	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	3530	&&	QRGcomp <=	3559	) {L = EEPROM.read	(	9	);	 C1 = EEPROM.read	(	208	);	 C2 = EEPROM.read	(	408	);	 Z = EEPROM.read(	608	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	3560	&&	QRGcomp <=	3589	) {L = EEPROM.read	(	10	);	 C1 = EEPROM.read	(	209	);	 C2 = EEPROM.read	(	409	);	 Z = EEPROM.read(	609	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	3590	&&	QRGcomp <=	3619	) {L = EEPROM.read	(	11	);	 C1 = EEPROM.read	(	210	);	 C2 = EEPROM.read	(	410	);	 Z = EEPROM.read(	610	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	3620	&&	QRGcomp <=	3649	) {L = EEPROM.read	(	12	);	 C1 = EEPROM.read	(	211	);	 C2 = EEPROM.read	(	411	);	 Z = EEPROM.read(	611	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	3650	&&	QRGcomp <=	3679	) {L = EEPROM.read	(	13	);	 C1 = EEPROM.read	(	212	);	 C2 = EEPROM.read	(	412	);	 Z = EEPROM.read(	612	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	3680	&&	QRGcomp <=	3709	) {L = EEPROM.read	(	14	);	 C1 = EEPROM.read	(	213	);	 C2 = EEPROM.read	(	413	);	 Z = EEPROM.read(	613	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	3710	&&	QRGcomp <=	3739	) {L = EEPROM.read	(	15	);	 C1 = EEPROM.read	(	214	);	 C2 = EEPROM.read	(	414	);	 Z = EEPROM.read(	614	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	3740	&&	QRGcomp <=	3769	) {L = EEPROM.read	(	16	);	 C1 = EEPROM.read	(	215	);	 C2 = EEPROM.read	(	415	);	 Z = EEPROM.read(	615	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	3770	&&	QRGcomp <=	3800	) {L = EEPROM.read	(	17	);	 C1 = EEPROM.read	(	216	);	 C2 = EEPROM.read	(	416	);	 Z = EEPROM.read(	616	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	5350	&&	QRGcomp <=	5366	) {L = EEPROM.read	(	18	);	 C1 = EEPROM.read	(	217	);	 C2 = EEPROM.read	(	417	);	 Z = EEPROM.read(	617	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	7000	&&	QRGcomp <=	7029	) {L = EEPROM.read	(	19	);	 C1 = EEPROM.read	(	218	);	 C2 = EEPROM.read	(	418	);	 Z = EEPROM.read(	618	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	7030	&&	QRGcomp <=	7059	) {L = EEPROM.read	(	20	);	 C1 = EEPROM.read	(	219	);	 C2 = EEPROM.read	(	419	);	 Z = EEPROM.read(	619	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	7060	&&	QRGcomp <=	7089	) {L = EEPROM.read	(	21	);	 C1 = EEPROM.read	(	220	);	 C2 = EEPROM.read	(	420	);	 Z = EEPROM.read(	620	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	7090	&&	QRGcomp <=	7119	) {L = EEPROM.read	(	22	);	 C1 = EEPROM.read	(	221	);	 C2 = EEPROM.read	(	421	);	 Z = EEPROM.read(	621	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	7120	&&	QRGcomp <=	7149	) {L = EEPROM.read	(	23	);	 C1 = EEPROM.read	(	222	);	 C2 = EEPROM.read	(	422	);	 Z = EEPROM.read(	622	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	7150	&&	QRGcomp <=	7179	) {L = EEPROM.read	(	24	);	 C1 = EEPROM.read	(	223	);	 C2 = EEPROM.read	(	423	);	 Z = EEPROM.read(	623	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	7180	&&	QRGcomp <=	7200	) {L = EEPROM.read	(	25	);	 C1 = EEPROM.read	(	224	);	 C2 = EEPROM.read	(	424	);	 Z = EEPROM.read(	624	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	10100	&&	QRGcomp <=	10124	) {L = EEPROM.read	(	26	);	 C1 = EEPROM.read	(	225	);	 C2 = EEPROM.read	(	425	);	 Z = EEPROM.read(	625	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	10125	&&	QRGcomp <=	10150	) {L = EEPROM.read	(	27	);	 C1 = EEPROM.read	(	226	);	 C2 = EEPROM.read	(	426	);	 Z = EEPROM.read(	626	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14000	&&	QRGcomp <=	14029	) {L = EEPROM.read	(	28	);	 C1 = EEPROM.read	(	227	);	 C2 = EEPROM.read	(	427	);	 Z = EEPROM.read(	627	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14030	&&	QRGcomp <=	14059	) {L = EEPROM.read	(	29	);	 C1 = EEPROM.read	(	228	);	 C2 = EEPROM.read	(	428	);	 Z = EEPROM.read(	628	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14060	&&	QRGcomp <=	14089	) {L = EEPROM.read	(	30	);	 C1 = EEPROM.read	(	229	);	 C2 = EEPROM.read	(	429	);	 Z = EEPROM.read(	629	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14090	&&	QRGcomp <=	14119	) {L = EEPROM.read	(	31	);	 C1 = EEPROM.read	(	230	);	 C2 = EEPROM.read	(	430	);	 Z = EEPROM.read(	630	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14120	&&	QRGcomp <=	14149	) {L = EEPROM.read	(	32	);	 C1 = EEPROM.read	(	231	);	 C2 = EEPROM.read	(	431	);	 Z = EEPROM.read(	631	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14150	&&	QRGcomp <=	14179	) {L = EEPROM.read	(	33	);	 C1 = EEPROM.read	(	232	);	 C2 = EEPROM.read	(	432	);	 Z = EEPROM.read(	632	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14180	&&	QRGcomp <=	14209	) {L = EEPROM.read	(	34	);	 C1 = EEPROM.read	(	233	);	 C2 = EEPROM.read	(	433	);	 Z = EEPROM.read(	633	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14210	&&	QRGcomp <=	14239	) {L = EEPROM.read	(	35	);	 C1 = EEPROM.read	(	234	);	 C2 = EEPROM.read	(	434	);	 Z = EEPROM.read(	634	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14240	&&	QRGcomp <=	14269	) {L = EEPROM.read	(	36	);	 C1 = EEPROM.read	(	235	);	 C2 = EEPROM.read	(	435	);	 Z = EEPROM.read(	635	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14270	&&	QRGcomp <=	14299	) {L = EEPROM.read	(	37	);	 C1 = EEPROM.read	(	236	);	 C2 = EEPROM.read	(	436	);	 Z = EEPROM.read(	636	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14300	&&	QRGcomp <=	14329	) {L = EEPROM.read	(	38	);	 C1 = EEPROM.read	(	237	);	 C2 = EEPROM.read	(	437	);	 Z = EEPROM.read(	637	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	14330	&&	QRGcomp <=	14350	) {L = EEPROM.read	(	39	);	 C1 = EEPROM.read	(	238	);	 C2 = EEPROM.read	(	438	);	 Z = EEPROM.read(	638	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	18068	&&	QRGcomp <=	18097	) {L = EEPROM.read	(	40	);	 C1 = EEPROM.read	(	239	);	 C2 = EEPROM.read	(	439	);	 Z = EEPROM.read(	639	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	18098	&&	QRGcomp <=	18127	) {L = EEPROM.read	(	41	);	 C1 = EEPROM.read	(	240	);	 C2 = EEPROM.read	(	440	);	 Z = EEPROM.read(	640	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	18128	&&	QRGcomp <=	18157	) {L = EEPROM.read	(	42	);	 C1 = EEPROM.read	(	241	);	 C2 = EEPROM.read	(	441	);	 Z = EEPROM.read(	641	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	18158	&&	QRGcomp <=	18168	) {L = EEPROM.read	(	43	);	 C1 = EEPROM.read	(	242	);	 C2 = EEPROM.read	(	442	);	 Z = EEPROM.read(	642	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21000	&&	QRGcomp <=	21029	) {L = EEPROM.read	(	44	);	 C1 = EEPROM.read	(	243	);	 C2 = EEPROM.read	(	443	);	 Z = EEPROM.read(	643	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21030	&&	QRGcomp <=	21059	) {L = EEPROM.read	(	45	);	 C1 = EEPROM.read	(	244	);	 C2 = EEPROM.read	(	444	);	 Z = EEPROM.read(	644	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21060	&&	QRGcomp <=	21089	) {L = EEPROM.read	(	46	);	 C1 = EEPROM.read	(	245	);	 C2 = EEPROM.read	(	445	);	 Z = EEPROM.read(	645	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21090	&&	QRGcomp <=	21119	) {L = EEPROM.read	(	47	);	 C1 = EEPROM.read	(	246	);	 C2 = EEPROM.read	(	446	);	 Z = EEPROM.read(	646	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21120	&&	QRGcomp <=	21149	) {L = EEPROM.read	(	48	);	 C1 = EEPROM.read	(	247	);	 C2 = EEPROM.read	(	447	);	 Z = EEPROM.read(	647	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21150	&&	QRGcomp <=	21179	) {L = EEPROM.read	(	49	);	 C1 = EEPROM.read	(	248	);	 C2 = EEPROM.read	(	448	);	 Z = EEPROM.read(	648	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21180	&&	QRGcomp <=	21209	) {L = EEPROM.read	(	50	);	 C1 = EEPROM.read	(	249	);	 C2 = EEPROM.read	(	449	);	 Z = EEPROM.read(	649	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21210	&&	QRGcomp <=	21239	) {L = EEPROM.read	(	51	);	 C1 = EEPROM.read	(	250	);	 C2 = EEPROM.read	(	450	);	 Z = EEPROM.read(	650	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21240	&&	QRGcomp <=	21269	) {L = EEPROM.read	(	52	);	 C1 = EEPROM.read	(	251	);	 C2 = EEPROM.read	(	451	);	 Z = EEPROM.read(	651	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21270	&&	QRGcomp <=	21299	) {L = EEPROM.read	(	53	);	 C1 = EEPROM.read	(	252	);	 C2 = EEPROM.read	(	452	);	 Z = EEPROM.read(	652	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21300	&&	QRGcomp <=	21329	) {L = EEPROM.read	(	54	);	 C1 = EEPROM.read	(	253	);	 C2 = EEPROM.read	(	453	);	 Z = EEPROM.read(	653	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21330	&&	QRGcomp <=	21359	) {L = EEPROM.read	(	55	);	 C1 = EEPROM.read	(	254	);	 C2 = EEPROM.read	(	454	);	 Z = EEPROM.read(	654	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21360	&&	QRGcomp <=	21389	) {L = EEPROM.read	(	56	);	 C1 = EEPROM.read	(	255	);	 C2 = EEPROM.read	(	455	);	 Z = EEPROM.read(	655	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21390	&&	QRGcomp <=	21419	) {L = EEPROM.read	(	57	);	 C1 = EEPROM.read	(	256	);	 C2 = EEPROM.read	(	456	);	 Z = EEPROM.read(	656	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	21420	&&	QRGcomp <=	21450	) {L = EEPROM.read	(	58	);	 C1 = EEPROM.read	(	257	);	 C2 = EEPROM.read	(	457	);	 Z = EEPROM.read(	657	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	24890	&&	QRGcomp <=	24919	) {L = EEPROM.read	(	59	);	 C1 = EEPROM.read	(	258	);	 C2 = EEPROM.read	(	458	);	 Z = EEPROM.read(	658	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	24949	&&	QRGcomp <=	24979	) {L = EEPROM.read	(	60	);	 C1 = EEPROM.read	(	259	);	 C2 = EEPROM.read	(	459	);	 Z = EEPROM.read(	659	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	24980	&&	QRGcomp <=	24990	) {L = EEPROM.read	(	61	);	 C1 = EEPROM.read	(	260	);	 C2 = EEPROM.read	(	460	);	 Z = EEPROM.read(	660	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28000	&&	QRGcomp <=	28029	) {L = EEPROM.read	(	62	);	 C1 = EEPROM.read	(	261	);	 C2 = EEPROM.read	(	461	);	 Z = EEPROM.read(	661	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28030	&&	QRGcomp <=	28059	) {L = EEPROM.read	(	63	);	 C1 = EEPROM.read	(	262	);	 C2 = EEPROM.read	(	462	);	 Z = EEPROM.read(	662	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28060	&&	QRGcomp <=	28089	) {L = EEPROM.read	(	64	);	 C1 = EEPROM.read	(	263	);	 C2 = EEPROM.read	(	463	);	 Z = EEPROM.read(	663	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28090	&&	QRGcomp <=	28119	) {L = EEPROM.read	(	65	);	 C1 = EEPROM.read	(	264	);	 C2 = EEPROM.read	(	464	);	 Z = EEPROM.read(	664	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28120	&&	QRGcomp <=	28149	) {L = EEPROM.read	(	66	);	 C1 = EEPROM.read	(	265	);	 C2 = EEPROM.read	(	465	);	 Z = EEPROM.read(	665	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28150	&&	QRGcomp <=	28179	) {L = EEPROM.read	(	67	);	 C1 = EEPROM.read	(	266	);	 C2 = EEPROM.read	(	466	);	 Z = EEPROM.read(	666	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28180	&&	QRGcomp <=	28209	) {L = EEPROM.read	(	68	);	 C1 = EEPROM.read	(	267	);	 C2 = EEPROM.read	(	467	);	 Z = EEPROM.read(	667	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28210	&&	QRGcomp <=	28239	) {L = EEPROM.read	(	69	);	 C1 = EEPROM.read	(	268	);	 C2 = EEPROM.read	(	468	);	 Z = EEPROM.read(	668	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28240	&&	QRGcomp <=	28269	) {L = EEPROM.read	(	70	);	 C1 = EEPROM.read	(	269	);	 C2 = EEPROM.read	(	469	);	 Z = EEPROM.read(	669	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28270	&&	QRGcomp <=	28299	) {L = EEPROM.read	(	71	);	 C1 = EEPROM.read	(	270	);	 C2 = EEPROM.read	(	470	);	 Z = EEPROM.read(	670	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28300	&&	QRGcomp <=	28329	) {L = EEPROM.read	(	72	);	 C1 = EEPROM.read	(	271	);	 C2 = EEPROM.read	(	471	);	 Z = EEPROM.read(	671	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28330	&&	QRGcomp <=	28359	) {L = EEPROM.read	(	73	);	 C1 = EEPROM.read	(	272	);	 C2 = EEPROM.read	(	472	);	 Z = EEPROM.read(	672	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28360	&&	QRGcomp <=	28389	) {L = EEPROM.read	(	74	);	 C1 = EEPROM.read	(	273	);	 C2 = EEPROM.read	(	473	);	 Z = EEPROM.read(	673	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28390	&&	QRGcomp <=	28419	) {L = EEPROM.read	(	75	);	 C1 = EEPROM.read	(	274	);	 C2 = EEPROM.read	(	474	);	 Z = EEPROM.read(	674	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28420	&&	QRGcomp <=	28449	) {L = EEPROM.read	(	76	);	 C1 = EEPROM.read	(	275	);	 C2 = EEPROM.read	(	475	);	 Z = EEPROM.read(	675	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28450	&&	QRGcomp <=	28479	) {L = EEPROM.read	(	77	);	 C1 = EEPROM.read	(	276	);	 C2 = EEPROM.read	(	476	);	 Z = EEPROM.read(	676	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28480	&&	QRGcomp <=	28509	) {L = EEPROM.read	(	78	);	 C1 = EEPROM.read	(	277	);	 C2 = EEPROM.read	(	477	);	 Z = EEPROM.read(	677	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28510	&&	QRGcomp <=	28539	) {L = EEPROM.read	(	79	);	 C1 = EEPROM.read	(	278	);	 C2 = EEPROM.read	(	478	);	 Z = EEPROM.read(	678	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28540	&&	QRGcomp <=	28569	) {L = EEPROM.read	(	80	);	 C1 = EEPROM.read	(	279	);	 C2 = EEPROM.read	(	479	);	 Z = EEPROM.read(	679	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28570	&&	QRGcomp <=	28599	) {L = EEPROM.read	(	81	);	 C1 = EEPROM.read	(	280	);	 C2 = EEPROM.read	(	480	);	 Z = EEPROM.read(	680	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28600	&&	QRGcomp <=	28629	) {L = EEPROM.read	(	82	);	 C1 = EEPROM.read	(	281	);	 C2 = EEPROM.read	(	481	);	 Z = EEPROM.read(	681	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28630	&&	QRGcomp <=	28659	) {L = EEPROM.read	(	83	);	 C1 = EEPROM.read	(	282	);	 C2 = EEPROM.read	(	482	);	 Z = EEPROM.read(	682	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28660	&&	QRGcomp <=	28689	) {L = EEPROM.read	(	84	);	 C1 = EEPROM.read	(	283	);	 C2 = EEPROM.read	(	483	);	 Z = EEPROM.read(	683	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28690	&&	QRGcomp <=	28719	) {L = EEPROM.read	(	85	);	 C1 = EEPROM.read	(	284	);	 C2 = EEPROM.read	(	484	);	 Z = EEPROM.read(	684	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28720	&&	QRGcomp <=	28749	) {L = EEPROM.read	(	86	);	 C1 = EEPROM.read	(	285	);	 C2 = EEPROM.read	(	485	);	 Z = EEPROM.read(	685	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28750	&&	QRGcomp <=	28779	) {L = EEPROM.read	(	87	);	 C1 = EEPROM.read	(	286	);	 C2 = EEPROM.read	(	486	);	 Z = EEPROM.read(	686	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28780	&&	QRGcomp <=	28809	) {L = EEPROM.read	(	88	);	 C1 = EEPROM.read	(	287	);	 C2 = EEPROM.read	(	487	);	 Z = EEPROM.read(	687	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28810	&&	QRGcomp <=	28839	) {L = EEPROM.read	(	89	);	 C1 = EEPROM.read	(	288	);	 C2 = EEPROM.read	(	488	);	 Z = EEPROM.read(	688	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28840	&&	QRGcomp <=	28869	) {L = EEPROM.read	(	90	);	 C1 = EEPROM.read	(	289	);	 C2 = EEPROM.read	(	489	);	 Z = EEPROM.read(	689	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28870	&&	QRGcomp <=	28899	) {L = EEPROM.read	(	91	);	 C1 = EEPROM.read	(	290	);	 C2 = EEPROM.read	(	490	);	 Z = EEPROM.read(	690	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28900	&&	QRGcomp <=	28929	) {L = EEPROM.read	(	92	);	 C1 = EEPROM.read	(	291	);	 C2 = EEPROM.read	(	491	);	 Z = EEPROM.read(	691	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28930	&&	QRGcomp <=	28959	) {L = EEPROM.read	(	93	);	 C1 = EEPROM.read	(	292	);	 C2 = EEPROM.read	(	492	);	 Z = EEPROM.read(	692	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28960	&&	QRGcomp <=	28989	) {L = EEPROM.read	(	94	);	 C1 = EEPROM.read	(	293	);	 C2 = EEPROM.read	(	493	);	 Z = EEPROM.read(	693	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	28990	&&	QRGcomp <=	29019	) {L = EEPROM.read	(	95	);	 C1 = EEPROM.read	(	294	);	 C2 = EEPROM.read	(	494	);	 Z = EEPROM.read(	694	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29020	&&	QRGcomp <=	29049	) {L = EEPROM.read	(	96	);	 C1 = EEPROM.read	(	295	);	 C2 = EEPROM.read	(	495	);	 Z = EEPROM.read(	695	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29050	&&	QRGcomp <=	29079	) {L = EEPROM.read	(	97	);	 C1 = EEPROM.read	(	296	);	 C2 = EEPROM.read	(	496	);	 Z = EEPROM.read(	696	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29080	&&	QRGcomp <=	29109	) {L = EEPROM.read	(	98	);	 C1 = EEPROM.read	(	297	);	 C2 = EEPROM.read	(	497	);	 Z = EEPROM.read(	697	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29110	&&	QRGcomp <=	29139	) {L = EEPROM.read	(	99	);	 C1 = EEPROM.read	(	298	);	 C2 = EEPROM.read	(	498	);	 Z = EEPROM.read(	698	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29140	&&	QRGcomp <=	29169	) {L = EEPROM.read	(	100	);	 C1 = EEPROM.read	(	299	);	 C2 = EEPROM.read	(	499	);	 Z = EEPROM.read(	699	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29170	&&	QRGcomp <=	29199	) {L = EEPROM.read	(	101	);	 C1 = EEPROM.read	(	300	);	 C2 = EEPROM.read	(	500	);	 Z = EEPROM.read(	700	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29200	&&	QRGcomp <=	29229	) {L = EEPROM.read	(	102	);	 C1 = EEPROM.read	(	301	);	 C2 = EEPROM.read	(	501	);	 Z = EEPROM.read(	701	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29230	&&	QRGcomp <=	29259	) {L = EEPROM.read	(	103	);	 C1 = EEPROM.read	(	302	);	 C2 = EEPROM.read	(	502	);	 Z = EEPROM.read(	702	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29260	&&	QRGcomp <=	29289	) {L = EEPROM.read	(	104	);	 C1 = EEPROM.read	(	303	);	 C2 = EEPROM.read	(	503	);	 Z = EEPROM.read(	703	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29290	&&	QRGcomp <=	29319	) {L = EEPROM.read	(	105	);	 C1 = EEPROM.read	(	304	);	 C2 = EEPROM.read	(	504	);	 Z = EEPROM.read(	704	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29320	&&	QRGcomp <=	29349	) {L = EEPROM.read	(	106	);	 C1 = EEPROM.read	(	305	);	 C2 = EEPROM.read	(	505	);	 Z = EEPROM.read(	705	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29350	&&	QRGcomp <=	29379	) {L = EEPROM.read	(	107	);	 C1 = EEPROM.read	(	306	);	 C2 = EEPROM.read	(	506	);	 Z = EEPROM.read(	706	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29380	&&	QRGcomp <=	29409	) {L = EEPROM.read	(	108	);	 C1 = EEPROM.read	(	307	);	 C2 = EEPROM.read	(	507	);	 Z = EEPROM.read(	707	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29410	&&	QRGcomp <=	29439	) {L = EEPROM.read	(	109	);	 C1 = EEPROM.read	(	308	);	 C2 = EEPROM.read	(	508	);	 Z = EEPROM.read(	708	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29440	&&	QRGcomp <=	29469	) {L = EEPROM.read	(	110	);	 C1 = EEPROM.read	(	309	);	 C2 = EEPROM.read	(	509	);	 Z = EEPROM.read(	709	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29470	&&	QRGcomp <=	29499	) {L = EEPROM.read	(	111	);	 C1 = EEPROM.read	(	310	);	 C2 = EEPROM.read	(	510	);	 Z = EEPROM.read(	710	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29500	&&	QRGcomp <=	29529	) {L = EEPROM.read	(	112	);	 C1 = EEPROM.read	(	311	);	 C2 = EEPROM.read	(	511	);	 Z = EEPROM.read(	711	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29530	&&	QRGcomp <=	29559	) {L = EEPROM.read	(	113	);	 C1 = EEPROM.read	(	312	);	 C2 = EEPROM.read	(	512	);	 Z = EEPROM.read(	712	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29560	&&	QRGcomp <=	29589	) {L = EEPROM.read	(	114	);	 C1 = EEPROM.read	(	313	);	 C2 = EEPROM.read	(	513	);	 Z = EEPROM.read(	713	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29590	&&	QRGcomp <=	29619	) {L = EEPROM.read	(	115	);	 C1 = EEPROM.read	(	314	);	 C2 = EEPROM.read	(	514	);	 Z = EEPROM.read(	714	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29620	&&	QRGcomp <=	29649	) {L = EEPROM.read	(	116	);	 C1 = EEPROM.read	(	315	);	 C2 = EEPROM.read	(	515	);	 Z = EEPROM.read(	715	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29650	&&	QRGcomp <=	29679	) {L = EEPROM.read	(	117	);	 C1 = EEPROM.read	(	316	);	 C2 = EEPROM.read	(	516	);	 Z = EEPROM.read(	716	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	29680	&&	QRGcomp <=	28059	) {L = EEPROM.read	(	118	);	 C1 = EEPROM.read	(	317	);	 C2 = EEPROM.read	(	517	);	 Z = EEPROM.read(	717	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50000	&&	QRGcomp <=	50029	) {L = EEPROM.read	(	119	);	 C1 = EEPROM.read	(	318	);	 C2 = EEPROM.read	(	518	);	 Z = EEPROM.read(	718	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50030	&&	QRGcomp <=	50059	) {L = EEPROM.read	(	120	);	 C1 = EEPROM.read	(	319	);	 C2 = EEPROM.read	(	519	);	 Z = EEPROM.read(	719	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50060	&&	QRGcomp <=	50089	) {L = EEPROM.read	(	121	);	 C1 = EEPROM.read	(	320	);	 C2 = EEPROM.read	(	520	);	 Z = EEPROM.read(	720	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50090	&&	QRGcomp <=	50119	) {L = EEPROM.read	(	122	);	 C1 = EEPROM.read	(	321	);	 C2 = EEPROM.read	(	521	);	 Z = EEPROM.read(	721	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50120	&&	QRGcomp <=	50149	) {L = EEPROM.read	(	123	);	 C1 = EEPROM.read	(	322	);	 C2 = EEPROM.read	(	522	);	 Z = EEPROM.read(	722	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50150	&&	QRGcomp <=	50179	) {L = EEPROM.read	(	124	);	 C1 = EEPROM.read	(	323	);	 C2 = EEPROM.read	(	523	);	 Z = EEPROM.read(	723	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50180	&&	QRGcomp <=	50209	) {L = EEPROM.read	(	125	);	 C1 = EEPROM.read	(	324	);	 C2 = EEPROM.read	(	524	);	 Z = EEPROM.read(	724	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50210	&&	QRGcomp <=	50239	) {L = EEPROM.read	(	126	);	 C1 = EEPROM.read	(	325	);	 C2 = EEPROM.read	(	525	);	 Z = EEPROM.read(	725	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50240	&&	QRGcomp <=	50269	) {L = EEPROM.read	(	127	);	 C1 = EEPROM.read	(	326	);	 C2 = EEPROM.read	(	526	);	 Z = EEPROM.read(	726	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50270	&&	QRGcomp <=	50299	) {L = EEPROM.read	(	128	);	 C1 = EEPROM.read	(	327	);	 C2 = EEPROM.read	(	527	);	 Z = EEPROM.read(	727	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50300	&&	QRGcomp <=	50329	) {L = EEPROM.read	(	129	);	 C1 = EEPROM.read	(	328	);	 C2 = EEPROM.read	(	528	);	 Z = EEPROM.read(	728	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50330	&&	QRGcomp <=	50359	) {L = EEPROM.read	(	130	);	 C1 = EEPROM.read	(	329	);	 C2 = EEPROM.read	(	529	);	 Z = EEPROM.read(	729	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50360	&&	QRGcomp <=	50389	) {L = EEPROM.read	(	131	);	 C1 = EEPROM.read	(	330	);	 C2 = EEPROM.read	(	530	);	 Z = EEPROM.read(	730	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50390	&&	QRGcomp <=	50419	) {L = EEPROM.read	(	132	);	 C1 = EEPROM.read	(	331	);	 C2 = EEPROM.read	(	531	);	 Z = EEPROM.read(	731	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50420	&&	QRGcomp <=	50449	) {L = EEPROM.read	(	133	);	 C1 = EEPROM.read	(	332	);	 C2 = EEPROM.read	(	532	);	 Z = EEPROM.read(	732	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50450	&&	QRGcomp <=	50479	) {L = EEPROM.read	(	134	);	 C1 = EEPROM.read	(	333	);	 C2 = EEPROM.read	(	533	);	 Z = EEPROM.read(	733	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50480	&&	QRGcomp <=	50509	) {L = EEPROM.read	(	135	);	 C1 = EEPROM.read	(	334	);	 C2 = EEPROM.read	(	534	);	 Z = EEPROM.read(	734	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50510	&&	QRGcomp <=	50539	) {L = EEPROM.read	(	136	);	 C1 = EEPROM.read	(	335	);	 C2 = EEPROM.read	(	535	);	 Z = EEPROM.read(	735	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50540	&&	QRGcomp <=	50569	) {L = EEPROM.read	(	137	);	 C1 = EEPROM.read	(	336	);	 C2 = EEPROM.read	(	536	);	 Z = EEPROM.read(	736	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50570	&&	QRGcomp <=	50599	) {L = EEPROM.read	(	138	);	 C1 = EEPROM.read	(	337	);	 C2 = EEPROM.read	(	537	);	 Z = EEPROM.read(	737	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50600	&&	QRGcomp <=	50629	) {L = EEPROM.read	(	139	);	 C1 = EEPROM.read	(	338	);	 C2 = EEPROM.read	(	538	);	 Z = EEPROM.read(	738	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50630	&&	QRGcomp <=	50659	) {L = EEPROM.read	(	140	);	 C1 = EEPROM.read	(	339	);	 C2 = EEPROM.read	(	539	);	 Z = EEPROM.read(	739	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50660	&&	QRGcomp <=	50689	) {L = EEPROM.read	(	141	);	 C1 = EEPROM.read	(	340	);	 C2 = EEPROM.read	(	540	);	 Z = EEPROM.read(	740	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50690	&&	QRGcomp <=	50719	) {L = EEPROM.read	(	142	);	 C1 = EEPROM.read	(	341	);	 C2 = EEPROM.read	(	541	);	 Z = EEPROM.read(	741	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50720	&&	QRGcomp <=	50749	) {L = EEPROM.read	(	143	);	 C1 = EEPROM.read	(	342	);	 C2 = EEPROM.read	(	542	);	 Z = EEPROM.read(	742	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50750	&&	QRGcomp <=	50779	) {L = EEPROM.read	(	144	);	 C1 = EEPROM.read	(	343	);	 C2 = EEPROM.read	(	543	);	 Z = EEPROM.read(	743	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50780	&&	QRGcomp <=	50809	) {L = EEPROM.read	(	145	);	 C1 = EEPROM.read	(	344	);	 C2 = EEPROM.read	(	544	);	 Z = EEPROM.read(	744	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50810	&&	QRGcomp <=	50839	) {L = EEPROM.read	(	146	);	 C1 = EEPROM.read	(	345	);	 C2 = EEPROM.read	(	545	);	 Z = EEPROM.read(	745	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50840	&&	QRGcomp <=	50869	) {L = EEPROM.read	(	147	);	 C1 = EEPROM.read	(	346	);	 C2 = EEPROM.read	(	546	);	 Z = EEPROM.read(	746	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50870	&&	QRGcomp <=	50899	) {L = EEPROM.read	(	148	);	 C1 = EEPROM.read	(	347	);	 C2 = EEPROM.read	(	547	);	 Z = EEPROM.read(	747	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50900	&&	QRGcomp <=	50929	) {L = EEPROM.read	(	149	);	 C1 = EEPROM.read	(	348	);	 C2 = EEPROM.read	(	548	);	 Z = EEPROM.read(	748	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50930	&&	QRGcomp <=	50959	) {L = EEPROM.read	(	150	);	 C1 = EEPROM.read	(	349	);	 C2 = EEPROM.read	(	549	);	 Z = EEPROM.read(	749	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50960	&&	QRGcomp <=	50989	) {L = EEPROM.read	(	151	);	 C1 = EEPROM.read	(	350	);	 C2 = EEPROM.read	(	550	);	 Z = EEPROM.read(	750	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	50990	&&	QRGcomp <=	51019	) {L = EEPROM.read	(	152	);	 C1 = EEPROM.read	(	351	);	 C2 = EEPROM.read	(	551	);	 Z = EEPROM.read(	751	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51020	&&	QRGcomp <=	51049	) {L = EEPROM.read	(	153	);	 C1 = EEPROM.read	(	352	);	 C2 = EEPROM.read	(	552	);	 Z = EEPROM.read(	752	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51050	&&	QRGcomp <=	51079	) {L = EEPROM.read	(	154	);	 C1 = EEPROM.read	(	353	);	 C2 = EEPROM.read	(	553	);	 Z = EEPROM.read(	753	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51080	&&	QRGcomp <=	51109	) {L = EEPROM.read	(	155	);	 C1 = EEPROM.read	(	354	);	 C2 = EEPROM.read	(	554	);	 Z = EEPROM.read(	754	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51110	&&	QRGcomp <=	51139	) {L = EEPROM.read	(	156	);	 C1 = EEPROM.read	(	355	);	 C2 = EEPROM.read	(	555	);	 Z = EEPROM.read(	755	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51140	&&	QRGcomp <=	51169	) {L = EEPROM.read	(	157	);	 C1 = EEPROM.read	(	356	);	 C2 = EEPROM.read	(	556	);	 Z = EEPROM.read(	756	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51170	&&	QRGcomp <=	51199	) {L = EEPROM.read	(	158	);	 C1 = EEPROM.read	(	357	);	 C2 = EEPROM.read	(	557	);	 Z = EEPROM.read(	757	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51200	&&	QRGcomp <=	51229	) {L = EEPROM.read	(	159	);	 C1 = EEPROM.read	(	358	);	 C2 = EEPROM.read	(	558	);	 Z = EEPROM.read(	758	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51230	&&	QRGcomp <=	51259	) {L = EEPROM.read	(	160	);	 C1 = EEPROM.read	(	359	);	 C2 = EEPROM.read	(	559	);	 Z = EEPROM.read(	759	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51260	&&	QRGcomp <=	51289	) {L = EEPROM.read	(	161	);	 C1 = EEPROM.read	(	360	);	 C2 = EEPROM.read	(	560	);	 Z = EEPROM.read(	760	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51290	&&	QRGcomp <=	51319	) {L = EEPROM.read	(	162	);	 C1 = EEPROM.read	(	361	);	 C2 = EEPROM.read	(	561	);	 Z = EEPROM.read(	761	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51320	&&	QRGcomp <=	51349	) {L = EEPROM.read	(	163	);	 C1 = EEPROM.read	(	362	);	 C2 = EEPROM.read	(	562	);	 Z = EEPROM.read(	762	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51350	&&	QRGcomp <=	51379	) {L = EEPROM.read	(	164	);	 C1 = EEPROM.read	(	363	);	 C2 = EEPROM.read	(	563	);	 Z = EEPROM.read(	763	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51380	&&	QRGcomp <=	51409	) {L = EEPROM.read	(	165	);	 C1 = EEPROM.read	(	364	);	 C2 = EEPROM.read	(	564	);	 Z = EEPROM.read(	764	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51410	&&	QRGcomp <=	51439	) {L = EEPROM.read	(	166	);	 C1 = EEPROM.read	(	365	);	 C2 = EEPROM.read	(	565	);	 Z = EEPROM.read(	765	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51440	&&	QRGcomp <=	51469	) {L = EEPROM.read	(	167	);	 C1 = EEPROM.read	(	366	);	 C2 = EEPROM.read	(	566	);	 Z = EEPROM.read(	766	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51470	&&	QRGcomp <=	51499	) {L = EEPROM.read	(	168	);	 C1 = EEPROM.read	(	367	);	 C2 = EEPROM.read	(	567	);	 Z = EEPROM.read(	767	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51500	&&	QRGcomp <=	51529	) {L = EEPROM.read	(	169	);	 C1 = EEPROM.read	(	368	);	 C2 = EEPROM.read	(	568	);	 Z = EEPROM.read(	768	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51530	&&	QRGcomp <=	51559	) {L = EEPROM.read	(	170	);	 C1 = EEPROM.read	(	369	);	 C2 = EEPROM.read	(	569	);	 Z = EEPROM.read(	769	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51560	&&	QRGcomp <=	51589	) {L = EEPROM.read	(	171	);	 C1 = EEPROM.read	(	370	);	 C2 = EEPROM.read	(	570	);	 Z = EEPROM.read(	770	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51590	&&	QRGcomp <=	51619	) {L = EEPROM.read	(	172	);	 C1 = EEPROM.read	(	371	);	 C2 = EEPROM.read	(	571	);	 Z = EEPROM.read(	771	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51620	&&	QRGcomp <=	51649	) {L = EEPROM.read	(	173	);	 C1 = EEPROM.read	(	372	);	 C2 = EEPROM.read	(	572	);	 Z = EEPROM.read(	772	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51650	&&	QRGcomp <=	51679	) {L = EEPROM.read	(	174	);	 C1 = EEPROM.read	(	373	);	 C2 = EEPROM.read	(	573	);	 Z = EEPROM.read(	773	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51680	&&	QRGcomp <=	51709	) {L = EEPROM.read	(	175	);	 C1 = EEPROM.read	(	374	);	 C2 = EEPROM.read	(	574	);	 Z = EEPROM.read(	774	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51710	&&	QRGcomp <=	51739	) {L = EEPROM.read	(	176	);	 C1 = EEPROM.read	(	375	);	 C2 = EEPROM.read	(	575	);	 Z = EEPROM.read(	775	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51740	&&	QRGcomp <=	51769	) {L = EEPROM.read	(	177	);	 C1 = EEPROM.read	(	376	);	 C2 = EEPROM.read	(	576	);	 Z = EEPROM.read(	776	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51770	&&	QRGcomp <=	51799	) {L = EEPROM.read	(	178	);	 C1 = EEPROM.read	(	377	);	 C2 = EEPROM.read	(	577	);	 Z = EEPROM.read(	777	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51800	&&	QRGcomp <=	51829	) {L = EEPROM.read	(	179	);	 C1 = EEPROM.read	(	378	);	 C2 = EEPROM.read	(	578	);	 Z = EEPROM.read(	778	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51830	&&	QRGcomp <=	51859	) {L = EEPROM.read	(	180	);	 C1 = EEPROM.read	(	379	);	 C2 = EEPROM.read	(	579	);	 Z = EEPROM.read(	779	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51860	&&	QRGcomp <=	51889	) {L = EEPROM.read	(	181	);	 C1 = EEPROM.read	(	380	);	 C2 = EEPROM.read	(	580	);	 Z = EEPROM.read(	780	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51890	&&	QRGcomp <=	51919	) {L = EEPROM.read	(	182	);	 C1 = EEPROM.read	(	381	);	 C2 = EEPROM.read	(	581	);	 Z = EEPROM.read(	781	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51920	&&	QRGcomp <=	51949	) {L = EEPROM.read	(	183	);	 C1 = EEPROM.read	(	382	);	 C2 = EEPROM.read	(	582	);	 Z = EEPROM.read(	782	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51950	&&	QRGcomp <=	51979	) {L = EEPROM.read	(	184	);	 C1 = EEPROM.read	(	383	);	 C2 = EEPROM.read	(	583	);	 Z = EEPROM.read(	783	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	
			else if 	(QRGcomp >=	51980	&&	QRGcomp <=	52000	) {L = EEPROM.read	(	185	);	 C1 = EEPROM.read	(	384	);	 C2 = EEPROM.read	(	584	);	 Z = EEPROM.read(	784	);		Serial1.print("t0.txt=");	Serial1.write(0x22); 	Serial1.print(C1); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);		Serial1.print("t1.txt=");	Serial1.write(0x22); 	Serial1.print(L); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial1.print("t2.txt=");	Serial1.write(0x22); 	Serial1.print(C2); 	Serial1.write(0x22); 	Serial1.write(NexT, 3);	 	Serial3.print('L'); 	Serial3.print(C1); 	Serial3.print('F'); 		Serial3.print('M'); 	Serial3.print(C2);	Serial3.print('F'); 		Serial3.print('N'); 	Serial3.print(L);	Serial3.print('F'); 	} 	

  }																							
  if (Lock == 1) {                            //    Lock - UnLock
    if (Z == 1) {
      Serial1.print("bt20.val=1"); 
      Serial1.write(NexT, 3);
      Serial1.print("bt20.txt="); 
      Serial1.write(0x22);
      Serial1.print("LOW-Z");
      Serial1.write(0x22); 
      Serial1.write(NexT, 3);
      } else {
      Serial1.print("bt20.val=0");
      Serial1.write(NexT, 3);
      Serial1.print("bt20.txt="); 
      Serial1.write(0x22);
      Serial1.print("HIGH-Z");
      Serial1.write(0x22); 
      Serial1.write(NexT, 3);
    }
    nexLoop(nex_lock_list);
    } else {
      if (bm == 0){
        nexLoop(nex_listen_Display1);
        } else if (bm == 1){
        nexLoop(nex_listen_Display2);
    }
  }
  Display();
}
void Config (){
  tv = EEPROM.read(900);
  cv = EEPROM.read(901);
  tm = EEPROM.read(902);
  ft = EEPROM.read(906);
  bm = EEPROM.read(908);
  if (Serial.available()  > 0) {              //    Diagnose-Serial
    Serialport0 = Serial.read();
    //Serial.print(Serialport0);
  }
  if (Serial1.available() > 0) {              //    Display-Serial
    char Serialport1 = Serial1.read();
    //Serial.print(Serialport1);
  }
  for (i = 0; i < 8; i++) {                   //    TRX-Serial
    if (Serial2.available() > 0) {
      TRXCAT[i] = Serial2.read();
    }
  }
  if (Serial3.available() > 0) {              //    Tuner-Serial
    Serialport3 = Serial3.read();
    Serial.print(Serialport3);
  }
  nexLoop(nex_listen_Config);
  Config();
}
																									
//_______________________________________________________________________________________________________________Nextion Display____________________________________________________________________________________
void a0PopCallback(void *ptr)  // Debug
{
  Serial1.print("page 3");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("t0.txt=");
  Serial1.write(0x22);
  Serial1.print(Call);
  Serial1.print("   Tuner   Setup");
  Serial1.write(0x22);
  Serial1.write(NexT, 3);

  Serial1.print("t2.txt=");
  Serial1.write(0x22);
  Serial1.print("Firmware ");
  Serial1.print(Firmware_v);
  Serial1.write(0x22);
  Serial1.write(NexT, 3);

  Setup = 1;
  tv = 0;
  cv = 0;
  tm = 0;
  ft = 0;
  bm = 0;

  tv = EEPROM.read(900);
  cv = EEPROM.read(901);
  tm = EEPROM.read(902);
  ft = EEPROM.read(906);
  bm = EEPROM.read(908);

  if (tv == 0 ) {
    Serial1.print("bs0.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=0"); 
    Serial1.write(NexT, 3);
    } else if (tv == 1 ) {
    Serial1.print("bs0.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=0"); 
    Serial1.write(NexT, 3);
    } else if (tv == 2 ) {
    Serial1.print("bs0.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=0"); 
    Serial1.write(NexT, 3);
    } else if (tv == 3 ) {
    Serial1.print("bs0.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=1"); 
    Serial1.write(NexT, 3);
  }
  if (cv == 0 ) {
    Serial1.print("bs4.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=0"); 
    Serial1.write(NexT, 3);
    } else if (cv == 1 ) {
    Serial1.print("bs4.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=0"); 
    Serial1.write(NexT, 3);
    } else if (cv == 2 ) {
    Serial1.print("bs4.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=0"); 
    Serial1.write(NexT, 3);
    } else if (cv == 3 ) {
    Serial1.print("bs4.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=1"); 
    Serial1.write(NexT, 3);
  }
  if (tm == 0 ) {
    Serial1.print("bs8.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs9.val=0"); 
    Serial1.write(NexT, 3);
    } else if (tm == 1 ) {
    Serial1.print("bs8.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs9.val=1"); 
    Serial1.write(NexT, 3);
  }
  if (bm == 0 ) {               //  Bauteile
    Serial1.print("bs10.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs11.val=0"); 
    Serial1.write(NexT, 3);
    } else if (bm == 1 ) {      //  3 Bauteile
    Serial1.print("bs10.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs11.val=1"); 
    Serial1.write(NexT, 3);
  }
  if (ft == 0 ) {               //  Funktionstest
    Serial1.print("bs12.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs13.val=1"); 
    Serial1.write(NexT, 3);
    } else if (ft == 1 ) {
    Serial1.print("bs12.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs13.val=0"); 
    Serial1.write(NexT, 3);
  }
  Config();
}

void a1PopCallback(void *ptr)  // Restart Tuner
{
  digitalWrite(A12, LOW);
  delay(25);
  digitalWrite(A12, HIGH);
  delay(25);
  digitalWrite(A12, LOW);
  delay(25);
  digitalWrite(A12, HIGH);
  delay(25);
  digitalWrite(A12, LOW);
  delay(25);
  digitalWrite(A12, LOW);
  delay(25);
  digitalWrite(A12, LOW);
  
    Serial1.print("page 3");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
}

void b0PopCallback(void *ptr)  // UP-C1
{
     if (C1 > 999) {
    C1 = 999;
  }
    if (C1 < 999) {
    C1 ++;
    Manual = 1;
    Serial3.print('A');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    CD1 = (C1ref + C1 * C1step);
    Serial1.print("t8.txt=");
    Serial1.write(0x22);
    Serial1.print(CD1 / 10);
    Serial1.print(".");
    Serial1.print(CD1 % 10);
    Serial1.print(" pF");
    Serial1.write(0x22);
    Serial1.write(NexT, 3); 
   }
}
void b1PopCallback(void *ptr)  // DOWN-C1
{
  if (C1 < 0) {
    C1 = 1;
  }
  if (C1 > 1) {
    C1--;
    Manual = 1;
    Serial3.print('A');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    CD1 = (C1ref + C1 * C1step);
    Serial1.print("t8.txt=");
    Serial1.write(0x22);
    Serial1.print(CD1 / 10);
    Serial1.print(".");
    Serial1.print(CD1 % 10);
    Serial1.print(" pF");
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
  }
}

void b2PopCallback(void *ptr)  // UP-L
{
   if (L > 999) {
    L = 999;
  }
    if (L < 999) {
    L ++;
    Manual = 1;
    Serial3.print('C');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    LD = (Lref + L * Lstep);
    Serial1.print("t6.txt=");
    Serial1.write(0x22);
    Serial1.print(LD / 1000);
    Serial1.print(".");
    Serial1.print(LD % 1000);
    Serial1.print(" uH");
    Serial1.write(0x22);
    Serial1.write(NexT, 3); 
   }
}
void b3PopCallback(void *ptr)  // DOWN-L
{
  if (L < 0) {
    L = 1;
  }
  if (L > 1) {
    L--;
    Manual = 1;
    Serial3.print('C');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    LD = (Lref + L * Lstep);
    Serial1.print("t6.txt=");
    Serial1.write(0x22);
    Serial1.print(LD / 1000);
    Serial1.print(".");
    Serial1.print(LD % 1000);
    Serial1.print(" uH");
    Serial1.write(0x22);
    Serial1.write(NexT, 3); 
  }
}

void b4PopCallback(void *ptr)  // UP-C2
{
   if (C2 > 999) {
    C2 = 999;
  }
    if (C2 < 99) {
    C2 ++;
  }
    Manual = 1;
    if (bm == 1) {
    Serial3.print('B');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    CD2 = (C2ref + C2 * C2step);
    Serial1.print("t10.txt=");
    Serial1.write(0x22);
    Serial1.print(CD2 / 10);
    Serial1.print(".");
    Serial1.print(CD2 % 10);
    Serial1.print(" pF");
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }
}
void b5PopCallback(void *ptr)  // DOWN-C2
{
  if (C2 < 0) {
    C2 = 1;
  }
  if (C2 > 1) {
    C2--;
  }
    Manual = 1;
    if (bm == 1) {
    Serial3.print('B');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    CD2 = (C2ref + C2 * C2step);
    Serial1.print("t10.txt=");
    Serial1.write(0x22);
    Serial1.print(CD2 / 10);
    Serial1.print(".");
    Serial1.print(CD2 % 10);
    Serial1.print(" pF");
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }
}

void b6PopCallback(void *ptr)  // Config
{
  Serial1.print("page 3");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("t0.txt=");
  Serial1.write(0x22);
  Serial1.print(Call);
  Serial1.print("   Tuner   Setup");
  Serial1.write(0x22);
  Serial1.write(NexT, 3);

  Serial1.print("t2.txt=");
  Serial1.write(0x22);
  Serial1.print("Firmware ");
  Serial1.print(Firmware_v);
  Serial1.write(0x22);
  Serial1.write(NexT, 3);

  Setup = 0;
  tv = 0;
  cv = 0;
  tm = 0;
  ft = 0;
  bm = 0;

  tv = EEPROM.read(900);
  cv = EEPROM.read(902);
  tm = EEPROM.read(904);
  ft = EEPROM.read(906);
  bm = EEPROM.read(908);

  if (tv == 0 ) {
    Serial1.print("bs0.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=0"); 
    Serial1.write(NexT, 3);
    } else if (tv == 1 ) {
    Serial1.print("bs0.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=0"); 
    Serial1.write(NexT, 3);
    } else if (tv == 2 ) {
    Serial1.print("bs0.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=0"); 
    Serial1.write(NexT, 3);
    } else if (tv == 3 ) {
    Serial1.print("bs0.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=1"); 
    Serial1.write(NexT, 3);
  }
  if (cv == 0 ) {
    Serial1.print("bs4.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=0"); 
    Serial1.write(NexT, 3);
    } else if (cv == 1 ) {
    Serial1.print("bs4.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=0"); 
    Serial1.write(NexT, 3);
    } else if (cv == 2 ) {
    Serial1.print("bs4.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=0"); 
    Serial1.write(NexT, 3);
    } else if (cv == 3 ) {
    Serial1.print("bs4.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=1"); 
    Serial1.write(NexT, 3);
  }
  if (tm == 0 ) {
    Serial1.print("bs8.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs9.val=0"); 
    Serial1.write(NexT, 3);
    } else if (tm == 1 ) {
    Serial1.print("bs8.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs9.val=1"); 
    Serial1.write(NexT, 3);
  }
  if (bm == 0 ) {               //  Bauteile
    Serial1.print("bs10.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs11.val=0"); 
    Serial1.write(NexT, 3);
    } else if (bm == 1 ) {      //  3 Bauteile
    Serial1.print("bs10.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs11.val=1"); 
    Serial1.write(NexT, 3);
  }
  if (ft == 0 ) {               //  Funktionstest
    Serial1.print("bs12.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs13.val=1"); 
    Serial1.write(NexT, 3);
    } else if (ft == 1 ) {
    Serial1.print("bs12.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs13.val=0"); 
    Serial1.write(NexT, 3);
  }
  Config();
}

void b7PopCallback(void *ptr)  // Save
{
	if  (Band== 160) { 	    // Band Speicher					
			EEPROM.put(	2000	,	 C1);
			EEPROM.put(	2001	,	 C2);
			EEPROM.put(	2002	,	 L);
			EEPROM.put(	2003	,	 Z);
		} else if (Band == 80) { 				
			EEPROM.put(	2004	,	 C1);
			EEPROM.put(	2005	,	 C2);
			EEPROM.put(	2006	,	 L);
			EEPROM.put(	2007	,	 Z);
		} else if (Band == 60) { 				
			EEPROM.put(	2008	,	 C1);
			EEPROM.put(	2009	,	 C2);
			EEPROM.put(	2010	,	 L);
			EEPROM.put(	2011	,	 Z);
		} else if (Band == 40) { 				
			EEPROM.put(	2012	,	 C1);
			EEPROM.put(	2013	,	 C2);
			EEPROM.put(	2014	,	 L);
			EEPROM.put(	2015	,	 Z);
		} else if (Band == 30) { 				
			EEPROM.put(	2016	,	 C1);
			EEPROM.put(	2017	,	 C2);
			EEPROM.put(	2018	,	 L);
			EEPROM.put(	2019	,	 Z);
		} else if (Band == 20) { 				
			EEPROM.put(	2020	,	 C1);
			EEPROM.put(	2021	,	 C2);
			EEPROM.put(	2022	,	 L);
			EEPROM.put(	2023	,	 Z);
		} else if (Band == 17) { 				
			EEPROM.put(	2024	,	 C1);
			EEPROM.put(	2025	,	 C2);
			EEPROM.put(	2026	,	 L);
			EEPROM.put(	2027	,	 Z);
		} else if (Band == 15) { 				
			EEPROM.put(	2028	,	 C1);
			EEPROM.put(	2029	,	 C2);
			EEPROM.put(	2030	,	 L);
			EEPROM.put(	2031	,	 Z);
		} else if (Band == 12) { 				
			EEPROM.put(	2032	,	 C1);
			EEPROM.put(	2033	,	 C2);
			EEPROM.put(	2034	,	 L);
			EEPROM.put(	2035	,	 Z);
		} else if (Band == 10) { 				
			EEPROM.put(	2036	,	 C1);
			EEPROM.put(	2037	,	 C2);
			EEPROM.put(	2038	,	 L);
			EEPROM.put(	2039	,	 Z);
		} else if (Band == 6) { 				
			EEPROM.put(	2040	,	 C1);
			EEPROM.put(	2041	,	 C2);
			EEPROM.put(	2042	,	 L);
			EEPROM.put(	2043	,	 Z);
	  }
  if (Manual == 0) {    // Frequenz Speicher
      if			  (QRGcomp >=	1810	&&	QRGcomp <=	1839	) {EEPROM.put	(	1	, L);	EEPROM.put	(	200	, C1);	EEPROM.put(	400	, C2);	EEPROM.put(	600	, Z);	Display();}
			else if   (QRGcomp >=	1840	&&	QRGcomp <=	1869	) {EEPROM.put	(	2	, L);	EEPROM.put	(	201	, C1);	EEPROM.put(	401	, C2);	EEPROM.put(	601	, Z);	Display();}
			else if 	(QRGcomp >=	1870	&&	QRGcomp <=	1899	) {EEPROM.put	(	3	, L);	EEPROM.put	(	202	, C1);	EEPROM.put(	402	, C2);	EEPROM.put(	602	, Z);	Display();}
			else if 	(QRGcomp >=	1900	&&	QRGcomp <=	1929	) {EEPROM.put	(	4	, L);	EEPROM.put	(	203	, C1);	EEPROM.put(	403	, C2);	EEPROM.put(	603	, Z);	Display();}
			else if 	(QRGcomp >=	1930	&&	QRGcomp <=	1959	) {EEPROM.put	(	5	, L);	EEPROM.put	(	204	, C1);	EEPROM.put(	404	, C2);	EEPROM.put(	604	, Z);	Display();}
			else if 	(QRGcomp >=	1960	&&	QRGcomp <=	1989	) {EEPROM.put	(	6	, L);	EEPROM.put	(	205	, C1);	EEPROM.put(	405	, C2);	EEPROM.put(	605	, Z);	Display();}
			else if 	(QRGcomp >=	1990	&&	QRGcomp <=	2000	) {EEPROM.put	(	7	, L);	EEPROM.put	(	206	, C1);	EEPROM.put(	406	, C2);	EEPROM.put(	606	, Z);	Display();}
			else if 	(QRGcomp >=	3500	&&	QRGcomp <=	3529	) {EEPROM.put	(	8	, L);	EEPROM.put	(	207	, C1);	EEPROM.put(	407	, C2);	EEPROM.put(	607	, Z);	Display();}
			else if 	(QRGcomp >=	3530	&&	QRGcomp <=	3559	) {EEPROM.put	(	9	, L);	EEPROM.put	(	208	, C1);	EEPROM.put(	408	, C2);	EEPROM.put(	608	, Z);	Display();}
			else if 	(QRGcomp >=	3560	&&	QRGcomp <=	3589	) {EEPROM.put	(	10	, L);	EEPROM.put	(	209	, C1);	EEPROM.put(	409	, C2);	EEPROM.put(	609	, Z);	Display();}
			else if 	(QRGcomp >=	3590	&&	QRGcomp <=	3619	) {EEPROM.put	(	11	, L);	EEPROM.put	(	210	, C1);	EEPROM.put(	410	, C2);	EEPROM.put(	610	, Z);	Display();}
			else if 	(QRGcomp >=	3620	&&	QRGcomp <=	3649	) {EEPROM.put	(	12	, L);	EEPROM.put	(	211	, C1);	EEPROM.put(	411	, C2);	EEPROM.put(	611	, Z);	Display();}
			else if 	(QRGcomp >=	3650	&&	QRGcomp <=	3679	) {EEPROM.put	(	13	, L);	EEPROM.put	(	212	, C1);	EEPROM.put(	412	, C2);	EEPROM.put(	612	, Z);	Display();}
			else if 	(QRGcomp >=	3680	&&	QRGcomp <=	3709	) {EEPROM.put	(	14	, L);	EEPROM.put	(	213	, C1);	EEPROM.put(	413	, C2);	EEPROM.put(	613	, Z);	Display();}
			else if 	(QRGcomp >=	3710	&&	QRGcomp <=	3739	) {EEPROM.put	(	15	, L);	EEPROM.put	(	214	, C1);	EEPROM.put(	414	, C2);	EEPROM.put(	614	, Z);	Display();}
			else if 	(QRGcomp >=	3740	&&	QRGcomp <=	3769	) {EEPROM.put	(	16	, L);	EEPROM.put	(	215	, C1);	EEPROM.put(	415	, C2);	EEPROM.put(	615	, Z);	Display();}
			else if 	(QRGcomp >=	3770	&&	QRGcomp <=	3800	) {EEPROM.put	(	17	, L);	EEPROM.put	(	216	, C1);	EEPROM.put(	416	, C2);	EEPROM.put(	616	, Z);	Display();}
			else if 	(QRGcomp >=	5350	&&	QRGcomp <=	5366	) {EEPROM.put	(	18	, L);	EEPROM.put	(	217	, C1);	EEPROM.put(	417	, C2);	EEPROM.put(	617	, Z);	Display();}
			else if 	(QRGcomp >=	7000	&&	QRGcomp <=	7029	) {EEPROM.put	(	19	, L);	EEPROM.put	(	218	, C1);	EEPROM.put(	418	, C2);	EEPROM.put(	618	, Z);	Display();}
			else if 	(QRGcomp >=	7030	&&	QRGcomp <=	7059	) {EEPROM.put	(	20	, L);	EEPROM.put	(	219	, C1);	EEPROM.put(	419	, C2);	EEPROM.put(	619	, Z);	Display();}
			else if 	(QRGcomp >=	7060	&&	QRGcomp <=	7089	) {EEPROM.put	(	21	, L);	EEPROM.put	(	220	, C1);	EEPROM.put(	420	, C2);	EEPROM.put(	620	, Z);	Display();}
			else if 	(QRGcomp >=	7090	&&	QRGcomp <=	7119	) {EEPROM.put	(	22	, L);	EEPROM.put	(	221	, C1);	EEPROM.put(	421	, C2);	EEPROM.put(	621	, Z);	Display();}
			else if 	(QRGcomp >=	7120	&&	QRGcomp <=	7149	) {EEPROM.put	(	23	, L);	EEPROM.put	(	222	, C1);	EEPROM.put(	422	, C2);	EEPROM.put(	622	, Z);	Display();}
			else if 	(QRGcomp >=	7150	&&	QRGcomp <=	7179	) {EEPROM.put	(	24	, L);	EEPROM.put	(	223	, C1);	EEPROM.put(	423	, C2);	EEPROM.put(	623	, Z);	Display();}
			else if 	(QRGcomp >=	7180	&&	QRGcomp <=	7200	) {EEPROM.put	(	25	, L);	EEPROM.put	(	224	, C1);	EEPROM.put(	424	, C2);	EEPROM.put(	624	, Z);	Display();}
			else if 	(QRGcomp >=	10100	&&	QRGcomp <=	10124	) {EEPROM.put	(	26	, L);	EEPROM.put	(	225	, C1);	EEPROM.put(	425	, C2);	EEPROM.put(	625	, Z);	Display();}
			else if 	(QRGcomp >=	10125	&&	QRGcomp <=	10150	) {EEPROM.put	(	27	, L);	EEPROM.put	(	226	, C1);	EEPROM.put(	426	, C2);	EEPROM.put(	626	, Z);	Display();}
			else if 	(QRGcomp >=	14000	&&	QRGcomp <=	14029	) {EEPROM.put	(	28	, L);	EEPROM.put	(	227	, C1);	EEPROM.put(	427	, C2);	EEPROM.put(	627	, Z);	Display();}
			else if 	(QRGcomp >=	14030	&&	QRGcomp <=	14059	) {EEPROM.put	(	29	, L);	EEPROM.put	(	228	, C1);	EEPROM.put(	428	, C2);	EEPROM.put(	628	, Z);	Display();}
			else if 	(QRGcomp >=	14060	&&	QRGcomp <=	14089	) {EEPROM.put	(	30	, L);	EEPROM.put	(	229	, C1);	EEPROM.put(	429	, C2);	EEPROM.put(	629	, Z);	Display();}
			else if 	(QRGcomp >=	14090	&&	QRGcomp <=	14119	) {EEPROM.put	(	31	, L);	EEPROM.put	(	230	, C1);	EEPROM.put(	430	, C2);	EEPROM.put(	630	, Z);	Display();}
			else if 	(QRGcomp >=	14120	&&	QRGcomp <=	14149	) {EEPROM.put	(	32	, L);	EEPROM.put	(	231	, C1);	EEPROM.put(	431	, C2);	EEPROM.put(	631	, Z);	Display();}
			else if 	(QRGcomp >=	14150	&&	QRGcomp <=	14179	) {EEPROM.put	(	33	, L);	EEPROM.put	(	232	, C1);	EEPROM.put(	432	, C2);	EEPROM.put(	632	, Z);	Display();}
			else if 	(QRGcomp >=	14180	&&	QRGcomp <=	14209	) {EEPROM.put	(	34	, L);	EEPROM.put	(	233	, C1);	EEPROM.put(	433	, C2);	EEPROM.put(	633	, Z);	Display();}
			else if 	(QRGcomp >=	14210	&&	QRGcomp <=	14239	) {EEPROM.put	(	35	, L);	EEPROM.put	(	234	, C1);	EEPROM.put(	434	, C2);	EEPROM.put(	634	, Z);	Display();}
			else if 	(QRGcomp >=	14240	&&	QRGcomp <=	14269	) {EEPROM.put	(	36	, L);	EEPROM.put	(	235	, C1);	EEPROM.put(	435	, C2);	EEPROM.put(	635	, Z);	Display();}
			else if 	(QRGcomp >=	14270	&&	QRGcomp <=	14299	) {EEPROM.put	(	37	, L);	EEPROM.put	(	236	, C1);	EEPROM.put(	436	, C2);	EEPROM.put(	636	, Z);	Display();}
			else if 	(QRGcomp >=	14300	&&	QRGcomp <=	14329	) {EEPROM.put	(	38	, L);	EEPROM.put	(	237	, C1);	EEPROM.put(	437	, C2);	EEPROM.put(	637	, Z);	Display();}
			else if 	(QRGcomp >=	14330	&&	QRGcomp <=	14350	) {EEPROM.put	(	39	, L);	EEPROM.put	(	238	, C1);	EEPROM.put(	438	, C2);	EEPROM.put(	638	, Z);	Display();}
			else if 	(QRGcomp >=	18068	&&	QRGcomp <=	18097	) {EEPROM.put	(	40	, L);	EEPROM.put	(	239	, C1);	EEPROM.put(	439	, C2);	EEPROM.put(	639	, Z);	Display();}
			else if 	(QRGcomp >=	18098	&&	QRGcomp <=	18127	) {EEPROM.put	(	41	, L);	EEPROM.put	(	240	, C1);	EEPROM.put(	440	, C2);	EEPROM.put(	640	, Z);	Display();}
			else if 	(QRGcomp >=	18128	&&	QRGcomp <=	18157	) {EEPROM.put	(	42	, L);	EEPROM.put	(	241	, C1);	EEPROM.put(	441	, C2);	EEPROM.put(	641	, Z);	Display();}
			else if 	(QRGcomp >=	18158	&&	QRGcomp <=	18168	) {EEPROM.put	(	43	, L);	EEPROM.put	(	242	, C1);	EEPROM.put(	442	, C2);	EEPROM.put(	642	, Z);	Display();}
			else if 	(QRGcomp >=	21000	&&	QRGcomp <=	21029	) {EEPROM.put	(	44	, L);	EEPROM.put	(	243	, C1);	EEPROM.put(	443	, C2);	EEPROM.put(	643	, Z);	Display();}
			else if 	(QRGcomp >=	21030	&&	QRGcomp <=	21059	) {EEPROM.put	(	45	, L);	EEPROM.put	(	244	, C1);	EEPROM.put(	444	, C2);	EEPROM.put(	644	, Z);	Display();}
			else if 	(QRGcomp >=	21060	&&	QRGcomp <=	21089	) {EEPROM.put	(	46	, L);	EEPROM.put	(	245	, C1);	EEPROM.put(	445	, C2);	EEPROM.put(	645	, Z);	Display();}
			else if 	(QRGcomp >=	21090	&&	QRGcomp <=	21119	) {EEPROM.put	(	47	, L);	EEPROM.put	(	246	, C1);	EEPROM.put(	446	, C2);	EEPROM.put(	646	, Z);	Display();}
			else if 	(QRGcomp >=	21120	&&	QRGcomp <=	21149	) {EEPROM.put	(	48	, L);	EEPROM.put	(	247	, C1);	EEPROM.put(	447	, C2);	EEPROM.put(	647	, Z);	Display();}
			else if 	(QRGcomp >=	21150	&&	QRGcomp <=	21179	) {EEPROM.put	(	49	, L);	EEPROM.put	(	248	, C1);	EEPROM.put(	448	, C2);	EEPROM.put(	648	, Z);	Display();}
			else if 	(QRGcomp >=	21180	&&	QRGcomp <=	21209	) {EEPROM.put	(	50	, L);	EEPROM.put	(	249	, C1);	EEPROM.put(	449	, C2);	EEPROM.put(	649	, Z);	Display();}
			else if 	(QRGcomp >=	21210	&&	QRGcomp <=	21239	) {EEPROM.put	(	51	, L);	EEPROM.put	(	250	, C1);	EEPROM.put(	450	, C2);	EEPROM.put(	650	, Z);	Display();}
			else if 	(QRGcomp >=	21240	&&	QRGcomp <=	21269	) {EEPROM.put	(	52	, L);	EEPROM.put	(	251	, C1);	EEPROM.put(	451	, C2);	EEPROM.put(	651	, Z);	Display();}
			else if 	(QRGcomp >=	21270	&&	QRGcomp <=	21299	) {EEPROM.put	(	53	, L);	EEPROM.put	(	252	, C1);	EEPROM.put(	452	, C2);	EEPROM.put(	652	, Z);	Display();}
			else if 	(QRGcomp >=	21300	&&	QRGcomp <=	21329	) {EEPROM.put	(	54	, L);	EEPROM.put	(	253	, C1);	EEPROM.put(	453	, C2);	EEPROM.put(	653	, Z);	Display();}
			else if 	(QRGcomp >=	21330	&&	QRGcomp <=	21359	) {EEPROM.put	(	55	, L);	EEPROM.put	(	254	, C1);	EEPROM.put(	454	, C2);	EEPROM.put(	654	, Z);	Display();}
			else if 	(QRGcomp >=	21360	&&	QRGcomp <=	21389	) {EEPROM.put	(	56	, L);	EEPROM.put	(	255	, C1);	EEPROM.put(	455	, C2);	EEPROM.put(	655	, Z);	Display();}
			else if 	(QRGcomp >=	21390	&&	QRGcomp <=	21419	) {EEPROM.put	(	57	, L);	EEPROM.put	(	256	, C1);	EEPROM.put(	456	, C2);	EEPROM.put(	656	, Z);	Display();}
			else if 	(QRGcomp >=	21420	&&	QRGcomp <=	21450	) {EEPROM.put	(	58	, L);	EEPROM.put	(	257	, C1);	EEPROM.put(	457	, C2);	EEPROM.put(	657	, Z);	Display();}
			else if 	(QRGcomp >=	24890	&&	QRGcomp <=	24919	) {EEPROM.put	(	59	, L);	EEPROM.put	(	258	, C1);	EEPROM.put(	458	, C2);	EEPROM.put(	658	, Z);	Display();}
			else if 	(QRGcomp >=	24949	&&	QRGcomp <=	24979	) {EEPROM.put	(	60	, L);	EEPROM.put	(	259	, C1);	EEPROM.put(	459	, C2);	EEPROM.put(	659	, Z);	Display();}
			else if 	(QRGcomp >=	24980	&&	QRGcomp <=	24990	) {EEPROM.put	(	61	, L);	EEPROM.put	(	260	, C1);	EEPROM.put(	460	, C2);	EEPROM.put(	660	, Z);	Display();}
			else if 	(QRGcomp >=	28000	&&	QRGcomp <=	28029	) {EEPROM.put	(	62	, L);	EEPROM.put	(	261	, C1);	EEPROM.put(	461	, C2);	EEPROM.put(	661	, Z);	Display();}
			else if 	(QRGcomp >=	28030	&&	QRGcomp <=	28059	) {EEPROM.put	(	63	, L);	EEPROM.put	(	262	, C1);	EEPROM.put(	462	, C2);	EEPROM.put(	662	, Z);	Display();}
			else if 	(QRGcomp >=	28060	&&	QRGcomp <=	28089	) {EEPROM.put	(	64	, L);	EEPROM.put	(	263	, C1);	EEPROM.put(	463	, C2);	EEPROM.put(	663	, Z);	Display();}
			else if 	(QRGcomp >=	28090	&&	QRGcomp <=	28119	) {EEPROM.put	(	65	, L);	EEPROM.put	(	264	, C1);	EEPROM.put(	464	, C2);	EEPROM.put(	664	, Z);	Display();}
			else if 	(QRGcomp >=	28120	&&	QRGcomp <=	28149	) {EEPROM.put	(	66	, L);	EEPROM.put	(	265	, C1);	EEPROM.put(	465	, C2);	EEPROM.put(	665	, Z);	Display();}
			else if 	(QRGcomp >=	28150	&&	QRGcomp <=	28179	) {EEPROM.put	(	67	, L);	EEPROM.put	(	266	, C1);	EEPROM.put(	466	, C2);	EEPROM.put(	666	, Z);	Display();}
			else if 	(QRGcomp >=	28180	&&	QRGcomp <=	28209	) {EEPROM.put	(	68	, L);	EEPROM.put	(	267	, C1);	EEPROM.put(	467	, C2);	EEPROM.put(	667	, Z);	Display();}
			else if 	(QRGcomp >=	28210	&&	QRGcomp <=	28239	) {EEPROM.put	(	69	, L);	EEPROM.put	(	268	, C1);	EEPROM.put(	468	, C2);	EEPROM.put(	668	, Z);	Display();}
			else if 	(QRGcomp >=	28240	&&	QRGcomp <=	28269	) {EEPROM.put	(	70	, L);	EEPROM.put	(	269	, C1);	EEPROM.put(	469	, C2);	EEPROM.put(	669	, Z);	Display();}
			else if 	(QRGcomp >=	28270	&&	QRGcomp <=	28299	) {EEPROM.put	(	71	, L);	EEPROM.put	(	270	, C1);	EEPROM.put(	470	, C2);	EEPROM.put(	670	, Z);	Display();}
			else if 	(QRGcomp >=	28300	&&	QRGcomp <=	28329	) {EEPROM.put	(	72	, L);	EEPROM.put	(	271	, C1);	EEPROM.put(	471	, C2);	EEPROM.put(	671	, Z);	Display();}
			else if 	(QRGcomp >=	28330	&&	QRGcomp <=	28359	) {EEPROM.put	(	73	, L);	EEPROM.put	(	272	, C1);	EEPROM.put(	472	, C2);	EEPROM.put(	672	, Z);	Display();}
			else if 	(QRGcomp >=	28360	&&	QRGcomp <=	28389	) {EEPROM.put	(	74	, L);	EEPROM.put	(	273	, C1);	EEPROM.put(	473	, C2);	EEPROM.put(	673	, Z);	Display();}
			else if 	(QRGcomp >=	28390	&&	QRGcomp <=	28419	) {EEPROM.put	(	75	, L);	EEPROM.put	(	274	, C1);	EEPROM.put(	474	, C2);	EEPROM.put(	674	, Z);	Display();}
			else if 	(QRGcomp >=	28420	&&	QRGcomp <=	28449	) {EEPROM.put	(	76	, L);	EEPROM.put	(	275	, C1);	EEPROM.put(	475	, C2);	EEPROM.put(	675	, Z);	Display();}
			else if 	(QRGcomp >=	28450	&&	QRGcomp <=	28479	) {EEPROM.put	(	77	, L);	EEPROM.put	(	276	, C1);	EEPROM.put(	476	, C2);	EEPROM.put(	676	, Z);	Display();}
			else if 	(QRGcomp >=	28480	&&	QRGcomp <=	28509	) {EEPROM.put	(	78	, L);	EEPROM.put	(	277	, C1);	EEPROM.put(	477	, C2);	EEPROM.put(	677	, Z);	Display();}
			else if 	(QRGcomp >=	28510	&&	QRGcomp <=	28539	) {EEPROM.put	(	79	, L);	EEPROM.put	(	278	, C1);	EEPROM.put(	478	, C2);	EEPROM.put(	678	, Z);	Display();}
			else if 	(QRGcomp >=	28540	&&	QRGcomp <=	28569	) {EEPROM.put	(	80	, L);	EEPROM.put	(	279	, C1);	EEPROM.put(	479	, C2);	EEPROM.put(	679	, Z);	Display();}
			else if 	(QRGcomp >=	28570	&&	QRGcomp <=	28599	) {EEPROM.put	(	81	, L);	EEPROM.put	(	280	, C1);	EEPROM.put(	480	, C2);	EEPROM.put(	680	, Z);	Display();}
			else if 	(QRGcomp >=	28600	&&	QRGcomp <=	28629	) {EEPROM.put	(	82	, L);	EEPROM.put	(	281	, C1);	EEPROM.put(	481	, C2);	EEPROM.put(	681	, Z);	Display();}
			else if 	(QRGcomp >=	28630	&&	QRGcomp <=	28659	) {EEPROM.put	(	83	, L);	EEPROM.put	(	282	, C1);	EEPROM.put(	482	, C2);	EEPROM.put(	682	, Z);	Display();}
			else if 	(QRGcomp >=	28660	&&	QRGcomp <=	28689	) {EEPROM.put	(	84	, L);	EEPROM.put	(	283	, C1);	EEPROM.put(	483	, C2);	EEPROM.put(	683	, Z);	Display();}
			else if 	(QRGcomp >=	28690	&&	QRGcomp <=	28719	) {EEPROM.put	(	85	, L);	EEPROM.put	(	284	, C1);	EEPROM.put(	484	, C2);	EEPROM.put(	684	, Z);	Display();}
			else if 	(QRGcomp >=	28720	&&	QRGcomp <=	28749	) {EEPROM.put	(	86	, L);	EEPROM.put	(	285	, C1);	EEPROM.put(	485	, C2);	EEPROM.put(	685	, Z);	Display();}
			else if 	(QRGcomp >=	28750	&&	QRGcomp <=	28779	) {EEPROM.put	(	87	, L);	EEPROM.put	(	286	, C1);	EEPROM.put(	486	, C2);	EEPROM.put(	686	, Z);	Display();}
			else if 	(QRGcomp >=	28780	&&	QRGcomp <=	28809	) {EEPROM.put	(	88	, L);	EEPROM.put	(	287	, C1);	EEPROM.put(	487	, C2);	EEPROM.put(	687	, Z);	Display();}
			else if 	(QRGcomp >=	28810	&&	QRGcomp <=	28839	) {EEPROM.put	(	89	, L);	EEPROM.put	(	288	, C1);	EEPROM.put(	488	, C2);	EEPROM.put(	688	, Z);	Display();}
			else if 	(QRGcomp >=	28840	&&	QRGcomp <=	28869	) {EEPROM.put	(	90	, L);	EEPROM.put	(	289	, C1);	EEPROM.put(	489	, C2);	EEPROM.put(	689	, Z);	Display();}
			else if 	(QRGcomp >=	28870	&&	QRGcomp <=	28899	) {EEPROM.put	(	91	, L);	EEPROM.put	(	290	, C1);	EEPROM.put(	490	, C2);	EEPROM.put(	690	, Z);	Display();}
			else if 	(QRGcomp >=	28900	&&	QRGcomp <=	28929	) {EEPROM.put	(	92	, L);	EEPROM.put	(	291	, C1);	EEPROM.put(	491	, C2);	EEPROM.put(	691	, Z);	Display();}
			else if 	(QRGcomp >=	28930	&&	QRGcomp <=	28959	) {EEPROM.put	(	93	, L);	EEPROM.put	(	292	, C1);	EEPROM.put(	492	, C2);	EEPROM.put(	692	, Z);	Display();}
			else if 	(QRGcomp >=	28960	&&	QRGcomp <=	28989	) {EEPROM.put	(	94	, L);	EEPROM.put	(	293	, C1);	EEPROM.put(	493	, C2);	EEPROM.put(	693	, Z);	Display();}
			else if 	(QRGcomp >=	28990	&&	QRGcomp <=	29019	) {EEPROM.put	(	95	, L);	EEPROM.put	(	294	, C1);	EEPROM.put(	494	, C2);	EEPROM.put(	694	, Z);	Display();}
			else if 	(QRGcomp >=	29020	&&	QRGcomp <=	29049	) {EEPROM.put	(	96	, L);	EEPROM.put	(	295	, C1);	EEPROM.put(	495	, C2);	EEPROM.put(	695	, Z);	Display();}
			else if 	(QRGcomp >=	29050	&&	QRGcomp <=	29079	) {EEPROM.put	(	97	, L);	EEPROM.put	(	296	, C1);	EEPROM.put(	496	, C2);	EEPROM.put(	696	, Z);	Display();}
			else if 	(QRGcomp >=	29080	&&	QRGcomp <=	29109	) {EEPROM.put	(	98	, L);	EEPROM.put	(	297	, C1);	EEPROM.put(	497	, C2);	EEPROM.put(	697	, Z);	Display();}
			else if 	(QRGcomp >=	29110	&&	QRGcomp <=	29139	) {EEPROM.put	(	99	, L);	EEPROM.put	(	298	, C1);	EEPROM.put(	498	, C2);	EEPROM.put(	698	, Z);	Display();}
			else if 	(QRGcomp >=	29140	&&	QRGcomp <=	29169	) {EEPROM.put	(	100	, L);	EEPROM.put	(	299	, C1);	EEPROM.put(	499	, C2);	EEPROM.put(	699	, Z);	Display();}
			else if 	(QRGcomp >=	29170	&&	QRGcomp <=	29199	) {EEPROM.put	(	101	, L);	EEPROM.put	(	300	, C1);	EEPROM.put(	500	, C2);	EEPROM.put(	700	, Z);	Display();}
			else if 	(QRGcomp >=	29200	&&	QRGcomp <=	29229	) {EEPROM.put	(	102	, L);	EEPROM.put	(	301	, C1);	EEPROM.put(	501	, C2);	EEPROM.put(	701	, Z);	Display();}
			else if 	(QRGcomp >=	29230	&&	QRGcomp <=	29259	) {EEPROM.put	(	103	, L);	EEPROM.put	(	302	, C1);	EEPROM.put(	502	, C2);	EEPROM.put(	702	, Z);	Display();}
			else if 	(QRGcomp >=	29260	&&	QRGcomp <=	29289	) {EEPROM.put	(	104	, L);	EEPROM.put	(	303	, C1);	EEPROM.put(	503	, C2);	EEPROM.put(	703	, Z);	Display();}
			else if 	(QRGcomp >=	29290	&&	QRGcomp <=	29319	) {EEPROM.put	(	105	, L);	EEPROM.put	(	304	, C1);	EEPROM.put(	504	, C2);	EEPROM.put(	704	, Z);	Display();}
			else if 	(QRGcomp >=	29320	&&	QRGcomp <=	29349	) {EEPROM.put	(	106	, L);	EEPROM.put	(	305	, C1);	EEPROM.put(	505	, C2);	EEPROM.put(	705	, Z);	Display();}
			else if 	(QRGcomp >=	29350	&&	QRGcomp <=	29379	) {EEPROM.put	(	107	, L);	EEPROM.put	(	306	, C1);	EEPROM.put(	506	, C2);	EEPROM.put(	706	, Z);	Display();}
			else if 	(QRGcomp >=	29380	&&	QRGcomp <=	29409	) {EEPROM.put	(	108	, L);	EEPROM.put	(	307	, C1);	EEPROM.put(	507	, C2);	EEPROM.put(	707	, Z);	Display();}
			else if 	(QRGcomp >=	29410	&&	QRGcomp <=	29439	) {EEPROM.put	(	109	, L);	EEPROM.put	(	308	, C1);	EEPROM.put(	508	, C2);	EEPROM.put(	708	, Z);	Display();}
			else if 	(QRGcomp >=	29440	&&	QRGcomp <=	29469	) {EEPROM.put	(	110	, L);	EEPROM.put	(	309	, C1);	EEPROM.put(	509	, C2);	EEPROM.put(	709	, Z);	Display();}
			else if 	(QRGcomp >=	29470	&&	QRGcomp <=	29499	) {EEPROM.put	(	111	, L);	EEPROM.put	(	310	, C1);	EEPROM.put(	510	, C2);	EEPROM.put(	710	, Z);	Display();}
			else if 	(QRGcomp >=	29500	&&	QRGcomp <=	29529	) {EEPROM.put	(	112	, L);	EEPROM.put	(	311	, C1);	EEPROM.put(	511	, C2);	EEPROM.put(	711	, Z);	Display();}
			else if 	(QRGcomp >=	29530	&&	QRGcomp <=	29559	) {EEPROM.put	(	113	, L);	EEPROM.put	(	312	, C1);	EEPROM.put(	512	, C2);	EEPROM.put(	712	, Z);	Display();}
			else if 	(QRGcomp >=	29560	&&	QRGcomp <=	29589	) {EEPROM.put	(	114	, L);	EEPROM.put	(	313	, C1);	EEPROM.put(	513	, C2);	EEPROM.put(	713	, Z);	Display();}
			else if 	(QRGcomp >=	29590	&&	QRGcomp <=	29619	) {EEPROM.put	(	115	, L);	EEPROM.put	(	314	, C1);	EEPROM.put(	514	, C2);	EEPROM.put(	714	, Z);	Display();}
			else if 	(QRGcomp >=	29620	&&	QRGcomp <=	29649	) {EEPROM.put	(	116	, L);	EEPROM.put	(	315	, C1);	EEPROM.put(	515	, C2);	EEPROM.put(	715	, Z);	Display();}
			else if 	(QRGcomp >=	29650	&&	QRGcomp <=	29679	) {EEPROM.put	(	117	, L);	EEPROM.put	(	316	, C1);	EEPROM.put(	516	, C2);	EEPROM.put(	716	, Z);	Display();}
			else if 	(QRGcomp >=	29680	&&	QRGcomp <=	28059	) {EEPROM.put	(	118	, L);	EEPROM.put	(	317	, C1);	EEPROM.put(	517	, C2);	EEPROM.put(	717	, Z);	Display();}
			else if 	(QRGcomp >=	50000	&&	QRGcomp <=	50029	) {EEPROM.put	(	119	, L);	EEPROM.put	(	318	, C1);	EEPROM.put(	518	, C2);	EEPROM.put(	718	, Z);	Display();}
			else if 	(QRGcomp >=	50030	&&	QRGcomp <=	50059	) {EEPROM.put	(	120	, L);	EEPROM.put	(	319	, C1);	EEPROM.put(	519	, C2);	EEPROM.put(	719	, Z);	Display();}
			else if 	(QRGcomp >=	50060	&&	QRGcomp <=	50089	) {EEPROM.put	(	121	, L);	EEPROM.put	(	320	, C1);	EEPROM.put(	520	, C2);	EEPROM.put(	720	, Z);	Display();}
			else if 	(QRGcomp >=	50090	&&	QRGcomp <=	50119	) {EEPROM.put	(	122	, L);	EEPROM.put	(	321	, C1);	EEPROM.put(	521	, C2);	EEPROM.put(	721	, Z);	Display();}
			else if 	(QRGcomp >=	50120	&&	QRGcomp <=	50149	) {EEPROM.put	(	123	, L);	EEPROM.put	(	322	, C1);	EEPROM.put(	522	, C2);	EEPROM.put(	722	, Z);	Display();}
			else if 	(QRGcomp >=	50150	&&	QRGcomp <=	50179	) {EEPROM.put	(	124	, L);	EEPROM.put	(	323	, C1);	EEPROM.put(	523	, C2);	EEPROM.put(	723	, Z);	Display();}
			else if 	(QRGcomp >=	50180	&&	QRGcomp <=	50209	) {EEPROM.put	(	125	, L);	EEPROM.put	(	324	, C1);	EEPROM.put(	524	, C2);	EEPROM.put(	724	, Z);	Display();}
			else if 	(QRGcomp >=	50210	&&	QRGcomp <=	50239	) {EEPROM.put	(	126	, L);	EEPROM.put	(	325	, C1);	EEPROM.put(	525	, C2);	EEPROM.put(	725	, Z);	Display();}
			else if 	(QRGcomp >=	50240	&&	QRGcomp <=	50269	) {EEPROM.put	(	127	, L);	EEPROM.put	(	326	, C1);	EEPROM.put(	526	, C2);	EEPROM.put(	726	, Z);	Display();}
			else if 	(QRGcomp >=	50270	&&	QRGcomp <=	50299	) {EEPROM.put	(	128	, L);	EEPROM.put	(	327	, C1);	EEPROM.put(	527	, C2);	EEPROM.put(	727	, Z);	Display();}
			else if 	(QRGcomp >=	50300	&&	QRGcomp <=	50329	) {EEPROM.put	(	129	, L);	EEPROM.put	(	328	, C1);	EEPROM.put(	528	, C2);	EEPROM.put(	728	, Z);	Display();}
			else if 	(QRGcomp >=	50330	&&	QRGcomp <=	50359	) {EEPROM.put	(	130	, L);	EEPROM.put	(	329	, C1);	EEPROM.put(	529	, C2);	EEPROM.put(	729	, Z);	Display();}
			else if 	(QRGcomp >=	50360	&&	QRGcomp <=	50389	) {EEPROM.put	(	131	, L);	EEPROM.put	(	330	, C1);	EEPROM.put(	530	, C2);	EEPROM.put(	730	, Z);	Display();}
			else if 	(QRGcomp >=	50390	&&	QRGcomp <=	50419	) {EEPROM.put	(	132	, L);	EEPROM.put	(	331	, C1);	EEPROM.put(	531	, C2);	EEPROM.put(	731	, Z);	Display();}
			else if 	(QRGcomp >=	50420	&&	QRGcomp <=	50449	) {EEPROM.put	(	133	, L);	EEPROM.put	(	332	, C1);	EEPROM.put(	532	, C2);	EEPROM.put(	732	, Z);	Display();}
			else if 	(QRGcomp >=	50450	&&	QRGcomp <=	50479	) {EEPROM.put	(	134	, L);	EEPROM.put	(	333	, C1);	EEPROM.put(	533	, C2);	EEPROM.put(	733	, Z);	Display();}
			else if 	(QRGcomp >=	50480	&&	QRGcomp <=	50509	) {EEPROM.put	(	135	, L);	EEPROM.put	(	334	, C1);	EEPROM.put(	534	, C2);	EEPROM.put(	734	, Z);	Display();}
			else if 	(QRGcomp >=	50510	&&	QRGcomp <=	50539	) {EEPROM.put	(	136	, L);	EEPROM.put	(	335	, C1);	EEPROM.put(	535	, C2);	EEPROM.put(	735	, Z);	Display();}
			else if 	(QRGcomp >=	50540	&&	QRGcomp <=	50569	) {EEPROM.put	(	137	, L);	EEPROM.put	(	336	, C1);	EEPROM.put(	536	, C2);	EEPROM.put(	736	, Z);	Display();}
			else if 	(QRGcomp >=	50570	&&	QRGcomp <=	50599	) {EEPROM.put	(	138	, L);	EEPROM.put	(	337	, C1);	EEPROM.put(	537	, C2);	EEPROM.put(	737	, Z);	Display();}
			else if 	(QRGcomp >=	50600	&&	QRGcomp <=	50629	) {EEPROM.put	(	139	, L);	EEPROM.put	(	338	, C1);	EEPROM.put(	538	, C2);	EEPROM.put(	738	, Z);	Display();}
			else if 	(QRGcomp >=	50630	&&	QRGcomp <=	50659	) {EEPROM.put	(	140	, L);	EEPROM.put	(	339	, C1);	EEPROM.put(	539	, C2);	EEPROM.put(	739	, Z);	Display();}
			else if 	(QRGcomp >=	50660	&&	QRGcomp <=	50689	) {EEPROM.put	(	141	, L);	EEPROM.put	(	340	, C1);	EEPROM.put(	540	, C2);	EEPROM.put(	740	, Z);	Display();}
			else if 	(QRGcomp >=	50690	&&	QRGcomp <=	50719	) {EEPROM.put	(	142	, L);	EEPROM.put	(	341	, C1);	EEPROM.put(	541	, C2);	EEPROM.put(	741	, Z);	Display();}
			else if 	(QRGcomp >=	50720	&&	QRGcomp <=	50749	) {EEPROM.put	(	143	, L);	EEPROM.put	(	342	, C1);	EEPROM.put(	542	, C2);	EEPROM.put(	742	, Z);	Display();}
			else if 	(QRGcomp >=	50750	&&	QRGcomp <=	50779	) {EEPROM.put	(	144	, L);	EEPROM.put	(	343	, C1);	EEPROM.put(	543	, C2);	EEPROM.put(	743	, Z);	Display();}
			else if 	(QRGcomp >=	50780	&&	QRGcomp <=	50809	) {EEPROM.put	(	145	, L);	EEPROM.put	(	344	, C1);	EEPROM.put(	544	, C2);	EEPROM.put(	744	, Z);	Display();}
			else if 	(QRGcomp >=	50810	&&	QRGcomp <=	50839	) {EEPROM.put	(	146	, L);	EEPROM.put	(	345	, C1);	EEPROM.put(	545	, C2);	EEPROM.put(	745	, Z);	Display();}
			else if 	(QRGcomp >=	50840	&&	QRGcomp <=	50869	) {EEPROM.put	(	147	, L);	EEPROM.put	(	346	, C1);	EEPROM.put(	546	, C2);	EEPROM.put(	746	, Z);	Display();}
			else if 	(QRGcomp >=	50870	&&	QRGcomp <=	50899	) {EEPROM.put	(	148	, L);	EEPROM.put	(	347	, C1);	EEPROM.put(	547	, C2);	EEPROM.put(	747	, Z);	Display();}
			else if 	(QRGcomp >=	50900	&&	QRGcomp <=	50929	) {EEPROM.put	(	149	, L);	EEPROM.put	(	348	, C1);	EEPROM.put(	548	, C2);	EEPROM.put(	748	, Z);	Display();}
			else if 	(QRGcomp >=	50930	&&	QRGcomp <=	50959	) {EEPROM.put	(	150	, L);	EEPROM.put	(	349	, C1);	EEPROM.put(	549	, C2);	EEPROM.put(	749	, Z);	Display();}
			else if 	(QRGcomp >=	50960	&&	QRGcomp <=	50989	) {EEPROM.put	(	151	, L);	EEPROM.put	(	350	, C1);	EEPROM.put(	550	, C2);	EEPROM.put(	750	, Z);	Display();}
			else if 	(QRGcomp >=	50990	&&	QRGcomp <=	51019	) {EEPROM.put	(	152	, L);	EEPROM.put	(	351	, C1);	EEPROM.put(	551	, C2);	EEPROM.put(	751	, Z);	Display();}
			else if 	(QRGcomp >=	51020	&&	QRGcomp <=	51049	) {EEPROM.put	(	153	, L);	EEPROM.put	(	352	, C1);	EEPROM.put(	552	, C2);	EEPROM.put(	752	, Z);	Display();}
			else if 	(QRGcomp >=	51050	&&	QRGcomp <=	51079	) {EEPROM.put	(	154	, L);	EEPROM.put	(	353	, C1);	EEPROM.put(	553	, C2);	EEPROM.put(	753	, Z);	Display();}
			else if 	(QRGcomp >=	51080	&&	QRGcomp <=	51109	) {EEPROM.put	(	155	, L);	EEPROM.put	(	354	, C1);	EEPROM.put(	554	, C2);	EEPROM.put(	754	, Z);	Display();}
			else if 	(QRGcomp >=	51110	&&	QRGcomp <=	51139	) {EEPROM.put	(	156	, L);	EEPROM.put	(	355	, C1);	EEPROM.put(	555	, C2);	EEPROM.put(	755	, Z);	Display();}
			else if 	(QRGcomp >=	51140	&&	QRGcomp <=	51169	) {EEPROM.put	(	157	, L);	EEPROM.put	(	356	, C1);	EEPROM.put(	556	, C2);	EEPROM.put(	756	, Z);	Display();}
			else if 	(QRGcomp >=	51170	&&	QRGcomp <=	51199	) {EEPROM.put	(	158	, L);	EEPROM.put	(	357	, C1);	EEPROM.put(	557	, C2);	EEPROM.put(	757	, Z);	Display();}
			else if 	(QRGcomp >=	51200	&&	QRGcomp <=	51229	) {EEPROM.put	(	159	, L);	EEPROM.put	(	358	, C1);	EEPROM.put(	558	, C2);	EEPROM.put(	758	, Z);	Display();}
			else if 	(QRGcomp >=	51230	&&	QRGcomp <=	51259	) {EEPROM.put	(	160	, L);	EEPROM.put	(	359	, C1);	EEPROM.put(	559	, C2);	EEPROM.put(	759	, Z);	Display();}
			else if 	(QRGcomp >=	51260	&&	QRGcomp <=	51289	) {EEPROM.put	(	161	, L);	EEPROM.put	(	360	, C1);	EEPROM.put(	560	, C2);	EEPROM.put(	760	, Z);	Display();}
			else if 	(QRGcomp >=	51290	&&	QRGcomp <=	51319	) {EEPROM.put	(	162	, L);	EEPROM.put	(	361	, C1);	EEPROM.put(	561	, C2);	EEPROM.put(	761	, Z);	Display();}
			else if 	(QRGcomp >=	51320	&&	QRGcomp <=	51349	) {EEPROM.put	(	163	, L);	EEPROM.put	(	362	, C1);	EEPROM.put(	562	, C2);	EEPROM.put(	762	, Z);	Display();}
			else if 	(QRGcomp >=	51350	&&	QRGcomp <=	51379	) {EEPROM.put	(	164	, L);	EEPROM.put	(	363	, C1);	EEPROM.put(	563	, C2);	EEPROM.put(	763	, Z);	Display();}
			else if 	(QRGcomp >=	51380	&&	QRGcomp <=	51409	) {EEPROM.put	(	165	, L);	EEPROM.put	(	364	, C1);	EEPROM.put(	564	, C2);	EEPROM.put(	764	, Z);	Display();}
			else if 	(QRGcomp >=	51410	&&	QRGcomp <=	51439	) {EEPROM.put	(	166	, L);	EEPROM.put	(	365	, C1);	EEPROM.put(	565	, C2);	EEPROM.put(	765	, Z);	Display();}
			else if 	(QRGcomp >=	51440	&&	QRGcomp <=	51469	) {EEPROM.put	(	167	, L);	EEPROM.put	(	366	, C1);	EEPROM.put(	566	, C2);	EEPROM.put(	766	, Z);	Display();}
			else if 	(QRGcomp >=	51470	&&	QRGcomp <=	51499	) {EEPROM.put	(	168	, L);	EEPROM.put	(	367	, C1);	EEPROM.put(	567	, C2);	EEPROM.put(	767	, Z);	Display();}
			else if 	(QRGcomp >=	51500	&&	QRGcomp <=	51529	) {EEPROM.put	(	169	, L);	EEPROM.put	(	368	, C1);	EEPROM.put(	568	, C2);	EEPROM.put(	768	, Z);	Display();}
			else if 	(QRGcomp >=	51530	&&	QRGcomp <=	51559	) {EEPROM.put	(	170	, L);	EEPROM.put	(	369	, C1);	EEPROM.put(	569	, C2);	EEPROM.put(	769	, Z);	Display();}
			else if 	(QRGcomp >=	51560	&&	QRGcomp <=	51589	) {EEPROM.put	(	171	, L);	EEPROM.put	(	370	, C1);	EEPROM.put(	570	, C2);	EEPROM.put(	770	, Z);	Display();}
			else if 	(QRGcomp >=	51590	&&	QRGcomp <=	51619	) {EEPROM.put	(	172	, L);	EEPROM.put	(	371	, C1);	EEPROM.put(	571	, C2);	EEPROM.put(	771	, Z);	Display();}
			else if 	(QRGcomp >=	51620	&&	QRGcomp <=	51649	) {EEPROM.put	(	173	, L);	EEPROM.put	(	372	, C1);	EEPROM.put(	572	, C2);	EEPROM.put(	772	, Z);	Display();}
			else if 	(QRGcomp >=	51650	&&	QRGcomp <=	51679	) {EEPROM.put	(	174	, L);	EEPROM.put	(	373	, C1);	EEPROM.put(	573	, C2);	EEPROM.put(	773	, Z);	Display();}
			else if 	(QRGcomp >=	51680	&&	QRGcomp <=	51709	) {EEPROM.put	(	175	, L);	EEPROM.put	(	374	, C1);	EEPROM.put(	574	, C2);	EEPROM.put(	774	, Z);	Display();}
			else if 	(QRGcomp >=	51710	&&	QRGcomp <=	51739	) {EEPROM.put	(	176	, L);	EEPROM.put	(	375	, C1);	EEPROM.put(	575	, C2);	EEPROM.put(	775	, Z);	Display();}
			else if 	(QRGcomp >=	51740	&&	QRGcomp <=	51769	) {EEPROM.put	(	177	, L);	EEPROM.put	(	376	, C1);	EEPROM.put(	576	, C2);	EEPROM.put(	776	, Z);	Display();}
			else if 	(QRGcomp >=	51770	&&	QRGcomp <=	51799	) {EEPROM.put	(	178	, L);	EEPROM.put	(	377	, C1);	EEPROM.put(	577	, C2);	EEPROM.put(	777	, Z);	Display();}
			else if 	(QRGcomp >=	51800	&&	QRGcomp <=	51829	) {EEPROM.put	(	179	, L);	EEPROM.put	(	378	, C1);	EEPROM.put(	578	, C2);	EEPROM.put(	778	, Z);	Display();}
			else if 	(QRGcomp >=	51830	&&	QRGcomp <=	51859	) {EEPROM.put	(	180	, L);	EEPROM.put	(	379	, C1);	EEPROM.put(	579	, C2);	EEPROM.put(	779	, Z);	Display();}
			else if 	(QRGcomp >=	51860	&&	QRGcomp <=	51889	) {EEPROM.put	(	181	, L);	EEPROM.put	(	380	, C1);	EEPROM.put(	580	, C2);	EEPROM.put(	780	, Z);	Display();}
			else if 	(QRGcomp >=	51890	&&	QRGcomp <=	51919	) {EEPROM.put	(	182	, L);	EEPROM.put	(	381	, C1);	EEPROM.put(	581	, C2);	EEPROM.put(	781	, Z);	Display();}
			else if 	(QRGcomp >=	51920	&&	QRGcomp <=	51949	) {EEPROM.put	(	183	, L);	EEPROM.put	(	382	, C1);	EEPROM.put(	582	, C2);	EEPROM.put(	782	, Z);	Display();}
			else if 	(QRGcomp >=	51950	&&	QRGcomp <=	51979	) {EEPROM.put	(	184	, L);	EEPROM.put	(	383	, C1);	EEPROM.put(	583	, C2);	EEPROM.put(	783	, Z);	Display();}
			else if 	(QRGcomp >=	51980	&&	QRGcomp <=	52000	) {EEPROM.put	(	185	, L);	EEPROM.put	(	384	, C1);	EEPROM.put(	584	, C2);	EEPROM.put(	784	, Z);	Display();}																							
  }
}

void bt0PopCallback(void *ptr)  // 160m
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt0.getValue(&number5);  // Read value of dual state button to know the
  ct0.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;
    Band = 160;
    
    C1 = EEPROM.read(2000);
    C2 = EEPROM.read(2001);
     L = EEPROM.read(2002);
     Z = EEPROM.read(2003);


    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    if (bm == 1) {
    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial1.print("bt0.val=1"); //  160
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt1PopCallback(void *ptr)  // 80m
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt1.getValue(&number5);  // Read value of dual state button to know the
  ct1.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;
    Band = 80;
    
    C1 = EEPROM.read(2004);
    C2 = EEPROM.read(2005);
     L = EEPROM.read(2006);
     Z = EEPROM.read(2007);

    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    if (bm == 1) {
    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }

    Serial1.print("bt1.val=1"); //  80
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt2PopCallback(void *ptr)  // 60m
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt2.getValue(&number5);  // Read value of dual state button to know the
  ct2.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;
    Band = 60;
    
    C1 = EEPROM.read(2008);
    C2 = EEPROM.read(2009);
     L = EEPROM.read(2010);
     Z = EEPROM.read(2011);

    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    if (bm == 1) {
    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial1.print("bt2.val=1"); //  60
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt3PopCallback(void *ptr)  // 40m
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt3.getValue(&number5);  // Read value of dual state button to know the
  ct3.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;
    Band = 40;
    
    C1 = EEPROM.read(2012);
    C2 = EEPROM.read(2013);
     L = EEPROM.read(2014);
     Z = EEPROM.read(2015);

    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    if (bm == 1) {
    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial1.print("bt3.val=1"); //  40
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt4PopCallback(void *ptr)  // 30m
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt4.getValue(&number5);  // Read value of dual state button to know the
  ct4.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;
    Band = 30;
    
    C1 = EEPROM.read(2016);
    C2 = EEPROM.read(2017);
     L = EEPROM.read(2018);
     Z = EEPROM.read(2019);

    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    if (bm == 1) {
    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial1.print("bt4.val=1"); //  30
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt5PopCallback(void *ptr)  // 20m
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt5.getValue(&number5);  // Read value of dual state button to know the
  ct5.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;
    Band = 20;
    
    C1 = EEPROM.read(2020);
    C2 = EEPROM.read(2021);
     L = EEPROM.read(2022);
     Z = EEPROM.read(2023);

    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    if (bm == 1) {
    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial1.print("bt5.val=1"); //  20
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt6PopCallback(void *ptr)  // 17m
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt6.getValue(&number5);  // Read value of dual state button to know the
  ct6.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;
    Band = 17;
    
    C1 = EEPROM.read(2024);
    C2 = EEPROM.read(2025);
     L = EEPROM.read(2026);
     Z = EEPROM.read(2027);

    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    if (bm == 1) {
    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial1.print("bt6.val=1"); //  17
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt7PopCallback(void *ptr)  // 15m
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt7.getValue(&number5);  // Read value of dual state button to know the
  ct7.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;
    Band = 15;
    
    C1 = EEPROM.read(2028);
    C2 = EEPROM.read(2029);
     L = EEPROM.read(2030);
     Z = EEPROM.read(2031);

    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    if (bm == 1) {
    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial1.print("bt7.val=1"); //  15
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt8PopCallback(void *ptr)  // 12m
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt8.getValue(&number5);  // Read value of dual state button to know the
  ct8.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;
    Band = 12;
    
    C1 = EEPROM.read(2032);
    C2 = EEPROM.read(2033);
     L = EEPROM.read(2034);
     Z = EEPROM.read(2035);

    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    if (bm == 1) {
    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial1.print("bt8.val=1"); //  12
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt9PopCallback(void *ptr)  // 10m
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt9.getValue(&number5);  // Read value of dual state button to know the
  ct9.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;
    Band = 10;
    
    C1 = EEPROM.read(2036);
    C2 = EEPROM.read(2037);
     L = EEPROM.read(2038);
     Z = EEPROM.read(2039);

    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    if (bm == 1) {
    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial1.print("bt9.val=1"); //  10
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt10PopCallback(void *ptr)  // 6m
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt10.getValue(&number5);  // Read value of dual state button to know the
  ct10.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;
    Band = 6;
    
    C1 = EEPROM.read(2040);
    C2 = EEPROM.read(2041);
     L = EEPROM.read(2042);
     Z = EEPROM.read(2043);

    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    if (bm == 1) {
    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    }

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial1.print("bt10.val=1"); //  6
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt11PopCallback(void *ptr)  // out of band
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt11.getValue(&number5);  // Read value of dual state button to know the
  ct11.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    Manual = 1;

    C1 = 1;
    C2 = 1;
     L = 1;
    Z = 0;

    Serial3.print('L');    // code for servo
    Serial3.print(C1);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t0.txt=");
    Serial1.write(0x22);
    Serial1.print(C1);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial3.print('M');    // code for servo
    Serial3.print(C2);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print(C2);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    Serial3.print('N');    // code for servo
    Serial3.print(L);      // servo angle data
    Serial3.println('F');  // finish data packet
    Serial1.print("t1.txt=");
    Serial1.write(0x22);
    Serial1.print(L);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);
    Serial1.print("bt1.val=1"); //  80
    Serial1.write(NexT, 3);

    Serial1.print("bt11.val=1"); //  out of Band
    Serial1.write(NexT, 3);

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bt12PopCallback(void *ptr)  // Lock - Unlock
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt12.getValue(&number5);  // Read value of dual state button to know the
  ct12.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    Lock = 1;
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
  } else {  // Since the dual state button is OFF...
    Lock = 0;
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
  }
}  // End of release event

void bt13PopCallback(void *ptr)  // Auto-Manual
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt13.getValue(&number5);  // Read value of dual state button to know the
  ct13.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
  Manual = 0;
  } else {  // Since the dual state button is OFF...
  Manual = 1;
  }
}  // End of release event

void bt14PopCallback(void *ptr)  // HIGH / LOW - Z
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bt14.getValue(&number5);  // Read value of dual state button to know the
  ct14.getValue(&number5);  // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    Z = 1;
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
  } else {  // Since the dual state button is OFF...
    Z = 0;
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
  }
}  // End of release event

void bs0PopCallback(void *ptr)  // Tuner Verbindung Baud
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs0.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    EEPROM.put (900, 0);
    
    Serial1.print("bs0.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=0"); 
    Serial1.write(NexT, 3);
    delay(1000);
    
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);

    Serial1.print("page 3");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
  } else {  // Since the dual state button is OFF...
  
  }
}  // End of release event

void bs1PopCallback(void *ptr)  // Tuner Verbindung Baud
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs1.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
      EEPROM.put (900, 1);
    
    Serial1.print("bs0.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=0"); 
    Serial1.write(NexT, 3);
    delay(1000);
    
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);

    Serial1.print("page 3");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
  } else {  // Since the dual state button is OFF...

  }
}  // End of release event

void bs2PopCallback(void *ptr)  // Tuner Verbindung Baud
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs2.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    EEPROM.put (900, 2);
    
    Serial1.print("bs0.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=0"); 
    Serial1.write(NexT, 3);
    delay(1000);
    
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);

    Serial1.print("page 3");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
  } else {  // Since the dual state button is OFF...

  }
}  // End of release event

void bs3PopCallback(void *ptr)  // Tuner Verbindung Baud
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs3.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    EEPROM.put (900, 3);
    
    Serial1.print("bs0.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs1.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs2.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs3.val=1"); 
    Serial1.write(NexT, 3);
    delay(1000);
    
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);

    Serial1.print("page 3");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
  } else {  // Since the dual state button is OFF...

  }
}  // End of release event

void bs4PopCallback(void *ptr)  // CAT Verbindung Baud
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs4.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
  EEPROM.put (901, 0);
    
    Serial1.print("bs4.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=0"); 
    Serial1.write(NexT, 3);
    delay(1000);
    
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);

    Serial1.print("page 3");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
  } else {  // Since the dual state button is OFF...
  
  }
}  // End of release event

void bs5PopCallback(void *ptr)  // CAT Verbindung Baud
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs5.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
  EEPROM.put (901, 1);
    
    Serial1.print("bs4.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=0"); 
    Serial1.write(NexT, 3);
    delay(1000);
    
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);

    Serial1.print("page 3");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
  } else {  // Since the dual state button is OFF...

  }
}  // End of release event

void bs6PopCallback(void *ptr)  // CAT Verbindung Baud
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs6.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
  EEPROM.put (901, 2);
    
    Serial1.print("bs4.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=0"); 
    Serial1.write(NexT, 3);
    delay(1000);
    
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);

    Serial1.print("page 3");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
  } else {  // Since the dual state button is OFF...

  }
}  // End of release event

void bs7PopCallback(void *ptr)  // CAT Verbindung Baud
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs7.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
  EEPROM.put (901, 3);
    
    Serial1.print("bs4.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs5.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs6.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs7.val=1"); 
    Serial1.write(NexT, 3);
    delay(1000);
    
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);

    Serial1.print("page 3");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
  } else {  // Since the dual state button is OFF...

  }
}  // End of release event

void bs8PopCallback(void *ptr)  // Tuner Model Stepper
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs8.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...

    EEPROM.put (904, 0);
    
    Serial1.print("bs8.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs9.val=0"); 
    Serial1.write(NexT, 3);
    delay(1000);

    if (Setup == 0) {

    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
    }
  } else {  // Since the dual state button is OFF...
  
  }
}  // End of release event

void bs9PopCallback(void *ptr)  // Tuner Model Relais
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs9.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...

    EEPROM.put (904, 1);

    Serial1.print("bs8.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs9.val=1"); 
    Serial1.write(NexT, 3);
    delay(1000);

    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
  } else {  // Since the dual state button is OFF...

  }
}  // End of release event

void bs10PopCallback(void *ptr)  // Tuner Model 2 Bauteile
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs10.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...

    Serial1.print("bs10.val=1"); //2Bauteile
    Serial1.write(NexT, 3);
    Serial1.print("bs11.val=0"); //3Bauteile
    Serial1.write(NexT, 3);
  
    EEPROM.put(908, 0);
    
    delay(500);

    if (Setup == 0) {

    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
    }

  } else {  // Since the dual state button is OFF...

  }
}  // End of release event

void bs11PopCallback(void *ptr)  // Tuner Model 3 Bauteile
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs11.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    
    
    Serial1.print("bs10.val=0"); //2Bauteile
    Serial1.write(NexT, 3);
    Serial1.print("bs11.val=1"); //3Bauteile
    Serial1.write(NexT, 3);
  
    EEPROM.put(908, 1);
    
    delay(500);

    if (Setup == 0) {

    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
    }

  } else {  // Since the dual state button is OFF...
  }
}  // End of release event

void bs12PopCallback(void *ptr)  // Funktionstest  Aktiviert
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs12.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    EEPROM.put	(906, 1);

    Serial1.print("bs12.val=1"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs13.val=0"); 
    Serial1.write(NexT, 3);
    delay(1000);
    
    if (Setup == 0) {

    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
    }
  } else {  // Since the dual state button is OFF...

  }
}  // End of release event

void bs13PopCallback(void *ptr)  // Funktionstest  Deaktiviert
{
  uint32_t number5 = 0;    // Create variable to store value we are going to get
  bs13.getValue(&number5);  // Read value of dual state button to know the
                           // state (0 or 1)

  if (number5 == 1) {  // If dual state button is equal to 1 (meaning is ON)...
    EEPROM.put	(906, 0);
    
    Serial1.print("bs12.val=0"); 
    Serial1.write(NexT, 3);
    Serial1.print("bs13.val=1"); 
    Serial1.write(NexT, 3);
    delay(1000);
  
    if (Setup == 0) {

    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
    }
  } else {  // Since the dual state button is OFF...

  }
}  // End of release event+

void q0PopCallback(void *ptr)   // back Tuner
{
    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();				
}
void q1PopCallback(void *ptr)   // Abgleich Tuner
{
  Serial1.print("page 4");
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print("t0.txt=");
  Serial1.write(0x22);
  Serial1.print(Call);
  Serial1.print("   Tuner   Setup");
  Serial1.write(0x22);
  Serial1.write(NexT, 3);

  Serial1.print("t2.txt=");
  Serial1.write(0x22);
  Serial1.print("Firmware ");
  Serial1.print(Firmware_v);
  Serial1.write(0x22);
  Serial1.write(NexT, 3);

  delay(150);
}

void n0PopCallback(void *ptr)   // C1  -0-  Abgleich
{
    Serial3.print('P');    // code for servo
    Serial3.print(1);      // servo angle data
    Serial3.println('F');  // finish data packet

    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
}

void n1PopCallback(void *ptr)   // C2  -0-  Abgleich
{
    Serial3.print('Q');    // code for servo
    Serial3.print(1);      // servo angle data
    Serial3.println('F');  // finish data packet

    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
}

void n2PopCallback(void *ptr)   //  L  -0-  Abgleich
{
    Serial3.print('R');    // code for servo
    Serial3.print(1);      // servo angle data
    Serial3.println('F');  // finish data packet

    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
}
void n3PopCallback(void *ptr)   // Band Eeprom leeren
{
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, HIGH);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
    delay(25);
    digitalWrite(A12, LOW);
  
     EEPROM.put(2000,1);
     EEPROM.put(2001,1);
     EEPROM.put(2002,1);
     EEPROM.put(2003,1);
     EEPROM.put(2004,1);
     EEPROM.put(2005,1);
     EEPROM.put(2006,1);
     EEPROM.put(2007,1);
     EEPROM.put(2008,1);
     EEPROM.put(2009,1);
     EEPROM.put(2010,1);
     EEPROM.put(2011,1);
     EEPROM.put(2012,1);
     EEPROM.put(2013,1);
     EEPROM.put(2014,1);
     EEPROM.put(2015,1);
     EEPROM.put(2016,1);
     EEPROM.put(2017,1);
     EEPROM.put(2018,1);
     EEPROM.put(2019,1);
     EEPROM.put(2020,1);
     EEPROM.put(2021,1);
     EEPROM.put(2022,1);
     EEPROM.put(2023,1);
     EEPROM.put(2024,1);
     EEPROM.put(2025,1);
     EEPROM.put(2026,1);
     EEPROM.put(2027,1);
     EEPROM.put(2028,1);
     EEPROM.put(2029,1);
     EEPROM.put(2030,1);
     EEPROM.put(2031,1);
     EEPROM.put(2032,1);
     EEPROM.put(2033,1);
     EEPROM.put(2034,1);
     EEPROM.put(2035,1);
     EEPROM.put(2036,1);
     EEPROM.put(2037,1);
     EEPROM.put(2038,1);
     EEPROM.put(2039,1);
     EEPROM.put(2040,1);
     EEPROM.put(2041,1);
     EEPROM.put(2042,1);
     EEPROM.put(2043,1);
    
    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
    
}
void n4PopCallback(void *ptr)   // Freq Eeprom leeren
{
    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();

}
void n5PopCallback(void *ptr)   // Tuner Reset
{
    Serial1.print("page 5");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
    
    Serial1.print("t2.txt=");
    Serial1.write(0x22);
    Serial1.print("Firmware ");
    Serial1.print(Firmware_v);
    Serial1.write(0x22);
    Serial1.write(NexT, 3);

    EEPROM.put(900, 99);
    EEPROM.put(902, 99);
    EEPROM.put(904, 99);
    EEPROM.put(906, 99);
    EEPROM.put(908, 99);

    digitalWrite(5, HIGH);     //  Reset OUT
    delay(2500);
    digitalWrite(5, LOW);      //  Reset OUT

    setup();
}
void loop() {
RS485();
}
