// Klasa StepperMotor jest klas� przystosowan� do zliczania obecnej pozycji silnika krokowego i wykonywania kolejnych krok�w.
//Transmisja odbywa si� na zasadzie podania kierunku ruchu(LOW/HIGH) po kt�rego zadeklarowaniu mo�liwy staje si� ruch silnika
//(ponownie LOW/HIGH naprzemiennie celem poruszania). Klasa zosta�a przystosowana do korzystania z wewn�trznego timera co umo-
//�liwia wstawienie metody Run w funkcji timera i ruch z odpowiedni� cz�stotliwo�ci�.

// cStepperMotor_Arduino.h
#ifndef cStepperMotor_Arduino_h
#define cStepperMotor_Arduino_h

class cStepperMotor
{
public:

	enum E_ErrorCode : int
    {
	  NoErrors 		= 0,			   // brak bledu
      DestReached 	= 1,               // osi�gni�to punkt docelowy
	  MoveError		= 2,			   // jaki� b��d ruchu! SPRAWDZI� JAKI
      BoundsHigh	= 3,               // osi�gni�to dodatni kra�cowy punkt ruchu
      BoundsLow		= 4,               // osi�gni�to ujemny kra�cowy punkt ruchu
	  ErrorInput	= 5,			   // b��d wprowadzania warto�ci zmiennych w jakiej� funkcji
	};

	enum E_Direction : int
	{
		DirBckwd	= -1,				// set direction to backward
		DirStop		= 0,				// set no direction
		DirFwd		= 1,				// set direction to forward
	};
	
private:

	bool		m_InOut;
	bool		m_InvertMovement;
	long		m_Bounds1; // bound1 = minimalny zakres wartosci krokowej, bound2 maksymalny zakres
	long		m_Bounds2;
	long		m_CurrStep;
	long		m_GoToStep;
	int			m_InnerTimer;
	int			m_pinMotor;
	int			m_PinDir;
	
	E_Direction	m_Direction;
	E_ErrorCode m_ErrorCode;
	
	class cMEnable
	{
		public:
			int		pinEnable;
			bool	useEnable;
			bool	isEnabled;
			bool	vInverted;
	} m_Enable;
	
	// Methods
	void	CheckAndChangeDir();

public:

	// Methods
			cStepperMotor(int PinStep, int PinDir, long StepMin, long StepMax);
	void	asmRun();
	void	asmSetZero();
	void	asmSetDir(bool InvertMovement);
	bool	asmGetDir();
	void	asmGoToZero();
	void	asmGoToMax(); // DOROBI� WARUNKI DLA SPRAWDZENIA CZY WARTOSC NIE JEST bledna
	void	asmGoToMin();
	void	asmSetMin(long Location);
	void	asmSetMax(long Location);
	int		asmGetStep();
	int		asmGetMax();
	int		asmGetMin();
	int		asmGetState();
	void	asmMoveTo(long Location);
	void	asmStopMovement();
	void	asmUseEnabling(int Pin, bool voltageInverted);
	void	asmEndEnabling();
	void	asmMotEnable();
	void	asmMotDisable();
	int		asmGetGoTo() { return m_GoToStep; }
										 
};

#endif