#ifndef _DEV_74HC595_H_
#define _DEV_74HC595_H_
#include <Arduino.h>

template<class T>
class Dev74HC595 {
    public:
        Dev74HC595(const uint16_t _sda, const uint16_t _sck, const uint16_t _push, const uint16_t _en) : sda_pin(_sda), sck_pin(_sck), push_pin(_push), en_pin(_en) {
            pinMode(sda_pin, OUTPUT);
            pinMode(sck_pin, OUTPUT);
            pinMode(push_pin, OUTPUT);
            pinMode(en_pin, OUTPUT);
        };
        void send(T* b, uint16_t len=1) {
            uint32_t andWord = 1;
            andWord <<= (sizeof(T) * 8 - 1);
            
            #ifdef _DEBUG_
                Serial.print("调试信息:");
                for(int i = 0; i < len; i++) {
                    char str[10];
                    sprintf(str, "\t0x%X", (b[i]));
                    Serial.print(str);
                }
                Serial.println();
            #endif

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
        };
        void operator=(const T& t)
        {
            send((T*)&t);
        }
        Dev74HC595& operator<<(const T& t) {
            send((T*)&t);
            return *this;
        }
    private:
        uint16_t    sda_pin;
        uint16_t    sck_pin;
        uint16_t    push_pin;
        uint16_t    en_pin;
};

#endif // _DRV_74HC595_H_
