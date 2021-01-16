### sim800l_lib

This library contains selected functions only.   

---
#### The module used in this project:
* Sim800l Red color module.

#### Introduction:

This module requires delicate handling comparing to other Arduino/ Embedded systems modules (Such as: nRF24L01  connected to a 5v power but still worked afterwords also nRF24L01 has tolerance for 5v logic levels). If the module (sim800l) accidently powerd using 5v supply or used 5v logic levels could easily burn the module. If the supply could not provide enough power (Recomended: 2A current) then also module refuses connecting to a network.

---
#### Unstable Issues:
1. Tried power up using TP4056 Li-Ion battery charger module (4.2v/ 2A) on a breadboard, used breadboard jumpers to make connections, the module didn't even turned on.   
2. Tried using power supply based LM2596s (4.2v and rated 3A) on a breadboard connected using jumper cables. Module turned on but refused to connect with a network. Module responded to AT commands but  break transmission occured every 10 - 20 seconds (According to one resource, that because the module tries to connect with the network but the supply power is not sufficient to do so).  
3. Used above LM2596s based power supply directly conneted to the module (not on the breadboard) and  the module worked successfully.
4. Soldered a 1000uF capacitor between 5v and Gnd pins and powered up using TP4056 module on breadboard module worked. However, after connect with with condensor mic (mic only not the module) and 8ohm speaker (without amplifier), the module refused to connect to the network. Added another 1000uF capacitor between power pins (on the breadboard) in order to bring module to the working state.
5. The capacitor has to be placed close as possible to power pins.
---
#### Connections:
| Master Device | Sim800l |
| --- | --- |
|4.2v | Vcc  |
|Gnd | Gnd  |
|Rx | Tx |
|Tx(3.3v) | Rx |  


* According to the data sheet pulling LOW the DTR pin activates the module but in this project the DTR pin wasn't connected to anything.

---
#### Power Supply: 
* 3.4v to 4.4v (According to the Data Sheet) / 2A 
  * Recomended: 4.0v to 4.2v 
* According to some sources it doesn't work with 3.3v supply. (Not tested in this project)  
* In this project 4.0v to 4.2v input power supply was used.  
* According to the data sheet the modules current cunsumption could be high as 2A when it transmit (Transmit Bursts).
* Observed curent consumption while making a call (before answering) can be high as 1.8A.  

---
#### Some useful AT Commands:

> AT+CSPN? => Get network providers name

> AT+CBC => Get battery voltage(supply)
>>Returns: AT+CBC+CBC: 0,81,4054   
>>0 = Charging status (0=not charging, 1=charging, 2=charging has finished)  
>>80 = Charged percentage  
>>4054 = Battery voltage in milli volts.   

> ATD0777123123; => Make a call (Digits are a dummy phone number)

> ATA => Answer an incomming call.

>AT+IPR? => Baud Rate (0: Auto Baud)

> AT+CSQ => Signal quality report.

>ATI => Product name and release information.

> AT+GSV => Product ID info, maufacturer, product name, revision info.

> AT&V => Display current config.

>AT+CMGF=1 => Set SMS format to text

>AT+CLTS=1 Get local timestamp enable
>>AT&W => Save changes
>>Restart the module

>AT+CCLK? => Clock (time)
>>AT+CCLK?+CCLK: "21/01/15,08:44:56+22"

----
#### Audio Input:

1. Condensor mic (not the module) used as the mic input and returned large hum noise at receiver/ callers end.

#### Audio Output:  

* Audio output worked fine with connected 8ohm speaker (without amp)   
  * Audio from other end (caller/ receiver) received successfully.
  * Ring tone worked