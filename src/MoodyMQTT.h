#ifndef MoodyMQTT_h
#define MoodyMQTT_h

#define MQTT_MAX_PACKET_SIZE 256
#define MQTT_KEEPALIVE       60
#define MQTT_SOCKET_TIMEOUT  60


#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
 

#define MAX_NUM_SCENARIOS 15
#define MQTT_PORT         1883
#define GREET_PUB_TOPIC   "moody/gateway/greeting/"
#define GREET_SUB_TOPIC   "moody/node/greeting"
#define ACTUATOR_TOPIC    "moody/node/data/"
#define SENSOR_TOPIC      "moody/gateway/data/"
#define SENSOR            0
#define ACTUATOR          1

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
void callback(char* topic, uint8_t* payload, unsigned int length);

class MoodyNode
{
    protected:
        MoodyNode(NodeData *data, int room);
        static MoodyNode*  instance;
        WiFiClient         wifiClient;
        PubSubClient       client;
        NodeData*          nodeInfo;
        char               greetMessage[256];
        bool               started;   
        int                room;

    public:
        static MoodyNode*  getInstance();
        void               begin(const char* ssid, const char* pass, const char* brokeraddr);
        void               greet();
        void               loop();
};

class MoodySensor : public MoodyNode
{
    protected:
        MoodySensor* init(NodeData* data, int room);
    public:
        MoodySensor(NodeData *data, int room);
        void send(int payload);
};

class MoodyActuator : public MoodyNode
{
    protected:
        void callback(char *topic, byte *payload, unsigned int length);
    public:
        MoodyActuator(NodeData *data, int room);
};

void moodyCallback(char *topic, byte *payload, unsigned int length);


#endif