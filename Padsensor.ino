#include <Adafruit_NAU7802.h>
//CapacitiveSensor
#include <CapacitiveSensor.h>

CapacitiveSensor   cs_9_10 = CapacitiveSensor(9,10);

int melody[] = {
  262, 196, 196, 220, 196, 0, 247, 262
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
//---------------

Adafruit_NAU7802 nau;

void setup() {
  Serial.begin(115200);
  Serial.println("NAU7802");
  if (! nau.begin()) {
    Serial.println("Failed to find NAU7802");
  }
  Serial.println("Found NAU7802");

  nau.setLDO(NAU7802_3V0);
  Serial.print("LDO voltage set to ");
  switch (nau.getLDO()) {
    case NAU7802_4V5:  Serial.println("4.5V"); break;
    case NAU7802_4V2:  Serial.println("4.2V"); break;
    case NAU7802_3V9:  Serial.println("3.9V"); break;
    case NAU7802_3V6:  Serial.println("3.6V"); break;
    case NAU7802_3V3:  Serial.println("3.3V"); break;
    case NAU7802_3V0:  Serial.println("3.0V"); break;
    case NAU7802_2V7:  Serial.println("2.7V"); break;
    case NAU7802_2V4:  Serial.println("2.4V"); break;
    case NAU7802_EXTERNAL:  Serial.println("External"); break;
  }

  nau.setGain(NAU7802_GAIN_128);
  Serial.print("Gain set to ");
  switch (nau.getGain()) {
    case NAU7802_GAIN_1:  Serial.println("1x"); break;
    case NAU7802_GAIN_2:  Serial.println("2x"); break;
    case NAU7802_GAIN_4:  Serial.println("4x"); break;
    case NAU7802_GAIN_8:  Serial.println("8x"); break;
    case NAU7802_GAIN_16:  Serial.println("16x"); break;
    case NAU7802_GAIN_32:  Serial.println("32x"); break;
    case NAU7802_GAIN_64:  Serial.println("64x"); break;
    case NAU7802_GAIN_128:  Serial.println("128x"); break;
  }

  nau.setRate(NAU7802_RATE_10SPS);
  Serial.print("Conversion rate set to ");
  switch (nau.getRate()) {
    case NAU7802_RATE_10SPS:  Serial.println("10 SPS"); break;
    case NAU7802_RATE_20SPS:  Serial.println("20 SPS"); break;
    case NAU7802_RATE_40SPS:  Serial.println("40 SPS"); break;
    case NAU7802_RATE_80SPS:  Serial.println("80 SPS"); break;
    case NAU7802_RATE_320SPS:  Serial.println("320 SPS"); break;
  }

  // Take 10 readings to flush out readings
  for (uint8_t i=0; i<10; i++) {
    while (! nau.available()) delay(1);
    nau.read();
  }

  while (! nau.calibrate(NAU7802_CALMOD_INTERNAL)) {
    Serial.println("Failed to calibrate internal offset, retrying!");
    delay(1000);
  }
  Serial.println("Calibrated internal offset");

  while (! nau.calibrate(NAU7802_CALMOD_OFFSET)) {
    Serial.println("Failed to calibrate system offset, retrying!");
    delay(1000);
  }
  Serial.println("Calibrated system offset");


  //CapacitiveSensor
  cs_9_10.set_CS_AutocaL_Millis(0xFFFFFFFF);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  //Serial.begin(9600);
  //----------------

}

void loop() {
  while (! nau.available()) {
    delay(1);
  }
  int32_t val = nau.read();
  Serial.print("Read "); Serial.print(val * -0.00004807692308); Serial.println(" KG");

  //CapacitiveSensor
  long start = millis();
  long total1 =  cs_9_10.capacitiveSensor(30);

  if (total1 > 35000){
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  if (total1 > 67500){
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
  }
  if (total1 > 125000){
    digitalWrite(5, HIGH);
  } else {
    digitalWrite(5, LOW);
  }
  if (total1 > 250000){
    digitalWrite(4, HIGH); /*
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(8, melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(8); 
    }*/
  } else {
    digitalWrite(4, LOW);
  }

  Serial.print(millis() - start);        
  Serial.print("\t");                   
  Serial.println(total1);                 
  delay(10); 
 //----------------

}