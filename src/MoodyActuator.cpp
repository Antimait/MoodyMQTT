#include "MoodyMQTT.h"

MoodyActuator::MoodyActuator(NodeData *dataInfo, int room) : MoodyNode(dataInfo, room){}

void MoodyActuator::callback(char *topic, byte *payload, unsigned int length)
{
    //payload in json format, to put in this->data and then burn to eeprom
    //if it gets updated
    //DynamicJsonDocument j_payload(80);
    //deserializeJson(j_payload, String(payload));



    //this->client.unsubscribe(GREET_SUB_TOPIC);
    //this->client.setCallback(callback);
    //this->client.subscribe(ACTUATOR_TOPIC);
    
}

