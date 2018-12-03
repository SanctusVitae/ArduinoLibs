// Source code
#include "cCommandQueue_Arduino.h"

cCommandQueue::cCommandQueue()
{
	m_Command = "";
	m_deleteIndex = 0;
}

void cCommandQueue::Initialize()
{ 
	Serial.begin(9600);
	Serial.setTimeout(3);
}

void cCommandQueue::Initialize(long int baud)
{ 
	Serial.begin(baud);
	Serial.setTimeout(3);
}

void cCommandQueue::cmd_Get()
{
	m_Command = m_Command + Serial.readString();
}

void cCommandQueue::cmd_Remove()
{
	m_Command.remove(0, m_deleteIndex);
	m_deleteIndex = 0; 
}

bool cCommandQueue::cmd_CheckExist(String str_cmd) // use inside the cmd_Parse function while you check for command, this tells the program how much of a string to delete using cmd_Remove
{
	int cmdIndex = -1;
	cmdIndex = m_Command.indexOf(str_cmd);
	if (cmdIndex >= 0)
	{ m_deleteIndex = cmdIndex+str_cmd.length(); return true; }
	else { return false; }
}

bool cCommandQueue::cmd_CheckForInnerValue(String str_startmarker, String str_stopmarker, long int& outVal)
{
	 int cmdIndex = -1;
	 int supIndex = -1;
	 cmdIndex = m_Command.indexOf(str_stopmarker);
	 supIndex = m_Command.indexOf(str_startmarker);
	 if ((cmdIndex >= 0) && (supIndex >= 0))
	 {
	 // tu skonczyles!
		String shortStr = "";
		shortStr = m_Command.substring(m_Command.indexOf(str_startmarker)+str_startmarker.length(), m_Command.indexOf(str_stopmarker));
		if (shortStr.length() > 0)
		{
			outVal = shortStr.toInt();
		}
		else
		{
			outVal = -777777;	// Error Value
		}
		m_deleteIndex = cmdIndex+str_stopmarker.length();
		return true;
	 }
	 else { return false; }
}
	
bool cCommandQueue::cmd_CheckForInnerValue(String str_startmarker, String str_stopmarker, double& outVal)
{
	 int cmdIndex = -1;
	 int supIndex = -1;
	 cmdIndex = m_Command.indexOf(str_stopmarker);
	 supIndex = m_Command.indexOf(str_startmarker);
	 if ((cmdIndex >= 0) && (supIndex >= 0))
	 {
	 // tu skonczyles!
		String shortStr = "";
		shortStr = m_Command.substring(m_Command.indexOf(str_startmarker)+str_startmarker.length(), m_Command.indexOf(str_stopmarker));
		if (shortStr.length() > 0)
		{
			outVal = shortStr.toFloat();
		}
		else
		{
			outVal = -777777;	// Error Value
		}
		m_deleteIndex = cmdIndex+str_stopmarker.length();
		return true;
	 }
	 else { return false; }
}

void cCommandQueue::cqClearQueue()
{
	m_Command = "";
	m_deleteIndex = 0;
}

void cCommandQueue::cqRun()
{
	if (Serial.available() > 0)
	{
		this->cmd_Get();
		this->cmd_Parse();
		this->cmd_Remove();
	}
}

 /*
if (this.cmd_ExistCheck(""))
{
}
*/
