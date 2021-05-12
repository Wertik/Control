#include "HostedServer.h"

#include <map>
#include <iterator>
#include <iostream>
#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "WiFiClient.h"
#include "ESP8266WebServer.h"

HostedServer::HostedServer(int port) : _port(port), _server(WiFiServer(port)) {
}

void HostedServer::connect(const char* ssid, const char* pass) {

    Serial.println();
    Serial.print("server | Connecting to ");
    Serial.print(ssid);
    Serial.print("...");

    // Wifi explicit STA mode the ESP would still create an AP with left over data from memory.
    // WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        attempts += 1;

        if (attempts > 25) {
            Serial.println("Failed to connect to " + String(ssid) + ", expect errors. Status: " + String(WiFi.status()));
            return;
        }
    }

    Serial.println();
    Serial.println("Connected to the network successfully.");

    this->_server.begin();

    attempts = 0;
    while (this->_server.status() != LISTEN) {
        delay(500);
        attempts += 1;

        /* wl_tcp_state
            CLOSED      = 0,
            LISTEN      = 1,
            SYN_SENT    = 2,
            SYN_RCVD    = 3,
            ESTABLISHED = 4,
            FIN_WAIT_1  = 5,
            FIN_WAIT_2  = 6,
            CLOSE_WAIT  = 7,
            CLOSING     = 8,
            LAST_ACK    = 9,
            TIME_WAIT   = 10
        */
        if (attempts > 25) {
            Serial.println("Failed to setup a server. Status: " + String(this->_server.status()));
            return;
        }
    }

    Serial.print("server | Local IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("server | MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("server | Mode: ");
    Serial.println(WiFi.mode(WIFI_STA));
    Serial.println("server | Server ready.");
}

bool HostedServer::attemptConnectClient() {

    if (this->_connected) {
        return false;
    }

    WiFiClient client = this->_server.available();

    if (client && client.connected()) {
        this->_connectedClient = client;
        this->_connected = true;
        Serial.println("server | >> Client " + this->_connectedClient.remoteIP().toString() + " connected.");
        return true;
    }

    return false;
}

bool HostedServer::attemptTerminateClient() {
    if (this->_connectedClient == NULL || !this->_connectedClient.connected()) {
        this->_connected = false;
        Serial.println("server | << Client disconnected.");
        return true;
    }

    return false;
}

void HostedServer::loop() {

    // New connections
    if (!this->isConnected()) {
        this->attemptConnectClient();
        return;
    }

    // Terminate if disconnected
    if (this->attemptTerminateClient()) {
        return;
    }
    
    // Note: Replaced while loop with this to not hang the process.
    while (this->_connectedClient.available()) {
        char c = this->_connectedClient.read();

        if (c == '\n') {
            if (this->_newLine) {
                this->_newLine = false;

                Serial.println("server | Received data: " + this->_data);

                // End of data pool, do some shit.
                this->_connectedClient.println(process(this->_data)); // Process into commands
                this->_data = ""; // reset data
                break;        
            } else {
                this->_newLine = true;
            }
        } else if (c != '\r') {
            this->_data += c;
            this->_newLine = false;
        }
    }
}

// Process received data
String HostedServer::process(String data) {

    auto itr = this->_commands.begin();

    for (itr = this->_commands.begin(); itr != this->_commands.end(); ++itr) {
        if (data.startsWith(itr->first)) {
            Serial.println("cmd parser | Executing command: " + itr->first);
            data.replace(itr->first + ";", "");

            String response = (itr->second)(data);
            Serial.println("cmd parser | Response: " + response);
            return response;
        }
    }

    Serial.println("cmd parser | Invalid command: " + data);
    return "400;Invalid command.";
}

void HostedServer::addCommand(String name, CommandFunction commandFunction) {
    this->_commands.emplace(name, commandFunction);
    Serial.println("cmd parser | Added command " + name);
}

bool HostedServer::isConnected() {
    return this->_connected;
}

WiFiClient HostedServer::connectedClient() {
    return this->_connectedClient;
}

WiFiServer HostedServer::server() {
    return this->_server;
}

int HostedServer::getPort() {
    return this->_port;
}