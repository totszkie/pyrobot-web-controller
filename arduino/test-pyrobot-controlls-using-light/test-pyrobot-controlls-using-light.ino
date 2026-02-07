// Pin Definitions
const int ledLeft  = 3; 
const int ledRight = 4; 
const int ledUp    = 5; 
const int ledDown  = 6; 
const int ledLight = 7; 
const int horn = 8; 

void setup() {
  Serial.begin(9600);
  pinMode(ledLeft,  OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledUp,    OUTPUT);
  pinMode(ledDown,  OUTPUT);
  pinMode(ledLight, OUTPUT);
  pinMode(horn,     OUTPUT);
  
  // Flash once to confirm code is running
  digitalWrite(ledLight, HIGH); delay(200); digitalWrite(ledLight, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();

    // --- Standard Movement ---
    if (cmd == 'U') digitalWrite(ledUp,    HIGH);
    if (cmd == 'u') digitalWrite(ledUp,    LOW);
    
    if (cmd == 'D') digitalWrite(ledDown,  HIGH);
    if (cmd == 'd') digitalWrite(ledDown,  LOW);
    
    if (cmd == 'L') digitalWrite(ledLeft,  HIGH);
    if (cmd == 'l') digitalWrite(ledLeft,  LOW);
    
    if (cmd == 'R') digitalWrite(ledRight, HIGH);
    if (cmd == 'r') digitalWrite(ledRight, LOW);

    // --- Diagonal Movement (Combination of Pins) ---
    // Top-Left (Q/q)
    if (cmd == 'Q') { digitalWrite(ledUp, HIGH); digitalWrite(ledLeft, HIGH); }
    if (cmd == 'q') { digitalWrite(ledUp, LOW);  digitalWrite(ledLeft, LOW); }

    // Top-Right (E/e)
    if (cmd == 'E') { digitalWrite(ledUp, HIGH); digitalWrite(ledRight, HIGH); }
    if (cmd == 'e') { digitalWrite(ledUp, LOW);  digitalWrite(ledRight, LOW); }

    // Bottom-Left (Z/z)
    if (cmd == 'Z') { digitalWrite(ledDown, HIGH); digitalWrite(ledLeft, HIGH); }
    if (cmd == 'z') { digitalWrite(ledDown, LOW);  digitalWrite(ledLeft, LOW); }

    // Bottom-Right (C/c)
    if (cmd == 'C') { digitalWrite(ledDown, HIGH); digitalWrite(ledRight, HIGH); }
    if (cmd == 'c') { digitalWrite(ledDown, LOW);  digitalWrite(ledRight, LOW); }

    // --- Horn (Momentary) ---
    if (cmd == 'H') digitalWrite(horn, HIGH);
    if (cmd == 'h') digitalWrite(horn, LOW);

    // --- Light (Toggle via System) ---
    if (cmd == 'N') digitalWrite(ledLight, HIGH);
    if (cmd == 'F') digitalWrite(ledLight, LOW);
  }
}