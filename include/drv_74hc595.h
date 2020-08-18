#ifndef _DRV_74HC595_H_
#define _DRV_74HC595_H_
#include <Arduino.h>

template<class T>
class Drv74HC595 {
    public:
        Drv74HC595(const uint16_t _sda, const uint16_t _sck, const uint16_t _push, const uint16_t _en) : sda_pin(_sda), sck_pin(_sck), push_pin(_push), en_pin(_en) {
            pinMode(sda_pin, OUTPUT);
            pinMode(sck_pin, OUTPUT);
            pinMode(push_pin, OUTPUT);
            pinMode(en_pin, OUTPUT);
        };
        void send(T* b, uint16_t len=1) {
            uint32_t andWord = 1;
            andWord <<= (sizeof(T) * 8 - 1);
            digitalWrite(push_pin, LOW);
            for(int l = 0; l < len; l++) {
                T t_b = b[l];
                for(int i = 0; i < sizeof(T) * 8; i++) {
                    digitalWrite(sck_pin, LOW);
                    digitalWrite(sda_pin, t_b & andWord);
                    t_b <<= 1;
                    digitalWrite(sck_pin, HIGH);
                }

            }
            digitalWrite(push_pin, HIGH);
        }
    private:
        uint16_t    sda_pin;
        uint16_t    sck_pin;
        uint16_t    push_pin;
        uint16_t    en_pin;
};

#endif // _DRV_74HC595_H_
