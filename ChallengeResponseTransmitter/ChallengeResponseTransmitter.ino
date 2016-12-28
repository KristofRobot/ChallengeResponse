/*
   Challenge-Response protocol between two nodes - transmitter side
   Use together with ChallengeResponseReceiver

   Usage: configure your 512 bit key in hmacKey, set radio pipe addresses and channel

   May 2016 - Kristof Robot
   Based on GettingStarted_CallResponse.ino
   Dec 2014 - TMRh20 - Updated
   Derived from examples by J. Coliz <maniacbug@ymail.com>

   CHANGES
   - 28Dec2016 - v1.1
      * Implemented double click
   - 01May2016 - v1.0
      * Tuned radio settings - stable working version
   - 06Mar2016 - v0.2
      * Adding radio powerdown statements to lower standby power usage to less than 1uA
   - 27Feb2016 - v0.1
      * Initial version

   Configure fuses as follows:
   -U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0x07:m
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

// Channel - to avoid interference with wifi, put it in the top 25 channels or so (max is 126)
const byte CHANNEL = 0;

// Max time to wait before timing out, in microseconds
const long MAX_TIME = 2000000;

// Max time between clicks, in microseconds
const long MAX_PRESS_TIME = 500000;

// Min time between clicks, in milliseconds
const long MIN_PRESS_TIME = 200;

// Button pin MUST be external interrupt pin!!
const byte buttonPin = 2;  //pin 2 on connected to GND through 10K resistor, button connects to Vcc when pressed (see Button sketch schematic)
//const byte ledPin = 8;  //pin connected to LED - 0 on board; 8 on test

// Key - 64 bytes - equal to HMAC-SHA-256 blocksize - CHANGE THIS!!
const uint8_t hmacKey[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

bool timeout=false;
bool singlePress=false;
bool doublePress=false;

//sha256 class for random generation
Sha256Class random_sha256;

//placeholder for challenge - 32 bytes
uint8_t challenge[]={
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

void setup(){
  //Entropy.initialize();  //Entropy is not compatible with LowPower library

  /*
   *  analogRead has a rather low variation, so this is a poor way of seeding
   *  i.e. the pseudo generated random numbers will be fairly predictable.
   *  Not a problem in our use case, as the strong random number is coming from the receiver
   *  and the transmitter random number serves as a nonce (unique value)
   *  to avoid repetition of (transmitter nonce,receiver challenge) tuple.
  */
  randomSeed(analogRead(0));

  random_sha256.init();
  pinMode(buttonPin, INPUT);
  /*pinMode(ledPin, OUTPUT);

  //blink at startup
  digitalWrite(ledPin, LOW);
  delay(1000);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);*/

  //Serial.begin(115200);
  //Serial.println(F("Starting Garage Door Transmitter"));

  //Setup and configure radio
  radio.begin();
  radio.setChannel(CHANNEL);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS); //1MBPS by default - 250Kbps reputedly is more reliably
  //radio.setPayloadSize(8); //32 is default, lower would increase performance?
  //radio.setRetries(15,15); //delay, count, default is 5, 15
  //radio.setAutoAck(false); //disable auto ack, enabled by default
  radio.openWritingPipe(addresses[1]);        // Both radios listen on the same pipes by default, but opposite addresses
  radio.openReadingPipe(1,addresses[0]);      // Open a reading pipe on address 0, pipe 1

  //printf_begin();                       //only needed for printDetails
  //radio.printDetails();                         //requires printf
}

void loop(void) {
    unsigned long timer, started_waiting_at, started_pressing_at;
    uint8_t *response, *nonce;

    //power down radio
    radio.powerDown();

    /***  Interrupt stuff ***/
    // Allow wake up pin to trigger interrupt on low.
    attachInterrupt(digitalPinToInterrupt(buttonPin), wakeUp, HIGH);

    // Enter power down state with ADC and BOD (brown out detection) module disabled.
    // Wake up when wake up pin is low.
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

    // Disable external pin interrupt on wake up pin.
    detachInterrupt(digitalPinToInterrupt(buttonPin));

    /*** Double click detection state machine ***/
    //First press should be released within MAX_PRESS_TIME us to register
    //Time between first and second press be in interval [MIN_PRESS_TIME ms,MAX_PRESS_TIME us[
    //Second press should be released within MIN_PRESS_TIME ms
    singlePress=false;
    doublePress=false;
    started_pressing_at = micros();

    delay(MIN_PRESS_TIME);

    //wait until button released, or bail out
    while(micros() - started_pressing_at < MAX_PRESS_TIME ){            // If waited longer than MAX_PRESS_TIME, dont count as double click
      if (digitalRead(buttonPin)==LOW) {
        singlePress=true;
        started_pressing_at=micros();
        break;
      }
    }

    //wait for second click
    if (singlePress){
      delay(MIN_PRESS_TIME);

      while(micros() - started_pressing_at < MAX_PRESS_TIME ){            // If waited longer than MAX_PRESS_TIME, dont count as double click
        if (digitalRead(buttonPin)==HIGH) {
          doublePress=true;
          break;
        }
      }
    }

    delay(MIN_PRESS_TIME);

    if (doublePress && digitalRead(buttonPin)==LOW){

      //power up radio
      radio.powerUp();
  
      /*** Do stuff when woken up ***/
      unsigned long time = micros();                          // Record the current microsecond count
      //digitalWrite(ledPin, HIGH);
  
      nonce = getRandomNumber();
      //Serial.print(F("Sending nonce: "));
      radio.write(nonce, 32);
  
      radio.startListening();
      //printHash(nonce);
  
      started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
      while (!radio.available() ){                             // While nothing is received
        if (micros() - started_waiting_at > MAX_TIME ){            // If waited longer than 2000ms, indicate timeout and exit while loop
            timeout = true;
            break;
        }
      }
  
     //digitalWrite(ledPin, LOW);
  
     if(timeout){
        radio.stopListening();
        //Serial.println(F("Command timed out..."));
     }else{
        // Read the challenge
        radio.read(challenge, 32);
  
        timer = micros();
        //Serial.print(F("Got challenge "));
        //printHash(challenge);
        //Serial.print(F(" round-trip delay: "));
        //Serial.print(timer-time);
        //Serial.println(F(" microseconds"));
  
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
  
        radio.write(response, 32);
        //Serial.print(F("Provided response "));
        //printHash(response);
      }
  
      timeout = false;
      
    } 
}

/*
void printHash(uint8_t* hash) {
  int i;
  for (i=0; i<32; i++) {
    ////Serial.print("0123456789abcdef"[hash[i]>>4]);
    ////Serial.print("0123456789abcdef"[hash[i]&0xf]);
    //Serial.print(hash[i]);
  }
  //Serial.println();
}
*/

/*
 * Using built-in random function, seeded with analogRead.
 * This is a poor way of seeding, as analogRead has a fairly low variation.
 * I.e. the pseudo generated random numbers will be fairly predictable
 * Not a problem in our use case, as the strong random number is coming from the receiver
 * and the transmitter random number serves as a nonce (unique value)
 * to avoid repetition of (transmitter nonce,receiver challenge) tuple.
 */
uint8_t* getRandomNumber(){
  // Using a basic whitening technique that takes the first byte of a new random value and builds up a 32-byte random value
  // This 32-byte random value is then hashed (SHA256) to produce the resulting nonce
  for (int i = 0; i < 32; i++) {
    //random_sha256.write(Entropy.random(255));  //entropy lib is not compatible with low power
    random_sha256.write(random(255));
  }
  return random_sha256.result();
}

void wakeUp()
{
    // Just an empty handler for the pin interrupt.
}
