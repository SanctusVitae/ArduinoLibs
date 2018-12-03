#include <cCommandQueue_Arduino.h>

// list of included commands
// cmd_CheckExist(string) checks if string exists and parses command
// cmd_CheckForInnerValue(string startmarker, string stopmarker, &double or &long int)
// checks for value between two markers like this MRK1_500_MRK2 and puts it inside &value

class cqProgramMessageQueue : public cCommandQueue
{
    private:
      // add methods to check commands from com port
      void programCommand1()
        {
          if (this->cmd_CheckExist("command1"))
          {
            // the code to execute if command exists
          }
        }
    public:
      // always add the command parsing by using this->methodForCommand
      void cmd_Parse() // parsing clears buffer and executes commands
      {
        this->programCommand1();
      }
}Queue; // you can use the class by simply declaring a variable or skip it and use Queue
        // the class has no variables and it shouldn't have anyway, static usage but on object
        
void setup() {
  Queue.Initialize(57600); // this actually starts a serial port too
  //so it is like Setup.begin(value), necessary to start queue parsing
}

void loop() {
  Queue.cqRun(); // method that executes your parsing command inside it
  // also clears buffer

}

// for sending From arduino To computer use simple Serial.print or whatever you use normally