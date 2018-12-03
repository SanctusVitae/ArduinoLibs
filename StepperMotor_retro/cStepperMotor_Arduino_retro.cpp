// Source code
#include "Arduino.h"
#include "cStepperMotor_Arduino_retro.h"

cStepperMotor::cStepperMotor(int PinStep, int PinDir, long StepMin, long StepMax)
{ 
    m_InOut = false;
    m_pinMotor = PinStep;
    m_PinDir = PinDir;
    m_ErrorCode = E_ErrorCode::DestReached;
	
	m_DirectionValue = LOW;
    
    pinMode(m_pinMotor, OUTPUT);
    pinMode(m_PinDir, OUTPUT);
    
	if (StepMin < StepMax) { m_Bounds1 = StepMin; m_Bounds2 = StepMax; }
	else { m_Bounds1 = 0; m_Bounds2 = 0; m_ErrorCode = E_ErrorCode::ErrorInput; }
    
    m_CurrStep = 0;
    m_GoToStep = 0;
    m_InvertMovement = true;
	
	m_Enable.useEnable = false;
	m_Enable.isEnabled = false;
}

// Getters and setters

void cStepperMotor::asmSetZero()
	{ m_CurrStep = 0; m_GoToStep = 0; }

void cStepperMotor::asmGoToZero()
	{ m_GoToStep = 0; }

void cStepperMotor::asmGoToMax()
	{ m_GoToStep = m_Bounds2; }

void cStepperMotor::asmGoToMin()
	{ m_GoToStep = m_Bounds1; }

void cStepperMotor::asmSetMin(long Location)
	{ m_Bounds1 = Location; }

void cStepperMotor::asmSetMax(long Location)
	{ m_Bounds2 = Location; }

long cStepperMotor::asmGetStep()
	{ return m_CurrStep; }
	
long cStepperMotor::asmGetMax()
	{ return m_Bounds2; }
	
long cStepperMotor::asmGetMin()
	{ return m_Bounds1; }

int cStepperMotor::asmGetState()
	{ return m_ErrorCode; }

void cStepperMotor::asmMoveTo(long Location)
	{ m_GoToStep = Location; }

void cStepperMotor::asmStopMovement()
	{ m_GoToStep = m_CurrStep; }
// logic
	
void cStepperMotor::asmSetDir(bool InvertMovement)  // sets pin for stepper motor direction to correct values
	{ 
		m_InvertMovement = !InvertMovement;

		if (m_InvertMovement)
		{ digitalWrite(m_PinDir, m_DirectionValue); m_Direction = E_Direction::DirFwd; }
		else
		{ digitalWrite(m_PinDir, !m_DirectionValue); m_Direction = E_Direction::DirBckwd; }
	}
	
void cStepperMotor::asmUseEnabling(int Pin, bool voltageInverted)
{
	m_Enable.useEnable = true;
	m_Enable.pinEnable = Pin;
	m_Enable.vInverted = voltageInverted;
	pinMode(m_Enable.pinEnable, OUTPUT);
	
		if (!m_Enable.vInverted) { digitalWrite(m_Enable.pinEnable, HIGH); }
		else { digitalWrite(m_Enable.pinEnable, LOW); }
}

void cStepperMotor::asmMotEnable()
{
	if (m_Enable.useEnable) { m_Enable.isEnabled = true; } else { m_Enable.isEnabled = false; }
}

void cStepperMotor::asmMotDisable()
{
	if (m_Enable.useEnable) { m_Enable.isEnabled = false; } else { m_Enable.isEnabled = true; }
}

void cStepperMotor::asmEndEnabling()
{
	m_Enable.useEnable = false;
	m_Enable.pinEnable = -1;
	m_Enable.vInverted = false;
}

// Private Method

void cStepperMotor::CheckAndChangeDir()
  {
      if (m_GoToStep > m_CurrStep)
      {
        if (m_InvertMovement)
        { if (m_Direction != E_Direction::DirFwd) { digitalWrite(m_PinDir, m_DirectionValue); m_Direction = E_Direction::DirFwd; } }
        else
        { if (m_Direction != E_Direction::DirBckwd) {  digitalWrite(m_PinDir, !m_DirectionValue); m_Direction = E_Direction::DirBckwd; } }
      }
      else
      {
        if (m_InvertMovement)
        { if (m_Direction != E_Direction::DirBckwd) { digitalWrite(m_PinDir, !m_DirectionValue); m_Direction = E_Direction::DirBckwd; } }
        else
        { if (m_Direction != E_Direction::DirFwd) { digitalWrite(m_PinDir, m_DirectionValue); m_Direction = E_Direction::DirFwd; } }
      }
  }
  
 void cStepperMotor::Method_Move()
 {	if (m_InOut) { digitalWrite(m_pinMotor, HIGH); m_InOut = false; } else { digitalWrite(m_pinMotor, LOW); m_InOut = true; }	/*RUCH*/ }
	 
  
// endof private methods

void cStepperMotor::asmRun()
	{
	if (m_Enable.useEnable && !m_Enable.isEnabled) return;  		// Sprawdzanie dla modułu 
	
    if (m_GoToStep != m_CurrStep) // && (m_GoToStep 
    {
      CheckAndChangeDir();
      
      if ((m_CurrStep > m_Bounds1) && (m_CurrStep < m_Bounds2))  
      {

        this->Method_Move(); // RUCH
          
        if (m_Direction == E_Direction::DirFwd)
        { m_CurrStep++; }
        else if (m_Direction == E_Direction::DirBckwd)
        { m_CurrStep--; }
        m_ErrorCode = E_ErrorCode::Moving;
        
      }
      else if (m_CurrStep == m_Bounds1)
      {
        if (m_GoToStep > m_Bounds1)
        {
          this->Method_Move();	// RUCH
          m_CurrStep++;
          m_ErrorCode = E_ErrorCode::Moving;
        }
        else { m_ErrorCode = E_ErrorCode::BoundsHigh; }		// Jeśli maksimum to BoundsHigh
      }
      else if (m_CurrStep == m_Bounds2)
      {
        if (m_GoToStep < m_Bounds2)
        {
          this->Method_Move(); // RUCH
          m_CurrStep--;
          m_ErrorCode = E_ErrorCode::Moving;
        }
        else { m_ErrorCode = E_ErrorCode::BoundsLow; } 		// Jeśli minimum to BoundsLow
      }
    }
    else if (m_CurrStep == m_GoToStep) { m_ErrorCode = E_ErrorCode::DestReached; }  // jeśli dojechaliśmy to DestReached
  }
  
  bool cStepperMotor::asmCheckDestReached()
  {
	if (m_CurrStep != m_GoToStep) return false;
	else return true;
  }