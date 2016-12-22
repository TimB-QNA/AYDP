bool state=false;

void setup() {
  // put your setup code here, to run once:
  pinMode(A4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(A4,state);
  state=!state;
  delay(5);
}
