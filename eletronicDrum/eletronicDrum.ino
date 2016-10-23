///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////마이크로 프로세서 및 실습 ///////////////////////////////
/////////2013136038 박성준//2013136062 신찬욱//////////////////////////////////////////////////////
///////////////////////////////////////////////Electronic Drum/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include "Adafruit_MPR121.h"


Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;


#define CRASH_CYMBAL    (49)//
#define RIDE_CYMBAL     (51)//
#define HIGH_HAT        (44)//
#define LOW_FLOOR_TOM   (41)
#define HIGH_FLOOR_TOM  (43)
#define LOW_MID_TOM     (47)
#define HIGH_MID_TOM    (48)
#define LOW_TOM         (45)
#define HIGH_TOM        (50)
#define ACOUSTIC_SNARE  (38)
#define ELECTRIC_SNARE  (40)
#define BASS_DRUM       (35)//

/*---------------------------------------------------------
    S  E  T  U  P
  ---------------------------------------------------------*/
void setup() {
  Serial.begin(19200);

  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
}
void PercussionMessage(byte type, byte velocity) {
  Serial.write(0x90 | 9);
  switch (type) {
    case 0: Serial.write(CRASH_CYMBAL); break;
    case 1: Serial.write(RIDE_CYMBAL); break;
    case 2: Serial.write(HIGH_HAT); break;
    case 3: Serial.write(LOW_FLOOR_TOM); break;
    case 4: Serial.write(HIGH_FLOOR_TOM); break;
    case 5: Serial.write(LOW_MID_TOM); break;
    case 6: Serial.write(HIGH_MID_TOM); break;
    case 7: Serial.write(LOW_TOM); break;
    case 8: Serial.write(HIGH_TOM); break;
    case 9: Serial.write(ACOUSTIC_SNARE); break;
    case 10: Serial.write(ELECTRIC_SNARE); break;
    case 11: Serial.write(BASS_DRUM); break;
  }
  Serial.write(velocity);
}
/*---------------------------------------------------------
    L  O  O  P
  ---------------------------------------------------------*/
void loop() {
  currtouched = cap.touched();

  for (uint8_t i = 0; i < 12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      PercussionMessage(i, 127);
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      PercussionMessage(i, 0);
    }
  }
  lasttouched = currtouched;
  return;
}



