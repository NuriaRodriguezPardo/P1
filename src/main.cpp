#include <Arduino.h>

// put function declarations here:
//int myFunction(int, int);

// put function definitions here:
//int myFunction(int x, int y) {
//  return x + y;
//}

#define LED_BUILTIN 23
#define DELAY 500

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("ON");
  // delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("OFF");
  // delay(500);
}
