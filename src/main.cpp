//送信側にするときは#define SENDにし、#define RECEIVEをコメントアウトする。
//受信側にするときは#define RECEIVEにし、#define SENDをコメントアウトする。



//#define SEND
#define RECEIVE
#include <mbed.h>
#include <SerialSend.h>
#include <SerialReceive.h>
#define DATA_LEN 5
#define BAUD 115200

#ifdef SEND
SerialSend send(p13, p14, DATA_LEN, BAUD);
#endif

#ifdef RECEIVE
SerialReceive receive(p13, p14, DATA_LEN, BAUD);
#endif

Timer t;
DigitalOut led_1(LED1);
DigitalOut led_2(LED2);
Serial pc(USBTX, USBRX);

unsigned char* data = new unsigned char[DATA_LEN];
int main() {
  while(1) {
    t.start();
    #ifdef SEND
    data[0] = 0;
    data[1] = 11;
    data[2] = 4;
    data[3] = 5;
    data[4] = 14;
    send.sendData(data);
    while(t.read_ms() < 50);
    t.stop();
    t.reset();
    #endif

    #ifdef RECEIVE
    data = receive.receiveData();
    int data_1, data_2, data_3, data_4;
    data_1 = static_cast<int>(data[1]);
    data_2 = static_cast<int>(data[2]);
    data_3 = static_cast<int>(data[3]);
    data_4 = static_cast<int>(data[4]);
    if(receive.readable()){
      led_1 = 1;
      pc.printf("%d%d%d%d\r\n", data_1, data_2, data_3, data_4);
    } else {
      led_1 = 0;
    }
    while(t.read_us() < 500);
    t.stop();
    t.reset();
    #endif
  }
}
