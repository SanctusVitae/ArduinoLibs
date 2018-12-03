// cTimedOccurence_Arduino.h
#ifndef cTimedOccurence_Arduino_h
#define cTimedOccurence_Arduino_h

class cTimedOccurence
{
private:
    const int PrescalerArrayT2[4] = { 1, 8, 32, 64 };
    const int PrescalerArrayT1[5] = { 1, 8, 64, 256, 1024 };

public:
	// Methods
			cTimedOccurence() { }
	double Setup__8bit(int Frequency); // returns the value of compare match register
	double Setup_16bit(int Frequency); // returns the value of compare match register
};

#endif

/* Use with || Leave it as it is, do not make it into class, you can only have one timer event anyway

ISR(TIMER1_COMPA_vect)
{
  myMotor.asmRun();  // any code to run periodicaly
}

*/