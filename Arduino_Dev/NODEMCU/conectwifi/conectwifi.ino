#include <ESP8266WiFi.h>
const char* ssid = "Nokranger";//name of wifi
const char* password = "anusorn539";//pass of wifi
void setup() {
 Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.println("Conect to ...");
  Serial.println("Nokranger");//show name
  WiFi.begin(ssid,password);//conect to wifi
    while (WiFi.status()!= WL_CONNECTED)//wait for conect
  {
    delay(500);
    Serial.print(".");
    }
      Serial.println();
      Serial.println("WiFi Conected");//conect sucess
    Serial.println("IP Address : ");
    Serial.println(WiFi.localIP());//show serialIP of ESP8266
}
void loop() {}
