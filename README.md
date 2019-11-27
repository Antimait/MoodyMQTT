<h3>MoodyMQTT by Antima</h3>

An implementation of the Moody Sensor and Actuator schemes on the ESP8266 platform using MQTT as the application level protocol for communicating with the gateway.

You can use MoofyMQTT.h if you're working on your ESP trough the NodeMCU platform on the Arduino IDE; to install the library, clone the repository and zip it or click download zip from the upper right corner of the github page, then add it to your environment from the Sketch menu by clicking Sketch -> Include Library -> Add -> .ZIP Library... and selecting the zip file you just downloaded. 

![howto](http://moody.antima.it/static/zip.png)


Note that MoodyMQTT.h has the following non native libraries as dependencies: ESP8266WiFi.h, PubSubClient.h, ArduinoJson.h. You will have to install them either by adding their zip libraries or searching them using the Manage Libraries tool before you start working on your node (remembering to add the Esp mirror to the additional board manager section).

After you include the library, you're good to go and you can start programming your own sensor/actuator node powered by Esp&MQTT: let us know what you're doing by writing to us through the contact form on the website or via email, to share your works and to help us improve!