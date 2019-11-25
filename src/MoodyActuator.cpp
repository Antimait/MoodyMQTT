#include "MoodyMQTT.h"

template <typename T>
MoodyActuator<T>::MoodyActuator(NodeData *dataInfo, int room) : MoodyNode(dataInfo, room){}

template <typename T>
void MoodyActuator<T>::callback(char *topic, byte *payload, unsigned int length)
{
    //payload in json format, to put in this->data and then burn to eeprom
    //if it gets updated
    //DynamicJsonDocument j_payload(80);
    //deserializeJson(j_payload, String(payload));



    //this->client.unsubscribe(GREET_SUB_TOPIC);
    //this->client.setCallback(callback);
    //this->client.subscribe(ACTUATOR_TOPIC);
    
}

template <typename T>
void setActuateRoutine(std::function<void(T command)> actuate){
    //actuate = actuate;
}