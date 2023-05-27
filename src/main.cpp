#include <Arduino.h>
#include <jled.h>
#include <Bounce2.h>

#define PIN_BUTTON PB0
#define PIN_LED PB1
#define PATTERNS 4

Bounce bounce = Bounce();

auto led = JLed(PIN_LED);

uint8_t ledpattern = 0;

void changeLEDpattern()
{
  switch (ledpattern)
  {
  case 0:
    led.Breathe(2000).LowActive().Forever();
    break;
  case 1:
    led.Blink(500, 500).LowActive().Forever();
    break;
  case 2:
    led.FadeOn(500).DelayAfter(500).FadeOff(500).DelayAfter(500).LowActive().Forever();
    break;
  case 3:
    led.Off().Forever();
    break;
  }

  ledpattern++;
  if (ledpattern >= PATTERNS)
  {
    ledpattern = 0;
  }
}

void setup()
{
  // BOUNCE SETUP

  // SELECT ONE OF THE FOLLOWING :
  // 1) IF YOUR INPUT HAS AN INTERNAL PULL-UP
  bounce.attach(PIN_BUTTON); // USE INTERNAL PULL-UP
  // 2) IF YOUR INPUT USES AN EXTERNAL PULL-UP
  // bounce.attach( BOUNCE_PIN, INPUT ); // USE EXTERNAL PULL-UP

  // DEBOUNCE INTERVAL IN MILLISECONDS
  bounce.interval(5); // interval in ms

  // Start first LED pattern
  changeLEDpattern();
}

void loop()
{
  // JLED UPDATE
  led.Update();

  // BOUNCE UPDATE
  bounce.update();

  if (bounce.changed())
  {
    // THE STATE OF THE INPUT CHANGED
    // GET THE STATE
    int deboucedInput = bounce.read();
    // IF THE CHANGED VALUE IS LOW
    if (deboucedInput == HIGH)
    {
      changeLEDpattern();
    }
  }
}
