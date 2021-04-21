#ifndef HostedServer_h
#define HostedServer_h

#include <map>
#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "WiFiClient.h"
#include "ESP8266WebServer.h"

typedef String (*CommandFunction)(String);
typedef std::map<String, CommandFunction> CommandMap;

class HostedServer {
    private:
        int _port;

        WiFiServer _server;
        WiFiClient _connectedClient;

        bool _connected = false;

        CommandMap _commands;

        String process(String data);

        String _data = "";
        bool _newLine = false;
    public:
        HostedServer(int port);

        void connect(const char* ssid, const char* pass);

        // Returns true if a new connection has been made, false otherwise.
        bool attemptConnectClient();

        // Returns true if the currently connected client has been terminated.
        bool attemptTerminateClient();

        // Getters

        bool isConnected();

        WiFiClient connectedClient();

        WiFiServer server();

        int getPort();

        void loop();

        void addCommand(String name, CommandFunction commandFunction);
};

#endif