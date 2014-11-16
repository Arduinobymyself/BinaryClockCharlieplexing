/*
#####################################################################################
#  	Arquivo:            Binary_Clock_Charlieplexing.ino                                             
#       Micro-processador:  Arduino UNO ou Teensy 2.0++      
#  	Linguagem:	    Wiring / C /Processing /Fritzing / Arduino IDE
#       Versão:             V.1
#						
#	Objetivo:           Arduino Binary Clock using Charlieplexing method
#										  
#	Funcionamento:	    Just a Binary clock
#                           
#
#			
#   Autor:              Marcelo Moraes 
#   Data:               23/02/14	
#   Local:              Sorocaba - SP, Brazil	
#					
#####################################################################################
 
  Este projeto contém código de domínio público.
  A modificação é permitida sem aviso prévio.
  
LED BINARY CLOCK
The original project by Kevin Darrah

For the Charlieplexing method (20 LEDs)
n(n-1)=LED Where n = line numbers and LED is the LED amouth
20 LEDs so n(n-1)=20 then n=5

Line 1 - arduino pin 2
Line 2 - arduino pin 3
Line 3 - arduino pin 4
Line 4 - arduino pin 5
Line 5 - arduino pin 6

hour10    LED-1 and LED-2
hour      LED-3, LED-4, LED-5 and LED-6
min10     LED-7, LED-8 and LED-9
min       LED-10, LED-11, LED-12 and LED-13
sec10     LED-14, LED-15 and LED-16
sec       LED-17, LED-18, LED-19 and LED-20

Duvidas e ou sugestões, envie para:
Marcelo Moraes
arduinobymyself.blogspot.com.br
arduinobymyself@gmail.com
*/



#include <Wire.h>

// objects definition
//RTC_DS1307 RTC;

int i, data=0, t;
int sec, sec10=0, minute=0, min10=0, hour=0, hour10=0;


void setup(void){
  Wire.begin();           
  Serial.begin(9600); 
  
  
  // I2C communication
  // SCL connected to arduino Analog pin 5
  // SDA connected to arduino Analog pin 4
  
  // configuring I2C RTC DS1307 device
  // the first memory addres 0x0000 stores the seconds
  // the second memory address 0x0001 stores the minutes
  // the third memory address 0x0002 stores the hours
  
  // the code below is to set the clock on the first time
  // after settled, comment the lines below
  Wire.beginTransmission(B1101000); // device address
  Wire.write(0x00);                  // start from th first memory address
  Wire.write(0x00); // write the seconds 00 (b7 = ch=0; b6,b5,b4 = sec10; b3,b2,b1,b0 = sec1)
  Wire.write(0x46); // write the minutes 46 (b7 = 0; b6,b5,b4 = min10; b3,b2,b1,b0 = min1)
  Wire.write(B00010101); // Write the hours 15 (b7 = 0; b6 = 12/24; b5,b4 = h10;  b3,b2,b1,b0 = h1)
  Wire.endTransmission();
  
  
}




void loop(){
  
  //delay(1000);
  Wire.beginTransmission(B1101000); // starts the device communication 
  Wire.write(0x00);   // starts from first memory address
  Wire.endTransmission(); // ends the device communication
  //delay(1);
  Wire.requestFrom(B1101000,3); // request 3 bytes from this device
 
  sec = Wire.read(); // reads first byte "seconds"
  minute = Wire.read(); // reads second byte "minutes"
  hour = Wire.read(); // reads third byte "hours"
    
  
  sec10 = sec >> 4; // shift over to the right 4 bits to get the sec10
  for (i=0; i<4; i++)
  bitClear(sec, i+4); // clear right portin to get exactly the sec1
  
  min10 = minute >> 4;
    for (i=0; i<4; i++)
  bitClear(minute, i+4);
  bitClear(hour, 5);
  bitClear(hour, 6);
  
  hour10 = hour >> 4;
  bitClear(hour, 4);
    
  // just for debbuging
  // use serial monitor to check the values
  Serial.print(sec10, DEC);
  Serial.print(sec, DEC);
  Serial.print(min10, DEC);
  Serial.print(minute, DEC);
  Serial.print(hour10, DEC);
  Serial.println(hour, DEC);
  
  // write the values to LEDs
  Write(hour10, hour, min10, minute, sec10, sec);
}





