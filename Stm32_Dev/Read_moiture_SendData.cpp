#include "mbed.h"
#include <string>
#include <rtos.h>

DigitalOut myled(D7);

Serial pc(D1, D0);
Serial m_HLtx(PA_9, PA_10);

AnalogIn moiture(A0);
AnalogIn vref(A5);

typedef uint32_t message_t;
Queue <message_t, 4> queue;

//Queue <messeage_t, 4> queue;
Thread thread,thread2;
uint8_t start_text = 0x02;
uint8_t number_data = 0x04;
uint8_t end_text = 0x03;
uint16_t mvalue;
float humidity;
bool status=false;
void readSensor(){
    mvalue = moiture.read_u16();
    mvalue = mvalue >> 4;
    humidity = mvalue;
    humidity = (950*humidity)/4096;
 
    
    myled = 1;
    wait(0.25);
    
    pc.printf("START TEXT : %d, NUMBER DATA : %d, ADC DATA : %d, Huimidity DATA :%.2f, END TEXT : %d\n\n",start_text,number_data,mvalue,humidity,end_text);//ปริ้นออกมาทางซีเรียลพอร์ตเป็นค่าที่ได้จากเซ็นเซอร์  
}

void sendData(){

    char data[sizeof(humidity)];
    sprintf(data, "%.2f", humidity);

    m_HLtx.puts(data);
    m_HLtx.puts("\r\n");
    wait(1.0);   
}
    
void thread_1() {
    while (1) {
        if(status == false){
            readSensor();
            status = true;
        }
        Thread::wait(1000);//sleep time  1000ms = 1s
    }
}
void thread_2(){
    while(1){
        if(status == true){
            sendData();
            status = false;
        }
        Thread::wait(1000);
    }
}

int main() {
    m_HLtx.baud(9600);
    //string data;
    //สร้าง thread สำหรับการทำงานของโปรแกรม
    pc.printf("Hello TESA TOP GUN RALLY 2017\n\n");
    
    thread.start(thread_1);
    thread2.start(thread_2);
    
    //loop สุดท้ายไม่ต้องทำอะไร ปล่อยไว้ไม่ให้จบ
    while (1) {
        Thread::wait(1000);
    }
}
