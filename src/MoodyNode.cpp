#include "MoodyMQTT.h"


MoodyNode::MoodyNode(NodeData *data, int room)
{
    this->wifiClient = WiFiClient();
    this->client = PubSubClient(this->wifiClient);
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

    this->client.setServer(brokeraddr, MQTT_PORT);
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
    delay(2000);
    this->greet();
}


void MoodyNode::greet()
{
    this->client.publish((String(GREET_PUB_TOPIC) + this->room).c_str(), this->greetMessage);
    Serial.println(this->greetMessage);
}

void MoodyNode::keepAlive()
{
    this->client.publish("ka", "1");
}

