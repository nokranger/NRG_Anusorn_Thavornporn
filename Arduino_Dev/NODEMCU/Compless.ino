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

//cut string ส่วนที่ไปตัดเอามาเก็บไว้ในตัวแปรนี้
String get_data = "";
String get_data2 = "";
String get_data3 = "";
String get_data4 = "";
String get_data5 = "";


// ThingSpeak Settings
const char* host = "api.thingspeak.com";
const char* api = "GQO6KI2RY61MI0KX";
const int httpPort = 80;
const int updateThingSpeakInterval = 15 * 1000;      // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)

// Variable Setup
long lastConnectionTime = 0; 
boolean lastConnected = false;
int failedCounter = 0;
int value = 0;

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
    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());//show serialIP of ESP8266
}
void updateThingSpeak(String field1,String field2,String field3 ,String field4,String field5){
  if (client.connect(host,httpPort)){         
      String url = "/update?api_key=";
      url += api;
      url += "&field1=";
      url += field1;
      url += "&field2=";
      url += field2;      
      url += "&field3=";
      url += field3;
      url += "&field4=";
      url += field4;
      url += "&field5=";
      url += field5;
      Serial.print("Requesting URL : ");
      Serial.println(url);
    
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" + 
                   "Connection: close\r\n\r\n");
      lastConnectionTime = millis();
      delay(10);
      while(client.available()){
        String line = client.readStringUntil('\r');
        Serial.print(line);
      }    
  }else{
      lastConnectionTime = millis();   
  }
}

void loop() 
{
  while(client.available())//does function while server recall
  {
    String line = client.readStringUntil('\n');// read server ทีละบรรทัด
    get_data = cut_string(line,"city","city id");
    if(get_data != "NULL")
    {
      Serial.print("City ID : ");
      Serial.println(get_data);
      }
     get_data2 = cut_string(line,"city","name");
    if(get_data != "NULL")
    {
      Serial.print("City Name : ");
      Serial.println(get_data2);
      }
    get_data3 = cut_string(line,"speed","speed value");
    if(get_data != "NULL")
    {
      Serial.print("Wind Speed : ");
      Serial.println(get_data3);
      }
    get_data4 = cut_string(line,"humidity","humidity value");
    if(get_data != "NULL")
    {
      Serial.print("Humidity : ");
      Serial.println(get_data4);
      }
      get_data5 = cut_string(line,"temperature","temperature value");
    if(get_data != "NULL")
    {
      Serial.print("Temperature : ");
      Serial.println(get_data5);
      }
    Serial.println(line);//show serial port
    }

    //////////////////////////////////connect client////////////
   if (client.available())
  {
        while ( client.available() > 0 ) {
          char c = client.read();
          Serial.print(c);
       }
  }

  // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected)
  {
    Serial.println("...disconnected");
    Serial.println();

    client.stop();
  }

         ///////update to thingSpeak ///////
   updateThingSpeak(get_data,get_data2,get_data3,get_data4,get_data5);
        Serial.print ("DATA : ");
        Serial.println (get_data);
        Serial.println (get_data2);
        Serial.println (get_data3);
        Serial.println (get_data4);
        Serial.println (get_data5);
        Serial.println("Send Data Comples +++");
        get_data = "";
    lastConnected = client.connected();
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
