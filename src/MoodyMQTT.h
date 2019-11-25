#ifndef MoodyMQTT_h
#define MoodyMQTT_h

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
 

#define MAX_NUM_SCENARIOS 15
#define MQTT_PORT 1883
#define GREET_PUB_TOPIC "moody/gateway/greeting/"
#define GREET_SUB_TOPIC "moody/node/greeting"
#define ACTUATOR_TOPIC  "moody/node/data/"
#define SENSOR_TOPIC    "moody/gateway/data/"

// Helper structs for data keeping

struct nodedata {
    const char* type;
    const char* group;
    const char* datatypes;
};

template <typename T>
struct data
{   
    uint8_t n_scenario;
    T actTable[MAX_NUM_SCENARIOS];
};

template <typename T>
using ActuatorData = data<T>;
using NodeData = nodedata;


// Classes definitions from here on

class MoodyNode
{
    protected:
        WiFiClient   wifiClient;
        PubSubClient client;
        NodeData*    nodeInfo;
        char         greetMessage[256];
        bool         started;   
        int          room;
 
    public:
        MoodyNode(NodeData *data, int room);
        void begin(const char* ssid, const char* pass, const char* brokeraddr);
        void greet();
        void keepAlive();
};

class MoodySensor : public MoodyNode
{
    public:
        MoodySensor(NodeData *data, int room);
        void send(int payload);
    
};

template <typename T>
class MoodyActuator : public MoodyNode
{
    private:
        std::function<void(T command)> actuate;
        void callback(char *topic, byte *payload, unsigned int length);

    public:
        MoodyActuator(NodeData *data, int room);
        void setActuateRoutine(std::function<void(T command)> actuate);
};

#endif