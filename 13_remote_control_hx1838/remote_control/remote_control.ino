/**
 * Simple IR remote control demo for the HX1838.
 * 
 * Demonstrates the usage a infrared based remote control similar
 * to the one described here:
 * http://www.hobbytronics.co.uk/hx1838-infra-red-remote
 *  
 * Connections:
 * 
 * Arduino   | IR
 * --------------------
 * 11        | S
 * GND       | GND
 * VCC (+5V) | VIN
 */
 
#include <IRremote.h> 

const int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

int lastButtonCode = 0;

long getButtonCode() {
  long result = 0;
  if (irrecv.decode(&results)) {
    result = results.value;
    if(result != 0xffffffff) {
      lastButtonCode = result;
    } else {
      result = lastButtonCode;
    }
    irrecv.resume();
  } else {
    result = 0;
  }
  return result & 0xff;
}

void loop()
{
  int button = getButtonCode();
  if(button) {
    Serial.println(button, HEX);
  }
}
