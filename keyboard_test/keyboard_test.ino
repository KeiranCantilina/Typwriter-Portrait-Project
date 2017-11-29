void setup() {
  
  for(int i = 2; i<10; i++){
    pinMode(i, OUTPUT); 
  }
  for(int i = 24; i<32; i++){
    pinMode(i, OUTPUT); 
  }

  for(int i = 2; i<10; i++){
    digitalWrite(i, LOW); 
  }
  for(int i = 24; i<32; i++){
    digitalWrite(i, LOW); 
  }
  
  delay(1000);

  for(int j = 24; j<30; j++){
    for(int k = 2; k<10; k++){
      digitalWrite(j, HIGH);
      digitalWrite(k, HIGH);
      delay(100);
      digitalWrite(j, LOW);
      digitalWrite(k, LOW);
      delay(150);
    }
  }

  delay(1000);
  digitalWrite(31, HIGH);
  digitalWrite(3, HIGH);
  delay(100);
  digitalWrite(31, LOW);
  digitalWrite(3, LOW);

  
  delay(1000);
  digitalWrite(30, HIGH);
  digitalWrite(3, HIGH);
  delay(100);
  digitalWrite(30, LOW);
  digitalWrite(3, LOW);
  delay(2000);

  for(int j = 24; j<30; j++){
    for(int k = 2; k<10; k++){
      digitalWrite(j, HIGH);
      digitalWrite(k, HIGH);
      delay(100);
      digitalWrite(j, LOW);
      digitalWrite(k, LOW);
      delay(150);
    }
  }
  delay(1000);
}



// the loop function runs over and over again forever
void loop() {
  
  
}
