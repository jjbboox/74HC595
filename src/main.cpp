#include <arduino.h>
#include <drv_74hc595.h>

static const uint16_t sda_pin = 10;
static const uint16_t sck_pin = 11;
static const uint16_t push_pin = 12;
static const uint16_t en_pin = 13;

void setup() {
    // 定义一个以uint16_t为数据单位的595对象
    Drv74HC595<uint16_t> hc595(sda_pin, sck_pin, push_pin, en_pin);
    // 定义一个用于发送的数组
    uint16_t data[2] = {0xff00, 0xf0f0};
    // 发送整个数组到74hc595
    hc595.send(data, 2);
    uint16_t a = 0x2345;
    // 发送1个数据到74hc595
    hc595.send(&a);
}

void loop() {

}