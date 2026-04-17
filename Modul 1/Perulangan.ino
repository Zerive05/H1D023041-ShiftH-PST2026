int timer = 100;           
// delay. Semakin tinggi angkanya, semakin lambat waktunya. 
void setup() { 
  output: 
  for (int ledPin = 2; ledPin < 5; ledPin++) { 
  pinMode(ledPin, OUTPUT); 
  } 
} 

void loop() { 
    for (int ledPin = 2; ledPin < 5; ledPin++) { 
    digitalWrite(ledPin, HIGH); 
    delay(timer); 
    digitalWrite(ledPin, LOW);
    
    for (int ledPin = 7; ledPin >= 2; ledPin--) { 
    digitalWrite(ledPin, HIGH); 
    delay(timer); 
    digitalWrite(ledPin, LOW); 
    } 
  } 
}