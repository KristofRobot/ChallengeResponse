/*
   Challenge-Response protocol between two nodes - transmitter side
   Use together with ChallengeResponseReceiver

   Usage: configure your 512 bit key in hmacKey, set radio pipe addresses and channel

   February 2016 - Kristof Robot
   Based on GettingStarted_CallResponse.ino
   Dec 2014 - TMRh20 - Updated
   Derived from examples by J. Coliz <maniacbug@ymail.com>

   CHANGES
   - 06Mar2016 - v0.2
      * Adding radio powerdown statements to lower standby power usage to less than 1uA
   - 27Feb2016 - v0.1
      * Initial version
*/

#include <SPI.h>
#include "RF24.h"
#include "sha256.h"
#include "LowPower.h"
//#include <printf.h>   //only needed to be able to use radio.printDetails()
//#include <Entropy.h>  //not working together with LowPower library

/*** User Config ***/
// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10
RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const byte addresses[][6] = {"aaaaa","bbbbb"};

// Channel
const byte channel = 0;

// Max time to wait before timing out, in microseconds
const long MAX_TIME = 2000000;

// Activation pin - connected to GND through 10K resistor, button connects to Vcc when pressed (see Button sketch schematic)
const byte buttonPin = 2;

// Key - 64 bytes - equal to HMAC-SHA-256 blocksize - CHANGE THIS!!
const uint8_t hmacKey[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

/*** End User Config ***/

//sha256 class for random generation
Sha256Class random_sha256;

void setup(){
  //Entropy.initialize();
  randomSeed(analogRead(0));
  random_sha256.init();
  pinMode(buttonPin, INPUT);

  //Serial.begin(115200);
  //Serial.println(F("Starting Garage Door Transmitter"));

  //Setup and configure radio
  radio.begin();
  radio.setChannel(channel);
  //radio.setPALevel(RF24_PA_LOW);   //for testing
  radio.setPALevel(RF24_PA_HIGH);

  radio.openWritingPipe(addresses[1]);        // Both radios listen on the same pipes by default, but opposite addresses
  radio.openReadingPipe(1,addresses[0]);      // Open a reading pipe on address 0, pipe 1

  //printf_begin();                       //only needed for printDetails
  //radio.printDetails();                         //requires printf
}

void loop(void) {
    //unsigned long timer
    unsigned long started_waiting_at;
    uint8_t *response;
    uint8_t *nonce;
    bool timeout=false;
    //placeholder for challenge - 32 bytes
    uint8_t challenge[]={
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    };

    //power down radio
    radio.powerDown();

    /***  Interrupt stuff ***/
    // Allow wake up pin to trigger interrupt on low.
    attachInterrupt(digitalPinToInterrupt(buttonPin), wakeUp, HIGH);

    // Enter power down state with ADC and BOD (brown out detection) module disabled.
    // Wake up when wake up pin is low.
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

    // Disable external pin interrupt on wake up pin.
    detachInterrupt(0);

    /*** Do stuff when woken up ***/
    //power up radio
    radio.powerUp();

    unsigned long time = micros();                          // Record the current microsecond count

    nonce = getRandomNumber();
    //Serial.print(F("Sending nonce: "));
    radio.write(nonce, 32);
    //printHash(nonce);
    radio.startListening();
    delay(100); //gives the transmitter some time to come back

    started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    while (!radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > MAX_TIME ){            // If waited longer than 2000ms, indicate timeout and exit while loop
          timeout = true;
          break;
      }
    }

    if (timeout) {
      radio.stopListening();
      //Serial.println("Command timed out...");
    } else {
      radio.read(challenge, 32);                  // Read the challenge

      /*
      timer = micros();
      Serial.print(F("Got challenge "));
      printHash(challenge);
      Serial.print(F(" round-trip delay: "));
      Serial.print(timer-time);
      Serial.println(F(" microseconds"));
      */

      radio.stopListening();

      //process challenge and return
      //init HMAC - it is important to do this every time, otherwise it incorporates previous hashes, making transmitter and receiver go out of sync
      Sha256.initHmac(hmacKey,64);
      int i=0;
      for (i=0; i<32; i++) {
        Sha256.print(nonce[i]);
        Sha256.print(challenge[i]);
      }
      response = Sha256.resultHmac();
      radio.write(response,32);

      //Serial.print(F("Provided response "));
      //printHash(response);
    }
}

/*
void printHash(uint8_t* hash) {
  int i;
  for (i=0; i<32; i++) {
    Serial.print("0123456789abcdef"[hash[i]>>4]);
    Serial.print("0123456789abcdef"[hash[i]&0xf]);
  }
  Serial.println();
}
*/

uint8_t* getRandomNumber(){
  // Using a basic whitening technique that takes the first byte of a new random value and builds up a 32-byte random value
  // This 32-byte random value is then hashed (SHA256) to produce the resulting nonce
  for (int i = 0; i < 32; i++) {
    //random_sha256.write(Entropy.random(255));
    random_sha256.write(random(255));
  }
  return random_sha256.result();
}

void wakeUp()
{
    // Just an empty handler for the pin interrupt.
}
