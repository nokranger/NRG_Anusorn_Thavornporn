int analogPin1 = A0;
int analogPin2 = A2;
int sensorValueTP = 0;
int sensorValueMC = 0;
char ef;
void setup() {
   // put your setup code here, to run once:
   Serial.begin(9600);
}

void loop(){
   char ef;
    if(Serial.available()>=0){
      ef=Serial.read();
      if(ef=='t'||ef=='T'){
        sensorValueTP = analogRead(analogPin1);
         String T="TP"+String(sensorValueTP);
         Serial.println(T);
      }
      if(ef=='m'||ef=='M'){
        sensorValueMC = analogRead(analogPin2);
        String M="MC"+String(sensorValueMC);
        Serial.println(M);
      }
    }
}

