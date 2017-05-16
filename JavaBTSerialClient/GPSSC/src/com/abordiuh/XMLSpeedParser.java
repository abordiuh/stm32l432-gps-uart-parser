/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.abordiuh;

import java.io.ByteArrayInputStream;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;

public class XMLSpeedParser {

    private String xmlString;
    private String maxspeed = null;
    private String road_name = null;

    public XMLSpeedParser(String xmlString) {
        this.xmlString = xmlString;
    }

    public void parseXml() {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse(new InputSource(new ByteArrayInputStream(xmlString.getBytes("utf-8"))));

            NodeList osmChildNodes = document.getChildNodes().item(0).getChildNodes();

            for (int i = 0; i < osmChildNodes.getLength(); i++) {
                Node nodeOsm = osmChildNodes.item(i);
                if (nodeOsm.getNodeName() == "way") {
                    NodeList childWayNodes = nodeOsm.getChildNodes();
                    for (int j = 0; j < childWayNodes.getLength(); j++) {
                        Node nodeWay = childWayNodes.item(j);

                        if (nodeWay.getNodeName() == "tag") {
                            NamedNodeMap attributes = nodeWay.getAttributes();
                            Node tagNode_k = attributes.getNamedItem("k");
                            if (tagNode_k.getNodeValue().equals("maxspeed")) {
                                Node maxspeedNode_v = attributes.getNamedItem("v");
                                maxspeed = maxspeedNode_v.getNodeValue();
                            }
                            if (tagNode_k.getNodeValue().equals("name")) {
                                Node nameNode_v = attributes.getNamedItem("v");
                                road_name = nameNode_v.getNodeValue();
                            }
                        }
                    }
                }
            }
            if(maxspeed == null)
            for (int i = 0; i < osmChildNodes.getLength(); i++) {
                Node nodeOsm = osmChildNodes.item(i);
                if (nodeOsm.getNodeName() == "node") {
                    NodeList childWayNodes = nodeOsm.getChildNodes();
                    for (int j = 0; j < childWayNodes.getLength(); j++) {
                        Node nodeWay = childWayNodes.item(j);

                        if (nodeWay.getNodeName() == "tag") {
                            NamedNodeMap attributes = nodeWay.getAttributes();
                            Node tagNode_k = attributes.getNamedItem("k");
                            if (tagNode_k.getNodeValue().equals("maxspeed")) {
                                Node maxspeedNode_v = attributes.getNamedItem("v");
                                maxspeed = maxspeedNode_v.getNodeValue();
                            }

                            road_name = "Traffic sign";
//                            if (tagNode_k.getNodeValue().equals("name")) {
//                                Node nameNode_v = attributes.getNamedItem("v");
//                                road_name = nameNode_v.getNodeValue();
//                            }
                        }
                    }
                }
            }
        } catch (Exception ex) {
            System.out.println("Error:" + ex.toString());
        }
    }

    public String getMaxSpeed() {
        if (maxspeed != null) {
            return maxspeed;
        } else {
            return "0";
        }
    }

    public String getRoadName() {
        if (road_name != null) {
            return road_name;
        } else {
            return "0";
        }
    }

}
