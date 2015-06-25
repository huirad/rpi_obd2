rpi_obd2
========
Minimalistic access to OBD2 data with an ELM327 compatible adapter


Connecting to Bluetooth-OBD on my openSUSE laptop
-------------------------------------------------
* Check whether the built-in bluetooth adapter is active or blocked
  * `hciconfig -a` or `hciconfig dev`
  * `sudo rfkill list`
* If it's blocked and/or down: unblock and activate it (order seems to be unimportant)
  * `sudo rfkill unblock bluetooth`
  * `sudo hciconfig hci0 up`
* Search for the bluetooth dongle
  * `hcitool scan`
  * This command reports the MAC address of all found BT devices at 00:0B:0D:84:B3:A0
* Bind the bluetooth donge to a rfcomm device
  * `sudo rfcomm bind 0 00:0B:0D:84:B3:A0`
  * Now the device /dev/rfcomm0 is created
* Try to connect to the device
  * `cat /dev/rfcomm0`
  * `minicom -D /dev/rfcomm0`
  * (call as sudo if you are not member of group dialout)
* TODO: CHECK what's the purpose of 
  * `rfcomm connect 0`
* TODO: CHECK how to enter the PIN when there is no GUI (KDE asked me for the PIN ...)

Useful ELM327 commands
----------------------
Note: all commands must be terminated by \r (CR).
Sending just a CR repeats the last command?!

AT commands
* `ATZ` Reset (`ATD` seems to be a synonym)
  * My OBD dongle will send a version string as response.
* `ATDP` Display used protocol (e.g. CAN)
  * Bus connection must be initialized first, e.g. by sending `0100`
* `ATE0` Disable character echo (default: `ATE1`: character echo on)
* `ATL0` Disable sending LF after CR (default: `ATL1`: LF is sent after CR)
* `ATS0` Disable sending spaces between hex characters (default: `ATS1`: spaces are sent between hex characters)
  * This command is not supported by my OBD dongle (apparently only a cheap ELM327 clone)

OBD2 data access: 
The first command sent after power up will initialize the bus connection
and may take longer.
The general command format is <SID> <PID> where 
* SID is the Service ID (in our case always 01) and 
* PID is the Parameter ID (identifying the parameter to read out)

All commands and responses are coded as 2-digit hex numbers without prefix.
The response format is <SID | 0x04> <PID> <result bytes depending on PID>

The following commands may be useful 
(see also https://en.wikipedia.org/wiki/OBD-II_PIDs)
* '0100` List supported PIDs in range 01..1F
  * returns 4 bytes as bitmask
* `0104' Engine load
  * returns 1 byte (A): LOAD_PCT[%] = A*100/255
* `010C` Engine RPM 
  * returns 2 bytes (A,B): RPM [1/min] = ((A*256)+B)/4
* `010D` Vehicle Speed
  * returns 1 byte (A): VSS [km/h] = A
* `0110` Mass Air Flow
  * returns 2 bytes (A,B): MAF [g/s] = ((A*256)+B) / 100
  * not availble on my car
* `011F` Run time since engine start
  * returns 2 bytes (A,B): RUNTIM [s] = (A*256)+B
* `0146` Ambient air temperature
  * returns 1 byte (A): AAT[°C] =  A-40
 



References
----------
* [rfkill](http://linux.die.net/man/1/rfkill)
* [rfkill- ubuntuusers](https://wiki.ubuntuusers.de/rfkill)
* [SDB:ELM327_based_ODB2_scan_tool](https://en.opensuse.org/SDB:ELM327_based_ODB2_scan_tool)

?? https://www.modmypi.com/blog/installing-the-raspberry-pi-nano-bluetooth-dongle

