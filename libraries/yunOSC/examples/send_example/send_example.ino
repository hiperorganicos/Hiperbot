//
//  yunOSC lib example for sending OSC formatted messages 
//  on local UDP using pyOSC python library on lininio
//
//  dependencies: 
//  * pyOSC lib installed on linino
//  * oscsend.py python script located in root@arduino.local/tmp
//  * pd-extended msg_to_freq_example.pd patch
//  
//  README/GUIDE: https://github.com/bobbyziom/OSC-yun-harmony/blob/master/README.md
//
//  - bobbyziom  
//

// include process bridge lib and yunOSC lib
#include <Process.h>
#include <yunOSC.h>

// make ip and port constants
#define IP_ADR "192.168.240.143"
#define PORT 22233

void setup() {
  
  // nevah forget the bridge
  Bridge.begin();
  
  // make udp connection
  osc.begin(IP_ADR, PORT);

}

void loop() {
  
  // make int array of values
  // just reading current oscillation for test
  int values[3] = {analogRead(A0), analogRead(A1), analogRead(A2)};
  
  // send osc message with 
  // argument1: route tag
  // argument2: int array of values
  // argument3: size of array
  osc.send("/yun", values, 3);

}


