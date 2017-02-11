#ifndef _MPR_121_UTIL_H_
#define _MPR_121_UTIL_H_

/**
 * Helper class used to simplify access to the MPR121 capacitive touch sensor.
 */
class MPR121Helper {
  private:
    Adafruit_MPR121& m_mpr121;

  private:
    void (*m_onTouched)(uint8_t);
    void (*m_onReleased)(uint8_t);

  private:    
    // Keeps track of the last pins touched
    // so we know when buttons are 'released'
    uint16_t m_lasttouched;
    uint16_t m_currtouched;

  private:
    static void doNothing(uint8_t pin) {};
    
  public:
    MPR121Helper(Adafruit_MPR121& mpr121) : m_mpr121(mpr121) {
      m_lasttouched = 0;
      m_currtouched = 0;

      registerOnTouched(&doNothing);
      registerOnReleased(doNothing);
    }

  public:
    /**
     * Register function to be called when pin was touched.
     * Only one function can be registered at any time.
     */
    void registerOnTouched(void (*onTouched)(uint8_t)) {
      m_onTouched = onTouched;
    }
    /**
     * Register function to be called when pin was touched.
     * Only one function can be registered at any time.
     */
    void registerOnReleased(void (*onReleased)(uint8_t)) {
      m_onReleased = onReleased;
    }
    
    void update() {
      // get the currently touched pads
      // each bit in the returned value represents the state of the 
      // corresponding pin
      m_currtouched = m_mpr121.touched();
    
      // iterate through all pins and check their status
      for (uint8_t i=0; i<12; i++) {
        // _BV(i) shifts 1 to left by the specified number, e.g. _BV(2) would be 00000100
        uint16_t checkBit = _BV(i);
        
        // if it *is* touched and *wasnt* touched before, alert!
        if ((m_currtouched & checkBit) && !(m_lasttouched & checkBit) ) {
          m_onTouched(i);
        }
        // if it *was* touched and now *isnt*, alert!
        if (!(m_currtouched & checkBit) && (m_lasttouched & checkBit) ) {
          m_onReleased(i);
        }
      }
    
      // update our last state
      m_lasttouched = m_currtouched;
    }

    void printDebugInfo() {
      // debugging info, what
      Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(m_mpr121.touched(), HEX);
      Serial.print("Filt: ");
      for (uint8_t i=0; i<12; i++) {
        Serial.print(m_mpr121.filteredData(i)); Serial.print("\t");
      }
      Serial.println();
      Serial.print("Base: ");
      for (uint8_t i=0; i<12; i++) {
        Serial.print(m_mpr121.baselineData(i)); Serial.print("\t");
      }
      Serial.println();
      
      // put a delay so it isn't overwhelming
      delay(100);
    }    
};
#endif
