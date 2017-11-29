
//Continually prints spaces until the end of the line, then prints backspace till the beginning, etc

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

    
}



void loop() {
  for(int i = 1; i<65; i++){
    digitalWrite(30, HIGH);
    digitalWrite(2, HIGH);  
    delay(100);
                      
    digitalWrite(30, LOW);
    digitalWrite(2, LOW);  
    delay(1000);
  }

  for(int i = 1; i<65; i++){
    digitalWrite(30, HIGH);
    digitalWrite(7, HIGH);  
    delay(100);
                      
    digitalWrite(30, LOW);
    digitalWrite(7, LOW);  
    delay(1000);
  }

}