void Write(int h10, int h, int m10,int m, int s10, int s){
  if(h10==1){// LED-1
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    reset();
  }
  if(h10==2){// LED-2
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    reset();
  }
  if(h==1){// LED-3
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    reset(); 
  }
  if(h==2){// LED-4
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    reset();  
  }
  if(h==3){// LED-3 and LED-4
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    reset();
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    reset();    
  }  
  if(h==4){// LED-5
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(5, HIGH);
    reset();
  }
  if(h==5){// LED-5 and LED-3
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(5, HIGH);
    reset();
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    reset();
  }
  if(h==6){// LED-5 and LED-4
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(5, HIGH);
    reset();
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    reset();
  }
  if(h==7){// LED-5 and LED-4 and LED-3
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(5, HIGH);
    reset();
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    reset();
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    reset();  
  }
  if(h==8){// LED-6
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(2, HIGH);
    digitalWrite(5, LOW);
    reset(); 
  } 
  if(h==9){// LED-6 and LED-3
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(2, HIGH);
    digitalWrite(5, LOW);
    reset(); 
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    reset();
  }
  if(m10==1){// LED-7
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(2, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(6, HIGH);
    reset(); 
  }
  if(m10==2){// LED-8
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(2, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(2, HIGH);
    digitalWrite(6, LOW);
    reset(); 
  }
  if(m10==3){// LED-7 and LED-8
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(2, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(2, HIGH);
    digitalWrite(6, LOW);
    reset(); 
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(2, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(6, HIGH);
    reset();
  }
  if(m10==4){// LED-9
    pinMode(2, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    reset(); 
  }
  if(m10==5){// LED-9 and LED 7
    pinMode(2, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    reset();
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(2, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(6, HIGH);
    reset();  
  }
  if(m==1){// LED-12
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(6, INPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    reset(); 
  }
  if(m==2){// LED-11
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(6, INPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    reset(); 
  }
  if(m==3){// LED-11 and LED-12
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(6, INPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    reset(); 
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(6, INPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    reset(); 
  }
  if(m==4){// LED-10
    pinMode(2, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    reset(); 
  }
  if(m==5){// LED-10 and LED-12
    pinMode(2, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(6, INPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    reset(); 
  }
  if(m==6){// LED-10 and LED-11
    pinMode(2, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(6, INPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    reset(); 
  }
  if(m==7){// LED-10 and LED-11 and LED-12
    pinMode(2, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(6, INPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(6, INPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    reset(); 
  }
  if(m==8){// LED-13
    pinMode(2, INPUT);
    pinMode(4, INPUT);
    pinMode(6, INPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    digitalWrite(3, LOW);
    reset(); 
  }
  if(m==9){// LED-13 and LED-12
    pinMode(2, INPUT);
    pinMode(4, INPUT);
    pinMode(6, INPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    digitalWrite(3, LOW);
    reset(); 
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(6, INPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    reset(); 
  }
  if(s10==1){// LED-14
    pinMode(2, INPUT);
    pinMode(4, INPUT);
    pinMode(6, INPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    reset(); 
  }
  if(s10==2){// LED-15
    pinMode(2, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(3, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    digitalWrite(3, LOW);
    reset(); 
  }
  if(s10==3){// LED-14 and LED-15
    pinMode(2, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(3, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    digitalWrite(3, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(4, INPUT);
    pinMode(6, INPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    reset();  
  }
  if(s10==4){// LED-16
    pinMode(2, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(3, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(3, HIGH);
    digitalWrite(6, LOW);
    reset(); 
  }  
  if(s10==5){// LED-16 and LED-14
    pinMode(2, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(3, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(3, HIGH);
    digitalWrite(6, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(4, INPUT);
    pinMode(6, INPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    reset();
  }   
  if(s==1){// LED-18
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    reset(); 
  }  
  if(s==2){// LED-17
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    reset(); 
  }
  if(s==3){// LED-17 and LED-18
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    reset(); 
  }
  if(s==4){// LED-20
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(4, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(6, LOW);
    reset(); 
  }
  if(s==5){// LED-20 and LED-18
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(4, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(6, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    reset(); 
  }
  if(s==6){// LED-20 and LED-17
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(4, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(6, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    reset(); 
  }
  if(s==7){// LED-20 and LED-17 and LED18
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(4, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(6, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    reset(); 
  }
  if(s==8){// LED-19
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(4, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    digitalWrite(4, LOW);
    reset(); 
  }
  if(s==9){// LED-19 adn LED-18
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(5, INPUT);
    pinMode(4, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    digitalWrite(4, LOW);
    reset();
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    reset(); 
  }
 
}//write





// reset the LEDs and promotes a delay
void reset(){
  delay(2); // 2ms
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW); 
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
}//reset




