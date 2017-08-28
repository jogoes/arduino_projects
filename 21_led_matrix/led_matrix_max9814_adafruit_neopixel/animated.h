#ifndef _ANIMATED_H_
#define _ANIMATED_H_

class Animated {
  private:
    int m_delayMs;
    int m_lastMillis;

  public:
    Animated(int delayMs) : m_delayMs(delayMs) {
      m_lastMillis = millis();
    }

  public:
    bool requiresUpdate() {
      return (millis() - m_lastMillis > m_delayMs);
    }
    
    void next(bool forceUpdate) {
      if (requiresUpdate()) {
        onNext();
        onShow();
        m_lastMillis = millis();
      } else if(forceUpdate) {
        onShow();
      }
    }

    virtual void onShow() = 0;    
    virtual void onNext() = 0;
};

#endif
