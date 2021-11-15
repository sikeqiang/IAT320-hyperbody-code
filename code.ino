#define LIGHT A8
#define PIN A1
#define NUMPIXELS 100
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup()
{
    strip.begin();
    Serial.begin(9600);
    pinMode(LIGHT, INPUT);
}
void loop()
{
    int temp = analogRead(LIGHT);
    Serial.println(temp);

    if (temp < 15) {
        changeColor(NUMPIXELS, strip.Color(104, 188, 247));
    }
    else if(temp<45)
    {
        changeColor(NUMPIXELS, strip.Color(255, 252, 255));
    }
    else if (temp < 65) {
        changeColor(NUMPIXELS, strip.Color(241, 255, 150));
    }
    else if (temp < 90) {
        changeColor(NUMPIXELS, strip.Color(231, 109, 242));
    }
    else if (temp < 115) {
        changeColor(NUMPIXELS, strip.Color(55, 0, 252));
    }
    else if (temp < 140) {
        changeColor(NUMPIXELS, strip.Color(0, 177, 252));
    }
    else if (temp<170) {
        colorWipe(strip.Color(255, 0, 0),10);
    }

    else if (temp<200) {
        rainbowCycle(10);
    }
    else {
        changeColor(NUMPIXELS, strip.Color(104, 188, 247));
    }
    delay(60);
}
void changeColor(int num, uint32_t c)
{
    if (num > strip.numPixels())
    {
        num = strip.numPixels();
    }
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        if (i <= num)
        {
            strip.setPixelColor(i, c);
        }
        else
        {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
    }
    strip.show();
}

void colorWipe(uint32_t c, uint8_t wait)
{
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, c);
        delay(wait);
        strip.show();
        delay(wait);
    }
}

void rainbowCycle(uint8_t wait)
{
    uint16_t i;

    for (i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + millis() / 200) & 255));
        strip.show();
        delay(wait);
    }
}

uint32_t Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
