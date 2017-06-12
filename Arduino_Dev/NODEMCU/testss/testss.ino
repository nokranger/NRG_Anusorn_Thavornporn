#include <ESP8266WiFi.h>
#define SERVER_PORT 80
const char* ssid = "SFBRM";//name of wifi
const char* password = "0846318958";//pass of wifi

const char* server_ip = "api.openweathermap.org";
String city = "bangkok";

String str_get1 = "GET /data/2.5/weather?q=";
String str_get2 = "&mode=xml&units=metric\n\n";
String str_apiId = "&appid=2100e87ca548704c2137ff03cd791158";
String str_host = "Host: api.openweathermap.org\n\n";


WiFiServer server(SERVER_PORT);
WiFiClient client;

unsigned long previousMillis = 0;
const long interval = 10000;

void setup() {
 Serial.begin(115200);
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
void loop() 
{
  while(client.available())//does function while server recall
  {
    String line = client.readStringUntil('\n');// read server ทีละบรรทัด
    String get_data = cut_string(line,"city","city id");
    if(get_data != "NULL")
    {
      Serial.println("City ID");
      Serial.println(get_data);
      }
     String get_data2 = cut_string(line,"city","name");
    if(get_data != "NULL")
    {
      Serial.println("City Name");
      Serial.println(get_data2);
      }
    String get_data3 = cut_string(line,"speed","speed value");
    if(get_data != "NULL")
    {
      Serial.println("Wind Speed");
      Serial.println(get_data3);
      }
    String get_data4 = cut_string(line,"humidity","humidity value");
    if(get_data != "NULL")
    {
      Serial.println("Humidity");
      Serial.println(get_data4);
      }
      String get_data5 = cut_string(line,"temperature","temperature value");
    if(get_data != "NULL")
    {
      Serial.println("Temperature");
      Serial.println(get_data5);
      }
    Serial.println(line);//show serial port
    }
    unsigned long currentMillis = millis();//read time nodemcu start working
    if(currentMillis - previousMillis >= interval)//if time present - past >  interval does (pre = current)
    {
      previousMillis = currentMillis;
      Client_Request();//call dunction client_reques
      }
 }
    void Client_Request()
    {
      Serial.println("Connect TCP Server");
      int cnt=0;
      while(!client.connect(server_ip,SERVER_PORT))// connect to server wait for connected
      {
          Serial.print(".");
          delay(100);
          cnt++;
          if(cnt>50)   //if time conected  > 5sec exit function
          return;
        }
        Serial.println("Success");
        delay(500);
        client.print(str_get1+city+str_apiId+str_get2+str_host);
        Serial.print(str_get1+city+str_apiId+str_get2+str_host);
        delay(100);
      }
      
    String cut_string(String input,String header,String get_string)
    {
      if(input.indexOf(header) != -1){
        int num_get = input.indexOf(get_string);
        if(num_get != -1){
            int start_val = input.indexOf("\"",num_get)+1;
            int stop_val = input.indexOf("\"",start_val);
            return(input.substring(start_val,stop_val));
        }else{
            return("NULL");
        }
      }
      return("NULL");
    }
