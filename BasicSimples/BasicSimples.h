// BasicSimples.h
#ifndef BasicSimples_h
#define BasicSimples_h

class SimpleSwitch
{
  private:
    int    m_Pin;
    bool   m_PullUP;
  public:
    SimpleSwitch(int Pin, bool SetAsPullUP) { m_Pin = Pin; m_PullUP = SetAsPullUP; if (m_PullUP) { pinMode(m_Pin, INPUT_PULLUP); } else { pinMode(m_Pin, INPUT); } }
    bool   GetState() { if (m_PullUP) { if (digitalRead(m_Pin) == LOW) { return true; } else { return false; } } else { if (digitalRead(m_Pin) == HIGH) { return true; } else { return false; } } }
};

class SimpleSensor
{
  private:
    int    m_Pin;
    double m_refVal;
  public:
    SimpleSensor(int Pin, double refVal) { m_Pin = Pin; pinMode(m_Pin, INPUT_PULLUP); m_refVal = refVal; }
    double  GetValue() { double Value = analogRead(m_Pin); Value = Value * (m_refVal/double(1023)); return Value; }
	int		GetIntValue() { return analogRead(m_Pin); }
};

class SimpleDigitalDevice
{
  private:
    int    m_Pin;
    bool   m_Invert;
  public:
    SimpleDigitalDevice(int Pin, bool Inverted) { m_Pin = Pin; pinMode(m_Pin, OUTPUT); m_Invert = Inverted; if (m_Invert) { digitalWrite(m_Pin, HIGH); } else { digitalWrite(m_Pin, LOW); } }
    void On() { if (m_Invert) { digitalWrite(m_Pin, LOW); } else { digitalWrite(m_Pin, HIGH); } }
    void Off() { if (m_Invert) { digitalWrite(m_Pin, HIGH); } else { digitalWrite(m_Pin, LOW); } } 
};

#endif