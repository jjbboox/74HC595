#include <arduino.h>
#include <dev_74hc595.h>

static const uint16_t sda_pin = 0;
static const uint16_t sck_pin = 2;
static const uint16_t push_pin = 5;
static const uint16_t en_pin = 12;

typedef struct {
    uint8_t seg;
    uint8_t dig;
} NixieTubeCtrl;

void setup() {
    Serial.begin(115200);
    // 定义一个以uint16_t为数据单位的595对象
    Dev74HC595<uint16_t> hc595(sda_pin, sck_pin, push_pin, en_pin);

    Serial.println("设备初始化完毕");
    // 定义一个用于发送的数组
    uint16_t data[2] = {0xff00, 0xf0f0};
    // 发送整个数组到74hc595
    Serial.println("开始发送数组到595");
    hc595.send(data, 2);
    uint16_t a = 0x2345;
    // // 发送1个数据到74hc595
    Serial.println("发送单个整形16位数据到595");
    hc595.send(&a);
    uint16_t b = 0x0045;
    hc595 = b + a;
    hc595 << a << b;

    // Dev74HC595<NixieTubeCtrl> hc595_1(sda_pin, sck_pin, push_pin, en_pin);
    // NixieTubeCtrl ntc = {0xff, 0xfe};

    // // 动态扫描
    // for(int i = 0; i < 8; i++) {
    //     hc595_1 << ntc;
    //     ntc.dig <<= 1;
    //     delay(10);
    // }
}

void loop() {

}