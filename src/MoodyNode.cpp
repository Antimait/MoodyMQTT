#include "MoodyMQTT.h"

MoodyNode* MoodyNode::instance;

MoodyNode::MoodyNode(NodeData *data, int room)
{
    this->wifiClient = WiFiClient();
    this->nodeInfo = data;
    this->started = false;
    this->room = room;
    
    StaticJsonDocument<100> json_p;
    json_p["action"] = "greet";
    json_p["macaddress"] = WiFi.macAddress();
    json_p["type"] = this->nodeInfo->type;
    json_p["group"] = this->nodeInfo->group;
    json_p["datatypes"] = this->nodeInfo->datatypes;

    serializeJson(json_p, this->greetMessage);
    MoodyNode::instance = this;
}

MoodyNode* MoodyNode::getInstance() { 
    return MoodyNode::instance;
}

void MoodyNode::greet()
{
    this->client.publish((String(GREET_PUB_TOPIC) + this->room).c_str(), this->greetMessage);
    Serial.println("Sending greet message");
    Serial.println(this->greetMessage);
}

void callback(char* topic, uint8_t* payload, unsigned int length)
{
    Serial.println("Sub callback called");
    
    Serial.println("Msg arrived with topic: "+String(topic));   
    if(String(topic).equals(GREET_SUB_TOPIC))
    {
        Serial.println("Greet received");
    }
    MoodyNode::getInstance()->greet();
}

void MoodyNode::begin(const char *ssid, const char *pass, const char *brokeraddr)
{   
    if(this->started){
        return;
    }

    WiFi.begin(ssid, pass);
    Serial.println("Trying to connect to "+String(ssid));
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected with IP address: "+WiFi.localIP().toString());

    this->client = PubSubClient(brokeraddr, MQTT_PORT, callback, this->wifiClient);

    while (!this->client.connected())
    {
        Serial.print("Trying to connect to the broker @"+String(brokeraddr));
        String clientId = "MoodyNode-";
        clientId += (WiFi.macAddress()).substring(0, 6);
        if (this->client.connect(clientId.c_str()))
        {
            Serial.println("Connected!");
        }
        else
        {   
            Serial.print("Connection failed, rc=");
            Serial.print(this->client.state());
            Serial.println(" trying again in 5 seconds.");
            delay(5000);
        }
    }
    this->client.subscribe(GREET_SUB_TOPIC);
    this->started = true;
    this->greet();
    this->client.loop();
}


void MoodyNode::loop()
{
    this->client.loop();
}
