#include <yunOSC.h>
#include <Process.h>

/* 
 * NANO HIPERBOT
 * 
 * ANALOG PINS
 * 
 * 0 GSR / PLANTRONIC
 * 1 SOLO / HUMIDADE
 * 2 TEMPERATURA
 * 3 LDR / LUZ
 * 
 * DIGITAL PINS
 * 
 * 0 TX
 * 1 RX
 * 2 BARGRAPH CLOCK
 * 3 BARGRAPH RESET
 * 8 AUDIO OUT
 * 9 R 
 * 10 G
 * 11 B
 * 
 */
 
//#define IP_ADR "192.168.240.143"
#define IP_ADR "146.164.80.56"
#define PORT 22244

int C = 262, D = 294, E = 330, F = 349, G = 392, A = 440, B = 523, P = 0;

int ode[]   = {
  G,B,D,C,E,G,A,F,E,
  C,D,E,F,G,A,B,D,C,C,D,E,D,C,C,
};
int tempo[] = {
  1,1,1,1,1,1,1,1,1,1,1,1,1.5,1,.5,1,1,
  1,1,1,1,1,1,1,1,2,1,1,1,1.5,1,.5,1,1,
};

int pin_planta = A0;
int pin_solo   = A1;
int pin_temp   = A2;
int pin_luz    = A3;

int pin_bgraphclock = 2;
int pin_bgraphreset = 3;
int pin_cor_r       = 9;
int pin_cor_g       = 10;
int pin_cor_b       = 11;

int val_planta_raw=0;
int val_planta = 0;
int val_solo = 0;
int val_temp = 0;
int val_luz = 0;

void setup() {  
  pinMode(pin_bgraphclock, OUTPUT);
  pinMode(pin_bgraphreset, OUTPUT);
  pinMode(pin_cor_r, OUTPUT);
  pinMode(pin_cor_g, OUTPUT);
  pinMode(pin_cor_b, OUTPUT);
  
  // 2 YunOSC essential lines:
  Bridge.begin();
  osc.begin(IP_ADR, PORT);
}

void loop(){
  val_planta_raw = analogRead(A0);
  val_planta = map(analogRead(pin_planta), 350, 600, 0, 1023);
  val_solo = analogRead(pin_solo);
  val_temp = analogRead(pin_temp);
  val_luz = analogRead(pin_luz);

  // BARGRAPH
  int n = val_planta * 10 / 1023;
  for (int i = 0; i < n; i++){
    bgraph_clock();
  }
  bgraph_reset();
  
  sendOsc("/hiperbot/solo", val_solo);
  sendOsc("/hiperbot/gsr", val_planta);
  sendOsc("/hiperbot/temp", val_temp);
  sendOsc("/hiperbot/lumin", val_luz);
  
  RGBroutine();
  delay(100);
}

void sendOsc(String addr, int val) {
  int values[1];
  values[0] = val;
  osc.send(addr, values, 1);
}

void bgraph_clock(){
  digitalWrite(pin_bgraphclock, HIGH);
  delay(1);
  digitalWrite(pin_bgraphclock, LOW);
}

void bgraph_reset(){
  digitalWrite(pin_bgraphreset, HIGH);
  delay(1);
  digitalWrite(pin_bgraphreset, LOW);
}

void RGBroutine()
{
  int potVal = val_planta;
  int redVal = 0;
  int grnVal = 0;
  int bluVal = 0;

  if (potVal < 341)
  {
    potVal = (potVal * 3) / 4;
    redVal = 256 - potVal;
    grnVal = potVal;
    bluVal = 1;
  }
  else if (potVal < 682)
  {
    potVal = ((potVal - 341) * 3) / 4;
    redVal = 1;
    grnVal = 256 - potVal;
    bluVal = potVal;
  }
  else
  {
    potVal = ((potVal - 683) * 3) / 4;
    redVal = potVal;
    grnVal = 1;
    bluVal = 256 - potVal;
  }
  analogWrite(pin_cor_r, redVal);
  analogWrite(pin_cor_g, grnVal);
  analogWrite(pin_cor_b, bluVal);

}
