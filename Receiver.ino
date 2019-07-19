/*  Receiver Code 
*   Code to receive data from NRF24L01+ */


#include <SPI.h>
#include <RF24.h>

//Radio Configuration
#include <Servo.h> //Includes servo library

Servo finger1, finger2, finger3, finger4;

int servoPin1 = 3;
int servoPin2 = 5;
int servoPin3 = 6;
int servoPin4 = 9;

RF24 radio(7,8);
byte addresses[][6] = {"12345","23456"}; // make sure this matches the transmitter adresses

bool radioNumber=0;
bool role = 0;  //Control transmit/receive



struct Data{
   int b1 ;             //Create struct and create variable with that data-type
   int b2 ;   
   int b3 ; 
   int b4 ;   
}; 
Data data;





void setup() { 
    Serial.begin(9600);        
    radio.begin();             // Initializes radio
    radio.setPALevel(RF24_PA_LOW);   // Sets power output to low.
    radio.openWritingPipe(addresses[0]); //opens writing pipeline
    radio.openReadingPipe(1,addresses[1]); //opens reading pipeline
    radio.setPayloadSize(32); //sets payload size, but this is default
    radio.startListening();
    //Attach the servo objects to their respective pins
    finger1.attach(servoPin1);
    finger2.attach(servoPin2);
    finger3.attach(servoPin3);
    finger4.attach(servoPin4);

    /* set each servo pin to output; I'm not acutally sure if this is
    even necessary, but I did just in case it is */
    pinMode(servoPin1, OUTPUT);
    pinMode(servoPin2, OUTPUT);
    pinMode(servoPin3, OUTPUT);
    pinMode(servoPin4, OUTPUT);   
}
void loop() {
    delay(50);               //increase for debuggy, decrease to decrease jitter
    if(radio.available()){
        Serial.println("afawefw");
        radio.read(&data,sizeof(data)); //reads value of go
        

    } 

    Serial.println(data.b1);
    Serial.println(data.b2);
    Serial.println(data.b3);
    Serial.println(data.b4);
    /* Defines "pos" variables as being proportional to the flex inputs.
    The 400 to 700 value range seemed adequate for my sensors, but you can change
    yours accordingly. */
    int pos1 = map(data.b1, 400, 700, 0, 180);
    pos1 = constrain(pos1, 0, 180);
    int pos2 = map(data.b2, 400, 700, 0, 180);
    pos2 = constrain(pos2, 0, 180);
    int pos3 = map(data.b3, 400, 700, 0, 180);
    pos3 = constrain(pos3, 0, 180);
    int pos4 = map(data.b4, 200, 500, 0, 180);
    pos4 = constrain(pos4, 0, 180);
    
    //Tells servos to move by the amount specified in the "pos" variables
    finger1.write(pos1);
    finger2.write(pos2);
    finger3.write(pos3);
    finger4.write(pos4);
                 
    }
