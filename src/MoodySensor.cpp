#include "MoodyMQTT.h"

#define NODE_TYPE "sensor"

MoodySensor::MoodySensor(NodeData *data, int room) : MoodyNode(data, room) {};

void MoodySensor::send(int payload)
{
    if(!this->started){
        Serial.println("An error occurred, you must call begin before calling send!");
        return;
    }

    DynamicJsonDocument json_p(256);
    json_p["action"] = "data";
    json_p["data"] = payload;
    json_p["data_type"] = this->nodeInfo->group;

    char data[256];
    serializeJson(json_p, data);
    if(!this->client.publish((String(SENSOR_TOPIC) + this->room).c_str(), data)) {
        Serial.println("There's some problem with the publishing.");
    }
    Serial.println(data);
}