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
4. Some resources suggested using a 370uF to 1000uF capacitor between Vcc and Gnd pins of the module to avoid power issues.

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
* 3.4v to 4.4v (According to the Data Sheet)  
  * Recomended: 4.0v to 4.2v 
* According to some sources it doesn't work with 3.3v supply. (Not tested in this project)  
* In this project 4.0v to 4.2v input power supply was used.  
* According to the data sheet the modules current cunsumption could be high as 2A when it transmit (Transmit Bursts).  
