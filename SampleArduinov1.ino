#include <Adafruit_NeoPixel.h>

*/int buttonpins [] = {2,3,4,6,7};
*/
int ledpins [] = {2,3,4,5,6,7};
int buzzer = 8;
int gamelevel = 1;
int ledsequence[20];
int buttonsequence[20];
int delayvalue = 1000;


void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  noTone(buzzer);

}

void loop() {
  Serial.print("Starting Level: ");
  Serial.println(gamelevel);
  startgame();
  for (int i=0; i < 6; i++) {
    ledsequence[i] = randomiseLED();
    Serial.print("LED Value: ");
    Serial.println(ledsequence[i]);
  }
  checkinput();
  if (delayvalue > 100) {
    delayvalue -= 100;
  }
  gamelevel++;
  delay(1000);
}

int randomiseLED() {
  randomSeed(millis());
  int LED = random(5);
  if (LED ==0) {
    digitalWrite(ledpins[0], 1);
    delay(delayvalue);
    digitalWrite(ledpins[0], 0);
    delay(delayvalue);
    return 0;
  } else if (LED == 1){
    digitalWrite(ledpins[1], 0);
    delay(delayvalue);
    return 1;
  } else {
    digitalWrite(ledpins[2], 1);
    delay(delayvalue);
    digitalWrite(ledpins[2], 0);
    delay(delayvalue);
    return 2; }
}

void checkinput() {
  for (int x = 0; x < gamelevel;) {
    if (digitalRead(buttonpins[0]) == 1) {
      buttonsequence[x] = 0;
      digitalWrite(ledpins[0], 1);
      delay(200);
      digitalWrite(ledpins[0], 0);
      delay(200);
      if (buttonsequence[x] != ledsequence[x]) {
        fail(); }
        x++; }
        if (digitalRead(buttonpins[1]) ==1) {
          buttonsequence[x] = 1;
          digitalWrite(ledpins[1], 1);
          delay(200);
          digitalWrite(ledpins[1], 0);
          delay(200);
          if (buttonsequence[x] != ledsequence[x]) {
            fail(); }
            x++; }
            if (digitalRead(buttonpins[2]) == 1) {
              buttonsequence[x] = 2;
              digitalWrite(ledpins[2], 1);
              delay(200);
              digitalWrite(ledpins[2], 0);
              delay(200);
              if (buttonsequence[x] != ledsequence[x]) {
                fail(); }
                x++; }
  }}

  void fail() {

    Serial.println("Game Over");
    digitalWrite(ledpins[0], 1);
    digitalWrite(ledpins[1], 1);
    digitalWrite(ledpins[2], 1);
    delay(200);
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
    gamelevel = 0;
  }

void startgame() {
  Serial.println("Starting LEDS");
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledpins[0], HIGH);
    digitalWrite(ledpins[1], LOW);
    digitalWrite(ledpins[2], LOW);
 /*   delay(100);
    digitalWrite(ledpins[0], LOW);
    digitalWrite(ledpins[1], HIGH);
    digitalWrite(ledpins[2], LOW);
    delay(100);
    digitalWrite(ledpins[0], LOW);
    digitalWrite(ledpins[1], LOW);
    digitalWrite(ledpins[2], HIGH);
    delay(100);
    digitalWrite(ledpins[0], HIGH);
    digitalWrite(ledpins[1], HIGH);
    digitalWrite(ledpins[2], HIGH);
    delay(100);
    digitalWrite(ledpins[0], LOW);
    digitalWrite(ledpins[1], LOW);
    digitalWrite(ledpins[2], LOW);
    delay(100);
    */
  }
  delay(1000);
}
