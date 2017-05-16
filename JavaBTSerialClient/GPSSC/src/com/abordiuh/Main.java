package com.abordiuh;

import java.io.IOException;
import java.text.DecimalFormat;

public class Main{

    private static class StmActivity extends Thread {
        public String incomeString;
        public boolean started = false;

        @Override
        public void run() {
            SerialSTMCommunicator serialSTM = new SerialSTMCommunicator();
            try {
                System.out.println("GPGGA:"+incomeString);
                if (incomeString.length() > 40
                        && (serialSTM.isPortOpened() || serialSTM.connectToPort("COM8", 9600))) {

                    String nmea_gpgga[] = incomeString.split(",");
                    HttpUrlRequest httpUrlRequest = new HttpUrlRequest();
                    float lat = (int)(Float.parseFloat(nmea_gpgga[2]) / 100) + (Float.parseFloat(nmea_gpgga[2])
                            - (((int)(Float.parseFloat(nmea_gpgga[2]) / 100)) * 100))/60;
                    float lon = (int)(Float.parseFloat(nmea_gpgga[4]) / 100) + (Float.parseFloat(nmea_gpgga[4])
                            - (((int)(Float.parseFloat(nmea_gpgga[4]) / 100)) * 100))/60;

                    String latitude = (nmea_gpgga[3].contains("N")) ? String.valueOf(lat) : "-" + String.valueOf(lat);
                    String longtitude = (nmea_gpgga[5].contains("E")) ? String.valueOf(lon) : "-" + String.valueOf(lon);

                    double boxDistanceLat = 0.005;
                    double boxDistanceLong = 0.005;

                    // 5.6283473,50.5348043,5.6285261,50.534884

                    DecimalFormat df = new DecimalFormat("##.#######");

                    String latitudeNorth = df.format(Double.parseDouble(latitude) + boxDistanceLat);
                    String latitudeSouth = df.format(Double.parseDouble(latitude) - boxDistanceLat);
                    String longtitudeWest = df.format(Double.parseDouble(longtitude) + boxDistanceLong);
                    String longtitudeEast = df.format(Double.parseDouble(longtitude) - boxDistanceLong);
                    String url = "http://www.overpass-api.de/api/xapi?*[maxspeed=*][bbox=" + longtitudeWest + "," + latitudeSouth + "," + longtitudeEast + "," + latitudeNorth + "]";

                    String xmlStrAnswer = httpUrlRequest.sendGet(url);

                    System.out.println("Parsed XML:");

                    XMLSpeedParser xMLSpeedParser = new XMLSpeedParser(xmlStrAnswer);
                    xMLSpeedParser.parseXml();
                    System.out.println("Speed is: " + xMLSpeedParser.getMaxSpeed() + " Name: " + xMLSpeedParser.getRoadName());

                    currentThread().sleep(100);
                    serialSTM.sendRequest(incomeString);
                    String incomeSTM = serialSTM.getLastMessageFromPort();
                    currentThread().sleep(100);
                    while (!incomeSTM.contains("~")) {
                        incomeSTM = serialSTM.getLastMessageFromPort();
                    }
                    System.out.println("From STM: " + incomeSTM);
                    serialSTM.sendRequest("$SPD," + xMLSpeedParser.getRoadName() + "," + xMLSpeedParser.getMaxSpeed() + ",~\r\n");
                }
            } catch (IOException e) {
                e.printStackTrace();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        StmActivity stmActivity = new StmActivity();
        SerialGPSCommunicator serialGPS = new SerialGPSCommunicator();
        try {
            if (serialGPS.connectToPort("COM6", 9600)) {
                while (true) {
                    String income = serialGPS.getLastMessageFromPort();
                    while (!income.contains("GPGGA")) {
                        income = serialGPS.getLastMessageFromPort();
                    }
//                income = "$GPGGA,123519,4323.996,N,08024.180,E,1,08,0.9,545.4,M,46.9,M,,*47~";
                    if (!stmActivity.isAlive()) {
                        stmActivity.incomeString = income;
                        stmActivity.run();
                    }
                    }
                }
            } catch (IOException e1) {
            e1.printStackTrace();
        }
        //launch(args);
    }
}
