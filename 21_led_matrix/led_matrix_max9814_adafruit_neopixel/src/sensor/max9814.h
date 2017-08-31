#ifndef _MAX_9814_H_
#define _MAX_9814_H_

class Max9814 {
  
private:
  int m_pin;
public:
  Max9814(int pin) : m_pin(pin) {

  }

  unsigned int sampleSignal(int sampleWindowMs);
};

#endif
