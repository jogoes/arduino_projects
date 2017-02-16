/**
 * Simple RFID reader demo.
 * 
 * Demonstrates the usage of the Seeed RFID reader as described here:
 * https://www.seeedstudio.com/125Khz-RFID-module-UART-p-171.html
 *
 * Some instructions on how to use it can be found here:
 * http://www.instructables.com/id/Arduino-and-RFID-from-seeedstudio/
 * 
 * Connections:
 * 
 * Arduino   | RFID
 * --------------------
 * TX        | PIN 1
 * GND       | PIN 4
 * VCC (+5V) | PIN 5
 * 
 * Pin numbering on the RFID refers to the pin row consisting of 5 pins in total
 * with PIN 1 being the leftmost pin when holding the board oriented in front of you 
 * in a way that the 3-pin row is on top and the 5-pin row on the bottom.
 * 
 * The other pin row of 3 pins is not used for this project.
 */
#include <SoftwareSerial.h>

const int TX_PIN = 10;
const int RX_PIN = 11; // not used

// the ID we accept
const String ACCEPTED_ID = "05007E9452BD";
const int ID_LENGTH = ACCEPTED_ID.length();

SoftwareSerial RFID(TX_PIN, RX_PIN);

String msg;

void setup()  
{
  Serial.begin(9600);
  Serial.println("Serial Ready");

  RFID.begin(9600);
  Serial.println("RFID Ready");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
}

// reads all available characters
// from the RFID device and returns 
// them as a string
String readChars() {
  String chars;
  while(RFID.available()>0){
    char c = RFID.read(); 
    if(c < 32) {
      continue;
    }
    chars += c;
  }
  return chars;
}

void checkId(String id) {
  // in case the read ID is the same as our 
  // accepted ID turn on the LED
  if(id == ACCEPTED_ID) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void loop(){    
  msg += readChars();
  
  if(msg.length() >= ID_LENGTH) {
    // the message is long enough now to contain an ID
    String id = msg.substring(0, ID_LENGTH);
    Serial.println(id);
    checkId(id);
    // keep the remaining characters 
    // for our next message
    msg = msg.substring(ID_LENGTH);
  }
}

