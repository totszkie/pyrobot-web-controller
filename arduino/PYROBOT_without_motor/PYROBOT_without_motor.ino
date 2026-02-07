// Pin Definitions
//const int ledLeft  = 3; 
//const int ledRight = 4; 
//const int ledUp    = 5; 
//const int ledDown  = 6; 
const int ledLight = 5; 
const int horn = 10; 

void setup() {
  Serial.begin(9600);
  pinMode(ledLight, OUTPUT);
  pinMode(horn,     OUTPUT);
  
  // Flash once to confirm code is running
  digitalWrite(ledLight, HIGH); delay(200); digitalWrite(ledLight, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();


    // --- Horn (Momentary) ---
    if (cmd == 'H') digitalWrite(horn, HIGH);
    if (cmd == 'h') digitalWrite(horn, LOW);

    // --- Light (Toggle via System) ---
    if (cmd == 'N') digitalWrite(ledLight, HIGH);
    if (cmd == 'F') digitalWrite(ledLight, LOW);
  }
}