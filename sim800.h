
#ifndef _SIM800_h
#define _SIM800_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Sim800
{
 private:
	 char serialData[30];
	 char phNum[11];
	 char serReadVal;
	 boolean _ssrDataArrived = 0;
	 boolean _ssrRequestFlag = 0;

 public:
	 Sim800(int tempValue);

	 String sendSsr(String inStr);
	 void sendSMS(String inStrng, String phnNo);
	 void serialEcho();
	 void getCallerNum();
	 String deleteAllSMS();
	 String sendSsrAscii(String inStr);
	 void serialEchoAscii();
	 void textModeOn();
	 String readRecord();
	 void ringPin(boolean inPinVal = 1);
	
	 String readSsr(uint16_t inDelay = 100);
	 String readSMS(String inStr);
	 boolean atReturns1(); 
	 String getNumfrmRing(String inStr);
	 
};

//extern Sim800 Sim800;

#endif

