const int pinA = 2;
const int pinB = 3;
const int gazPin = 4;
const int frenPin = 5;

volatile int encoderPos = 0;
int lastEncoded = 0;

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  pinMode(gazPin, INPUT_PULLUP);
  pinMode(frenPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), updateEncoder, CHANGE);
}

void loop() {
  int gaz = digitalRead(gazPin) == LOW ? 1023 : 0;    // Butona basınca gaz ver
  int fren = digitalRead(frenPin) == LOW ? 1023 : 0;  // Butona basınca fren yap

  Serial.print(encoderPos);
  Serial.print(',');
  Serial.print(gaz);
  Serial.print(',');
  Serial.println(fren);
  delay(10);
}

void updateEncoder() {
  int MSB = digitalRead(pinA);
  int LSB = digitalRead(pinB);

  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderPos++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderPos--;

  encoderPos = constrain(encoderPos, -100, 100);
  lastEncoded = encoded;
}
