# STM32 L432 GPS NMEA Parser

The folder ABordiuh_GPS - contains source code and project of Atollic True
                          Studio on C:

  Firmware which receive GGA NMEA format GPS data and SPD
  (speed and name of the road) data from UART (java serial client app),
  parsing it and finally sending back parsed NMEA GGA data and display
  name and speed on a display.

****************************************************************************

The folder JavaBTSerialClient - contains source code and project of Intellij 
				IDE Studio on Java:

  Software written on java, which appear as serial client to STM32L432 UART
  and communicate through Bluetooth with device (Android + GPS app) which
  constantly sends NMEA location.

*Project done by using Atollic True Studio IDE
