// Klasa StepperMotor jest klas¹ przystosowan¹ do zliczania obecnej pozycji silnika krokowego i wykonywania kolejnych kroków.
//Transmisja odbywa siê na zasadzie podania kierunku ruchu(LOW/HIGH) po którego zadeklarowaniu mo¿liwy staje siê ruch silnika
//(ponownie LOW/HIGH naprzemiennie celem poruszania). Klasa zosta³a przystosowana do korzystania z wewnêtrznego timera co umo-
//¿liwia wstawienie metody Run w funkcji timera i ruch z odpowiedni¹ czêstotliwoœci¹.

// cStepperMotor_Arduino.h
#ifndef cStepperMotor_Arduino_h
#define cStepperMotor_Arduino_h

class cStepperMotor
{
public:

	enum E_ErrorCode : int
    {
	  NoErrors 		= 0,			   // brak bledu
      DestReached 	= 1,               // osi¹gniêto punkt docelowy
	  Moving		= 2,			   // jakiœ b³¹d ruchu! SPRAWDZIÆ JAKI
      BoundsHigh	= 3,               // osi¹gniêto dodatni krañcowy punkt ruchu
      BoundsLow		= 4,               // osi¹gniêto ujemny krañcowy punkt ruchu
	  ErrorInput	= 5,			   // b³¹d wprowadzania wartoœci zmiennych w jakiejœ funkcji
	};
	
	enum E_Direction : int
	{
		DirBckwd	= -1,				// set direction to backward
		DirStop		= 0,				// set no direction
		DirFwd		= 1,				// set direction to forward
	};

private:

	uint8_t		m_DirectionValue;		// accepts LOW/HIGH
	bool		m_InOut;
	bool		m_InvertMovement;		// switch forward between plus and minus values
	long		m_Bounds1; 				// minimalny zakres wartosci krokowej
	long		m_Bounds2;				// bound2 maksymalny zakres
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
	void 	Method_Move();

public:
	// Methods
			cStepperMotor(int PinStep, int PinDir, long StepMin, long StepMax);
	void	asmRun();
	void	asmSetZero();
	void	asmSetDir(bool MinEqualsLow);
	void	asmGoToZero();
	void	asmGoToMax(); // DOROBIÆ WARUNKI DLA SPRAWDZENIA CZY WARTOSC NIE JEST bledna
	void	asmGoToMin();
	void	asmSetMin(long Location);
	void	asmSetMax(long Location);
	long	asmGetStep();
	long	asmGetMax();
	long	asmGetMin();
	int		asmGetState();
	void	asmMoveTo(long Location);
	void	asmStopMovement();
	void	asmUseEnabling(int Pin, bool voltageInverted);
	void	asmEndEnabling();
	void	asmMotEnable();
	void	asmMotDisable();
	int		asmGetGoTo() { return m_GoToStep; }
	bool	asmCheckDestReached();
	
	int		asmDebugError() { return m_ErrorCode; }
};

#endif