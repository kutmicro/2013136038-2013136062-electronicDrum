
#include <Wire.h>
#include "Adafruit_MPR121.h"


Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;


#define CRASH_CYMBAL    (49)
#define RIDE_CYMBAL     (51)
#define HIGH_HAT        (44)
#define LOW_FLOOR_TOM   (41)
#define HIGH_FLOOR_TOM  (43)
#define LOW_MID_TOM     (47)
#define HIGH_MID_TOM    (48)
#define LOW_TOM         (45)
#define HIGH_TOM        (50)
#define ACOUSTIC_SNARE  (38)
#define ELECTRIC_SNARE  (40)
#define BASS_DRUM       (35)

void PercussionMessage(byte type, byte velocity) {
  Serial.write(0x90 | 9);
    switch(type){
      case 0: Serial.write(CRASH_CYMBAL);Serial.println("0touched"); break;
      case 1: Serial.write(RIDE_CYMBAL);Serial.println("1touched"); break;
      case 2: Serial.write(HIGH_HAT);Serial.println("2touched"); break;
      case 3: Serial.write(LOW_FLOOR_TOM);Serial.println("3touched"); break;
      case 4: Serial.write(HIGH_FLOOR_TOM);Serial.println("4touched"); break;
      case 5: Serial.write(LOW_MID_TOM); Serial.println("5touched");break;
      case 6: Serial.write(HIGH_MID_TOM); Serial.println("6touched");break;
      case 7: Serial.write(LOW_TOM); Serial.println("7touched");break;
      case 8: Serial.write(HIGH_TOM); Serial.println("8touched");break;
      case 9: Serial.write(ACOUSTIC_SNARE); Serial.println("9touched");break;
      case 10: Serial.write(ELECTRIC_SNARE); Serial.println("10touched");break;
      case 11: Serial.write(BASS_DRUM); Serial.println("11touched");break;
  }
  Serial.write(velocity);
}



  /*---------------------------------------------------------
      S  E  T  U  P
  ---------------------------------------------------------*/
void setup() {
  Serial.begin(19200);
  Serial.println("dd");
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
}


  /*---------------------------------------------------------
      L  O  O  P
  ---------------------------------------------------------*/
void loop() {
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
     PercussionMessage(i, 127);
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
     // PercussionMessage(i, 0);
    }
  }
  lasttouched = currtouched;
  return;
}
