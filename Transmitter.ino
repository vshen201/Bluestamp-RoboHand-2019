/* Transmitter Code
*  Code to read Joystick position and transmit it with a NRF24L01+ to a receiver 
*/

#include <SPI.h>
#include <RF24.h>

#include <Servo.h> //Includes servo library


// Radio Configuration

RF24 radio(9, 10); //sets CE and CSN pins to 9 & 10

byte addresses[][6] = {"12345","23456"}; //sets addresses for communication
//change these values to have unique communication! they can be anything


bool radioNumber=1;
bool role = 1;  //Control transmit 1/receive 0


//flexpins
int p1 = 1;       
int p2 = 2;      
int p3 = 3;        
int p4 = 0;  

struct Data{
   int b1 ;             // create struct for data package
   int b2 ;   
   int b3 ; 
   int b4 ;   
} data;                  //initialize variable of struct type



void setup() {
    Serial.begin(9600);                   // Get ready to send data back for debugging purposes
    radio.begin();                        // Get the transmitter ready
    radio.openWritingPipe(addresses[1]);  // Where we send data out
    radio.openReadingPipe(1,addresses[0]); // Where we receive data back
    radio.setPayloadSize(32);   //Sets payload size, however this is the default of the library. 
    radio.stopListening();   //listens for receiver's confirmation
    //Set each flex sensor pin to input: this is necessary
    pinMode(p1, INPUT);
    pinMode(p2, INPUT);
    pinMode(p3, INPUT);
    pinMode(p4, INPUT);
// May want to make value smaller if you are sending a small amount of data per packet

}

void loop() {
    data.b1 = analogRead(p1) ;             // Read the joystick values, puts values into package variables
    data.b2 = analogRead(p2) ;   
    data.b3 = analogRead(p3) ; 
    data.b4 = analogRead(p4) ; 
    Serial.println(data.b1);
    Serial.println(data.b2);
    Serial.println(data.b3);
    Serial.println(data.b4);
 

    delay(50);                                            // to stop jittering data

    if(radio.write(&data, sizeof(data)),Serial.println("sent go"));   // writes values to receiver, prints confirmation
 

}
