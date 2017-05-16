package com.abordiuh;

import gnu.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Enumeration;
import java.io.*;

/**
 * Created by abordiuh3916 on 4/19/2017.
 */
public class SerialSTMCommunicator implements SerialPortEventListener {
    private Enumeration portList;
    private CommPortIdentifier portId;
    private SerialPort serialPort;
    private OutputStream outputStream;
    private InputStream inputStream;
    private String lastMessageFromPort = "";
    private String tempMessageFromPort = "";

    public void closePort() {
        serialPort.close();
        inputStream = null;
        outputStream = null;
    }

    public boolean isPortOpened(){
        return (inputStream != null);
    }

    public boolean connectToPort(String portName, int portSpeed) throws IOException {
        portList = CommPortIdentifier.getPortIdentifiers();
        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                if (portId.getName().equals(portName)) {
                    try {
                        serialPort = (SerialPort) portId.open("STMJAVA", 4000);
                        serialPort.addEventListener(this);

                        serialPort.notifyOnDataAvailable(true);

                        outputStream = serialPort.getOutputStream();
                        inputStream = serialPort.getInputStream();

                        serialPort.setSerialPortParams(portSpeed,
                                SerialPort.DATABITS_8, SerialPort.STOPBITS_1,
                                SerialPort.PARITY_NONE);
                        serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_NONE);
                    } catch (Exception e) {
                        //return false;
                    }
                    System.out.println("Port " + portName + " opened!");
                    return true;
                } else {
                }
            }
        }
        System.out.println("Serial port " + portName + " is not available!");
        return false;
    }

    public void serialEvent(SerialPortEvent event) {
        SerialPort port = (SerialPort) event.getSource();
        if (event.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
            try {
                if (inputStream.available() > 0) {
                    byte[] readBufferArray;
                    int numBytes;
                    numBytes = inputStream.available();
                    readBufferArray = new byte[numBytes];
                    inputStream.read(readBufferArray);
                    String str = new String(readBufferArray, StandardCharsets.UTF_8);
                    if (str.contains("~")) {
                        int index = str.indexOf("\r");
                        String[] arrStr = str.split("\r");
                        lastMessageFromPort = tempMessageFromPort + arrStr[0];
                        tempMessageFromPort = "";
                    } else if (!str.contains("\r"))
                        tempMessageFromPort += str;
                }
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }

    public String getLastMessageFromPort() {
        return lastMessageFromPort;
    }

    public void sendRequest(String messageString) {
        if (outputStream != null)
            try {
                messageString += "\r\n";
                outputStream.write(messageString.getBytes());
                outputStream.flush();
            } catch (IOException e) {
                e.printStackTrace();
            }
    }
}
