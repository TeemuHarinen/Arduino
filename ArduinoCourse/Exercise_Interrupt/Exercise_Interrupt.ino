#define LED_PIN 12
#define BUTTON_PIN 2

volatile unsigned long lastTimeButtonReleased = millis();
unsigned long debounceDelay = 50; // volatile not needed since not modifying the value

byte LEDState = LOW;
volatile bool buttonReleased = false;

void toggleLED()
{
  if(LEDState == LOW)
  {
    LEDState = HIGH;
  }
  else
  {
    LEDState = LOW;
  }
  digitalWrite(LED_PIN, LEDState);
}

void buttonReleasedInterrupt()
{
  unsigned long timeNow = millis();
  if (timeNow - lastTimeButtonReleased > debounceDelay)
  {
    lastTimeButtonReleased = timeNow;
    buttonReleased = true;
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonReleasedInterrupt, FALLING);
}

void loop () {
  if (buttonReleased)
  {
    buttonReleased = false;
    toggleLED();
  }
}