// cTimedOccurence_Arduino.h
#ifndef cCommandQueue_Arduino_h
#define cCommandQueue_Arduino_h

#include <Arduino.h>


class cCommandQueue
{
	private:
		String  	m_Command;
		int     	m_deleteIndex;

		// Methods
		void			cmd_Get();
		void			cmd_Remove();

	protected:

		virtual void	cmd_Parse() { }
		bool			cmd_CheckExist(String str_cmd);
		bool 			cmd_CheckForInnerValue(String str_startmarker, String str_stopmarker, double& outVal);
		bool 			cmd_CheckForInnerValue(String str_startmarker, String str_stopmarker, long int& outVal);

	public:
					cCommandQueue();

		void		Initialize(); // zamiast konstruktora, niestety musi wejœc do setup {} inaczej nie odpali portu
		void		Initialize(long int baud); 
		void    	cqClearQueue();
		void    	cqRun();
};

#endif