// Source code
#include "Arduino.h"
#include "cTimedOccurence_Arduino.h"

double cTimedOccurence::Setup__8bit(int Frequency) // returns the value of compare match register
  {
    cli();//stop interrupts
    boolean Found = false;
    double CMRegister = 99999;
    int caseSwitch = 0;
    
    for (int i = 0; i < (sizeof(PrescalerArrayT2)/sizeof(*PrescalerArrayT2)); ++i)
    {
      CMRegister = ( 16000000 / (double((Frequency) * PrescalerArrayT2[i]) ) - 1);
      if ((CMRegister) < 256)
      {
        caseSwitch = i+1;
        Found = true;
        break;
      }
    }
    
    if (Found)
    {
      TCCR2A = 0;  // set entire TCCR2A register to 0
      TCCR2B = 0;  // same for TCCR2B
      TCNT2  = 0;  //initialize counter value to 0
      OCR2A = int(CMRegister);     // set compare match register timer
      
      switch (caseSwitch)
      {
        case 1: { TCCR2B |= (1 << CS20) | (0 << CS21) | (0 << CS22); break;}
        case 2: { TCCR2B |= (0 << CS20) | (1 << CS21) | (0 << CS22); break;}
        case 3: { TCCR2B |= (1 << CS20) | (1 << CS21) | (0 << CS22); break;}
        case 4: { TCCR2B |= (0 << CS20) | (0 << CS21) | (1 << CS22); break;}
        default:{ TCCR2B |= (0 << CS20) | (0 << CS21) | (0 << CS22); break;}
      }
      TCCR2A |= (1 << WGM21);      // turn on CTC mode
      // enable timer compare interrupt
      TIMSK2 |= (1 << OCIE2A);
      
      sei();  //allow interrupts
      return CMRegister;
    }
    else
    {
      sei();  //allow interrupts
      return CMRegister;
    }
  }
  
 
 double cTimedOccurence::Setup_16bit(int Frequency) // returns the value of compare match register
  {
    cli();//stop interrupts
    boolean Found = false;
    double CMRegister = 99999;
    int caseSwitch = 0;
    
    for (int i = 0; i < (sizeof(PrescalerArrayT1)/sizeof(*PrescalerArrayT1)); ++i)
    {
      CMRegister = ( 16000000 / (double((Frequency) * PrescalerArrayT1[i]) ) - 1);
      if ((CMRegister) < 65536)
      {
        caseSwitch = i+1;
        Found = true;
        break;
      }
    }
    
    if (Found)
    {
      TCCR1A = 0;// set entire TCCR1A register to 0
      TCCR1B = 0;// same for TCCR1B
      TCNT1  = 0;//initialize counter value to 0
      OCR1A = int(CMRegister);     // set compare match register timer 2
      
      switch (caseSwitch)
      {
        case 1: { TCCR1B |= (1 << CS10) | (0 << CS11) | (0 << CS12); break;}
        case 2: { TCCR1B |= (0 << CS10) | (1 << CS11) | (0 << CS12); break;}
        case 3: { TCCR1B |= (1 << CS10) | (1 << CS11) | (0 << CS12); break;}
        case 4: { TCCR1B |= (0 << CS10) | (0 << CS11) | (1 << CS12); break;}
        case 5: { TCCR1B |= (1 << CS10) | (0 << CS11) | (1 << CS12); break;}
        default:{ TCCR1B |= (0 << CS10) | (0 << CS11) | (0 << CS12); break;}
      }
      
      TCCR1B |= (0 << WGM10) | (0 << WGM11) | (1 << WGM12);      // turn on CTC mode
      // enable timer compare interrupt
      TIMSK1 |= (1 << OCIE1A);
      
      sei();  //allow interrupts
      return CMRegister;
    }
    else
    {
      sei();  //allow interrupts
      return CMRegister;
    }
  }