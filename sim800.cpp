
#include "sim800.h"
#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(8, 9); // rx, tx

Sim800::Sim800(int baudVal)
{
	gsmSerial.begin(baudVal);
	
}

void Sim800::getCallerNum()
{

}

void Sim800::serialEcho()
{
	if (Serial.available() > 0)
	{
		int8_t serInc = 0;
		while (Serial.available() > 0)
		{
			serialData[serInc] = char(Serial.read());
			Serial.print(serialData[serInc]); // Echo to serial port
			gsmSerial.print(serialData[serInc]); // Sent through Software serial
			serInc++;
		}
		//i = 0;
		Serial.println();
		gsmSerial.println();
	}

	if (gsmSerial.available() > 0)
	{
		while (gsmSerial.available() > 0)
		{
			Serial.print(char(gsmSerial.read()));
		}
	}
}

void Sim800::sendSMS(String inStrng, String phnNo)
{
	Serial.println(sendSsr("AT"));
	delay(100);
	gsmSerial.println("AT+CMGF=1");
	delay(300);
	sendSsr("AT+CMGF?");
	delay(100);
	gsmSerial.print("AT+CMGS=");
	delay(200);
	gsmSerial.write(0x22);// "
	//delay(25);
	gsmSerial.print(phnNo);
	//delay(25);
	gsmSerial.write(0x22);// "
	//delay(25);
	gsmSerial.println();
	//delay(25);
	gsmSerial.print(inStrng); // Message content
	delay(100);
	gsmSerial.println(char(26)); // ctrl+z

	delay(10000);

	if (gsmSerial.available() > 0)
	{
		while (gsmSerial.available() > 0)
		{
			Serial.print(char(gsmSerial.read()));
		}
	}
}
//=========================================================
String Sim800::sendSsr(String inStr)
{
	String outStr;
	int8_t serInc = 0;
	gsmSerial.println(inStr);
	delay(100);
	if (gsmSerial.available() > 0)
	{
		while (gsmSerial.available() > 0)
		{
			outStr += char(gsmSerial.read());
			serInc++;
		}
	}
	return outStr;
}
//==========================================================
String Sim800::deleteAllSMS()
{
	sendSsr("AT");
	delay(100);
	gsmSerial.println("AT+CMGF=1");
	delay(100);
	gsmSerial.print("AT+CMGDA=");
	gsmSerial.write(0x22);// "
	gsmSerial.print("DEL ALL");
	gsmSerial.write(0x22);// "
	gsmSerial.println();
	delay(100);
	String outString;
	if (gsmSerial.available() > 0)
	{
		while (gsmSerial.available() > 0)
		{
			outString += char(gsmSerial.read());
			delay(100);
		}
	}
	return outString;
}

String Sim800::sendSsrAscii(String inStr)
{
	String outStr;
	int8_t serInc = 0;
	gsmSerial.println(inStr);
	delay(100);
	if (gsmSerial.available() > 0)
	{
		while (gsmSerial.available() > 0)
		{
			outStr += gsmSerial.read();
			serInc++;
		}
	}
	return outStr;
}

void Sim800::serialEchoAscii()
{
	if (Serial.available() > 0)
	{
		int8_t serInc = 0;
		while (Serial.available() > 0)
		{
			serialData[serInc] = char(Serial.read());
			//Serial.print(serialData[serInc]); // Echo to serial port
			gsmSerial.print(serialData[serInc]); // Sent through Software serial
			serInc++;
		}
		//i = 0;
		//Serial.println();
		gsmSerial.println();
	}

	if (gsmSerial.available() > 0)
	{
		while (gsmSerial.available() > 0)
		{
			Serial.print(gsmSerial.read());
		}
	}
}

void Sim800::textModeOn()
{
	sendSsr("AT");
	delay(100);
	gsmSerial.println("AT+CMGF=1");
	delay(300);
}

String Sim800::readRecord()
{
	sendSsr("AT");
	delay(100);
	gsmSerial.println("AT+CMGF=1");
	delay(100);

	gsmSerial.print("AT+CMGL=");
	gsmSerial.write(0x22);// "
	gsmSerial.print("ALL");
	gsmSerial.write(0x22);// "
	gsmSerial.println();
	delay(300);

	String outStr;
	if (gsmSerial.available() > 0)
	{
		while (gsmSerial.available() > 0)
		{
			outStr += char(gsmSerial.read());
			
		}
		//Serial.println(outStr);
	}
	return outStr;
}

void Sim800::ringPin(boolean inPinVal = 1)
{
	if(!inPinVal)
	{
		String outStr;
		delay(200);
		if (gsmSerial.available() > 0)
		{
			while (gsmSerial.available() > 0)
			{
				outStr += gsmSerial.read();
			
			}
			//Serial.println(outStr.endsWith(80 104 1310 1310 7975 1310));
			if(outStr.endsWith("Ph\r\n\r\nOK\r\n"))
			{
				Serial.print("str matched");
			}
			else
			{
				Serial.print("str not matched");
			}
		}
	}
}

String Sim800::readSsr(uint16_t inDelay = 100)
{
	String outStr;
	uint16_t serInc;
	if (gsmSerial.available() > 0)
	{
		while (gsmSerial.available() > 0)
		{
			outStr += char(gsmSerial.read());
			serInc++;
			delay(inDelay);
		}
	}
	Serial.println(outStr);
	return outStr;
}

String Sim800::readSMS(String inStr) 
{
	sendSsr("AT");
	delay(100);
	Serial.print("AT+CMGR=");
	Serial.print(inStr);
	delay(100);
	return readSsr();
}

boolean Sim800::atReturns1()
{
	if (sendSsrAscii("AT").substring(11, 15) == "7975")
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

String Sim800::getNumfrmRing(String inStr)
{
	Serial.println(inStr);
	int8_t indxVal = inStr.indexOf("CLIP: ");
	String outString;
	
	for(int8_t i = 0; i < 9; i++)
	{
		phNum[i] = inStr.charAt(indxVal + 7 + i);
		outString += phNum[i];
		//Serial.print(phNum[i] );
	}
	
	Serial.println(outString);

	return outString;
}


//Sim800 Sim800;

