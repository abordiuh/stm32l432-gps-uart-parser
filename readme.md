# STM32 L432 GPS NMEA Parser

The folder ABordiuh_GPS - contains source code and project of Atollic TrueStudio on C:

  Firmware which receive GGA NMEA format GPS information and SPD
  (speed and name of the road) data from UART (java serial client app is sender),
  parses it and finally sends back parsed NMEA GGA data + displays
  name and speed on a connected LCD display.

****************************************************************************

The folder JavaBTSerialClient - contains source code and project of Intellij 
				IDE Studio on Java:

  Java serial client to STM32L432 UART which communicates through Bluetooth with 
  STM32 L432 mcu and constantly sends NMEA location.
