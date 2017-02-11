#ifndef _ACCELERATOR_INFO_H_
#define _ACCELERATOR_INFO_H_

/**
 * Helper class used to simplify tracking of minimums and maximums of values.
 */
class MinMaxValue {
  private:
    float m_min;
    float m_max;
    float m_value;

  public:
    MinMaxValue() : m_min(3E+38), m_max(-3E+38), m_value(0) { }

  public:
    float getMin() const { return m_min; }
    float getMax() const { return m_max; } 
    float getValue() const { return m_value; }

    void update(float value) {
      m_min = min(m_min, value);
      m_max = max(m_max, value);
      m_value = value;
    }

  public:
    String toString() const {
      return String("(min=") + String(m_min) + ", max=" + String(m_max) + String(", value=") + String(m_value) + String(")");
    }  
};

/**
 * Helper class wrapping an ADXL345 accelerometer simplifying access to min, max and current accelerometer values.
 */
class AcceleratorInfo {
  private:
    Adafruit_ADXL345_Unified& m_accel;

  private:
    MinMaxValue m_x;
    MinMaxValue m_y;
    MinMaxValue m_z;
    
  public:
    AcceleratorInfo(Adafruit_ADXL345_Unified& accel) : m_accel(accel) {
    }

  public:
    /**
     * Reads the current values from the accelerometer and updates
     * the internal state including e.g. calculating the maximum
     * and minimum accelerometer values.
     */
    void update() {
      sensors_event_t accelEvent;  
      m_accel.getEvent(&accelEvent);

      m_x.update(accelEvent.acceleration.x);
      m_y.update(accelEvent.acceleration.y);
      m_z.update(accelEvent.acceleration.z);
    }

    public:
      const MinMaxValue& getAccelX() const { return m_x; }
      const MinMaxValue& getAccelY() const { return m_y; }
      const MinMaxValue& getAccelZ() const { return m_z; }
   public:
      String toString() const {
        return 
          String("X: ") + m_x.toString() +
          String("\nY: ") + m_y.toString() +
          String("\nZ: ") + m_z.toString();
      }
};

#endif
