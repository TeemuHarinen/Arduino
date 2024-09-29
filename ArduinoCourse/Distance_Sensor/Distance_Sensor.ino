#define ECHO_PIN 3
#define TRIGGER_PIN 4

unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 100;

void triggerUltrasonicSensor()
{
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
}

double getUltrasonicDistance()
{
  double durationMicros = pulseIn(ECHO_PIN, HIGH);
  double distance = durationMicros / 58.0; //  -> cm
  return distance;
}


void setup() {
  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
}

void loop() {
  unsigned long timeNow = millis();

  if (timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay)
  {
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    triggerUltrasonicSensor();
    Serial.println(getUltrasonicDistance());
  }
}
