// Legacy come back here if something breaks for the capacitive sensor readings
#include <CapacitiveSensor.h>

CapacitiveSensor   cs_9_10 = CapacitiveSensor(9,10);

int melody[] = {
  262, 196, 196, 220, 196, 0, 247, 262
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
void setup()                    
{
   cs_9_10.set_CS_AutocaL_Millis(0xFFFFFFFF);
   pinMode(7, OUTPUT);
   pinMode(6, OUTPUT);
   pinMode(5, OUTPUT);
   pinMode(4, OUTPUT);
   Serial.begin(9600);

}

void loop()                    
{
  long start = millis();
  long total1 =  cs_9_10.capacitiveSensor(30);

  if (total1 > 4000){
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  if (total1 > 16000){
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
  }
  if (total1 > 24000){
    digitalWrite(5, HIGH);
  } else {
    digitalWrite(5, LOW);
  }
  if (total1 > 30000){
    digitalWrite(4, HIGH);
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(8, melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(8);
    }
  } else {
    digitalWrite(4, LOW);
  }

  Serial.print(millis() - start);        
  Serial.print("\t");                   
  Serial.println(total1);                 
  delay(10);                         
}
