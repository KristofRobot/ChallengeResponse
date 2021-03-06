/*
   Generate data using random generator, so its quality can be tested.
   Stay as close to the original setup as possible (include radio, ...)

   Usage: configure your 512 bit key in hmacKey, set radio pipe addresses and channel

   May 2016 - Kristof Robot
   Based on GettingStarted_CallResponse.ino
   Dec 2014 - TMRh20 - Updated
   Derived from examples by J. Coliz <maniacbug@ymail.com>

   CHANGES
   - 27Dec2016 - v0.1
      * Initial version
*/

#include <SPI.h>
#include "RF24.h"
//#include <printf.h>   //only needed to be able to use radio.printDetails()
#include "sha256.h"
#include <Entropy.h>
#include <MemoryFree.h>

/*** User Config ***/
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10 */
RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const byte addresses[][6] = {"aaaaa","bbbbb"};

// Channel - to avoid interference with wifi, put it in the top 25 channels or so (max is 126)
const byte channel = 0;

// This pin will output a HIGH when challenge response cycle is succesful
const int OUTPUT_PIN = 4;
// Time to wait after succesfull output, in mseconds
const int WAIT_OUTPUT = 2000;

// Threshold for invalid attempts - after reaching this number, receiver blocks
const byte MAX_INVALID_ATTEMPTS = 5;

// Max time to wait before timing out, in microseconds
const long MAX_TIME = 2000000;

// Key - 64 bytes - equal to HMAC-SHA-256 blocksize - CHANGE THIS!!
const uint8_t hmacKey[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

/*** End User Config ***/

byte invalid_attempts = 0;
Sha256Class random_sha256;  //sha256 class for random generation

void setup(){
  Entropy.initialize();
  random_sha256.init();

  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);

  Serial.begin(115200);
  //Serial.println(F("Starting Receiver"));

  // Setup and configure radio
  radio.begin();
  radio.setChannel(channel);
  radio.setPALevel(RF24_PA_LOW); //use this with antenna version!
  //radio.setPALevel(RF24_PA_HIGH); //still too high for antenna version
  //radio.setPALevel(RF24_PA_MAX); //too high for antenna version
  radio.setDataRate(RF24_250KBPS);
  //radio.setPayloadSize(8); //32 is default, lower would increase performance?
  //radio.setRetries(15,15); //default is 5, 15

  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);

  radio.startListening();                       // Start listening

  //printf_begin();                       //only needed for printDetails
  //radio.printDetails();                         //requires printf

}

void loop(void) {
    unsigned long started_waiting_at, stopped_waiting_at, waiting_at;
    uint8_t* challenge;
    // Placeholder for nonce - reserve 32 bytes
    uint8_t nonce[]={
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    };
    bool timeout = false;
    // Placeholder for response - reserve 32 bytes
    uint8_t response[]={
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    };

    //waiting_at=micros();
    //while(radio.available()){              // Read available payload
    //radio.read(nonce,32);
    radio.stopListening();

    //delay(1000);
    challenge = getRandomNumber();
    //printHash(challenge);

    //Serial.print(F("Received nonce, returning challenge: "));
    radio.write(challenge, 32);
    //printHash(challenge);

    radio.startListening();

 /*   started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    while (!radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > MAX_TIME){            // If waited longer than MAX_TIME, indicate timeout and exit while loop
          timeout = true;
          break;
      }
    }

    stopped_waiting_at = micros();
    Serial.println(micros()-waiting_at);
    //Serial.print("Stopped waiting after ");
    //Serial.print(stopped_waiting_at-started_waiting_at);
    //Serial.println(" ms");*/

  /*  if (timeout) {
      //Serial.println("Challenge timed out...");
    }else {*/
      //Serial.println("Reading response...");
      //radio.read(response, 32);
      radio.stopListening();
      //Serial.println(micros()-waiting_at);
      //init HMAC - it is important to do this every time, otherwise it incorporates previous hashes, making transmitter and receiver go out of sync
      Sha256.initHmac(hmacKey,64);
      int i=0;
      for (i=0; i<32; i++) {
        Sha256.print(nonce[i]);
        Sha256.print(challenge[i]);
      }
      if (isHashEqual(response,Sha256.resultHmac())){
        //reset invalid_attempts
        //invalid_attempts = 0;
        //Serial.println("Activating output!");
        activateOutput();
      }else{
        //Serial.print(F("Invalid response, got:"));
        //printHash(response);
        //Serial.print(F(" - while expecting:"));
        //printHash(Sha256.resultHmac());
      }
    

/*
      if (invalid_attempts > MAX_INVALID_ATTEMPTS-1){
          //block
          //Serial.print(F("Max Attempts reached - blocking"));
          while(1) ; //Repeat forever, preventing function from re-starting
      }
*/

      //timeout = false;
      //radio.startListening();

    //Serial.println(micros()-waiting_at);
    //Serial.println(freeMemory());

}

void activateOutput(){
  //switch output on/off
   //digitalWrite(OUTPUT_PIN, HIGH);
   delay(WAIT_OUTPUT); //wait some time to let the output react
   //digitalWrite(OUTPUT_PIN, LOW);
}

bool isHashEqual(uint8_t* hash, uint8_t* hash2){
  int i;
  for (i=0; i<32; i++) {
    if (!(hash[i] == hash2[i])){
      return false;
    }
  }
  return true;
}


void printHash(uint8_t* hash) {
  int i;
  for (i=0; i<32; i++) {
    ////Serial.print("0123456789abcdef"[hash[i]>>4]);
    ////Serial.print("0123456789abcdef"[hash[i]&0xf]);
    Serial.write(hash[i]);
  }
  //Serial.println();
}


uint8_t* getRandomNumber(){
  // Using a basic whitening technique that takes the first byte of a new random value and builds up a 32-byte random value
  // This 32-byte random value is then hashed (SHA256) to produce the resulting nonce
  for (int i = 0; i < 32; i++) {
    //dont use whitening, use random number directly, to test randomness
    //random_sha256.write(Entropy.random(255));
    Serial.write(Entropy.random(255));
  }
  //Serial.println(Entropy.available());
  return random_sha256.result();
}

/*uint8_t* getRandomNumber(){
  // Using a basic whitening technique that takes the first byte of a new random value and builds up a 32-byte random value
  // This 32-byte random value is then hashed (SHA256) to produce the resulting nonce
  //Serial.println(Entropy.available());
  for (int i = 0; i < 32; i++) {
    //Serial.write(Entropy.random(255));
    //Serial.println(Entropy.available());
    Serial.print(Entropy.random(255), DEC); 
   
  }
  Serial.println();
  Serial.println(Entropy.available());
  //Serial.println();
  return random_sha256.result();
}*/
