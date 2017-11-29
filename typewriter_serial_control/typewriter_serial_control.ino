// Typewriter serial control script (Brother SX-4000)
// by Keiran Cantilina (2017)

// Inspired by work done by Scott Perry (2009) documented on his site <http://numist.net/post/2010/project-typewriter.html>, this 
// particular implementation uses different (hopefully simpler) approaches in both hardware and software.
// This code is meant to be run on some sort of AVR/arduino thingy interfaced to the keyboard matrix pins of the typewriter.

// An attempt was made to make this project an excercize in exceptionally human-readable code

// Variable declaration
int incomingByte = 0;
char incomingLetter = '\0';
char search = '\0';
bool is_found = false;
bool is_uppercase = false;
int index = 9;
int probe_pin = 24;
int sense_pin = 2;

// Milliseconds between typed characters to allow time for daisy wheel to turn
int character_delay = 150;

// Character array, omitting non-ascii characters and stuff the typewriter can't do (like "\" apparently) plus space for null character at the end
char lowercase_array[48] = {' ', ',', '/', '1', '3', '7', '5', '-', '9', '.', '2', '4', '8', '6', '=', '0', 'q', 'e', 't', 'o', 'u', 'n', 'v', ';', 'z', 'f', 'h', 's', 'k', 'x', 'c', ']', 'w', 'r', 'y', 'p', 'i', 'm', 'b', 'a', 'g', 'j', 'd', 'l', '\t', '\n', '\''};
char uppercase_array[42] = {'?', '!', '#', '&', '%', '_', '(', '@', '$', '*', '+', ')', 'Q', 'E', 'T', 'O', 'U', 'N', 'V', ':', 'Z', 'F', 'H', 'S', 'K', 'X', 'C', '[', 'W', 'R', 'Y', 'P', 'I', 'M', 'B', '"', 'A', 'G', 'J', 'D', 'L'};

// Probe pin array
int probe_array_lowercase[] = {30, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 30, 29};
int probe_array_uppercase[] = {24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29};

// Sense pin array
int sense_array_lowercase[] = {2, 2, 3, 4, 5, 6, 7, 8, 9, 2, 4, 5, 6, 7, 8, 9, 3, 4, 5, 6, 7, 8, 9, 2, 3, 4, 5, 6, 7, 8, 9, 2, 3, 4, 5, 6, 7, 8, 9, 3, 4, 5, 6, 7, 9, 3, 2};
int sense_array_uppercase[] = {3, 4, 5, 6, 7, 8, 9, 4, 5, 6, 8, 9, 3, 4, 5, 6, 7, 8, 9, 2, 3, 4, 5, 6, 7, 8, 9, 2, 3, 4, 5, 6, 7, 8, 9, 2, 3, 4, 5, 6, 7};

void setup() {
  
  
	// Pin initiation. The first pair of for-loops isn't strictly necessary, but the second pair prevents catastrophic malfunction (at least when using certain sketchy arduino boards).
	
	// Sense pins set to output
	for(int i = 2; i<10; i++){
		pinMode(i, OUTPUT); 
	}
	
	// Probe pins set to output
	for(int i = 24; i<32; i++){
		pinMode(i, OUTPUT); 
	}
	
	// Sense pins set LOW (otherwise they float weird and all hell breaks loose)
	for(int i = 2; i<10; i++){
		digitalWrite(i, LOW); 
	}
	
	// Probe pins set LOW
	for(int i = 24; i<32; i++){
		digitalWrite(i, LOW); 
	}

	// Serial init. Change this if it's too slow, although you should only be receiving 7 bits at a time...
	Serial.begin(9600);	
	
}



void loop() {
	
	// Only run if there is something to type in the serial receive buffer
	if(Serial.available() > 0){
		
		// Transform input byte to char for my reading convenience when the inevitable troubleshooting begins
		incomingByte = Serial.read();
		incomingLetter = char(incomingByte);
		
		// Iterate through lowercase.array to find the recieved char until it's either found or the whole array is searched
		for(int j = 0; j<47 && is_found==false; j++){
			search = lowercase_array[j];
			
			// If the letter is found, capture index and flip flag to "found"
			if(search == incomingLetter){
				index = j;
				is_uppercase = false;
				is_found = true;
			}
			
		}
		
		// If the letter wasn't previously found, search the uppercase.array until it's either found or the whole array is searched
		for(int k = 0; k<42 && is_found==false; k++){
			search = uppercase_array[k];
			
			// If the letter is found, capture index, mark character as uppercase and flip flag to "found"
			if(search == incomingLetter){
				index = k;
				is_uppercase = true;
				is_found = true;
			}

		}
		
		// If the letter wasn't found, sub with "*"
		if(is_found == false){
			index = 9;
			is_uppercase = true;
		}
		
		// Reset is.found flag
		is_found = false;
		
		// Lookup probe and sense pin coords from arrays
		if(is_uppercase == false){
			probe_pin = probe_array_lowercase[index];
			sense_pin = sense_array_lowercase[index];
		}
			
		if(is_uppercase == true){
			probe_pin = probe_array_uppercase[index];
			sense_pin = sense_array_uppercase[index];
		}
		
		// Make sure capslock is down if necessary
		if(is_uppercase == true){
			digitalWrite(31, HIGH);
			digitalWrite(3, HIGH);
			delay(50);
			digitalWrite(31, LOW);
			digitalWrite(3, LOW);
			delay(50);
		}
		
		// Time to have that character typed!
		digitalWrite(probe_pin, HIGH);
		digitalWrite(sense_pin, HIGH);
		delay(100);
		digitalWrite(probe_pin, LOW);
		digitalWrite(sense_pin, LOW);
		delay(character_delay);
		
		// If carriage return was pressed, wait for it to go back
		if(incomingLetter == '\n'){
			delay(1350);
		}
		
		// Make sure capslock is up if necessary
		if(is_uppercase == true){
			digitalWrite(31, HIGH);
			digitalWrite(2, HIGH);
			delay(50);
			digitalWrite(31, LOW);
			digitalWrite(2, LOW);
			delay(50);
		}
		
		// Reset appropriate variables
		is_found = false;
		is_uppercase = false;
		
		// Send "ready" signal if serial buffer is empty
		if(Serial.available() == 0){
			Serial.write("R");
		}
	}
	
}
