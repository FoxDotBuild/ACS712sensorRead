#include "ACS712.h" //https://github.com/RobTillaart/ACS712 - More library info - Install via Tools -> Manage Libraries... Within Arduino IDE

#define ADC_PIN A0
#define ADC_EN  14
#define SIMPLE_AVG_SIZE 200

// ACS712 5A  uses 185 mV per A
// ACS712 20A uses 100 mV per A
// ACS712 30A uses  66 mV per A
// ESP 32 example (requires resistors to step down the logic voltage)
 ACS712  ACS(ADC_PIN, 5.0, 4095, 66);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  ACS.autoMidPoint();
  Serial.print("MidPoint: ");
  Serial.print(ACS.getMidPoint());
  Serial.print(". Noise mV: ");
  Serial.println(ACS.getNoisemV());
  enableADC();
  Serial.println("ADC enabled...");
}


void loop()
{
  Serial.print("mA: ");
  
  int readings[SIMPLE_AVG_SIZE];
  for (int i = 0; i < SIMPLE_AVG_SIZE; i++)
  {
    readings[i] = ACS.mA_AC();
  }
  int sum = 0;
  for (int i = 0; i < SIMPLE_AVG_SIZE; i++)
  {
    sum = sum + readings[i];
  }
  Serial.println(sum / SIMPLE_AVG_SIZE);
}

void enableADC()
{ //enables ADC on esp32 board b/c the board is weird like that
  pinMode(ADC_EN, OUTPUT);
  digitalWrite(ADC_EN, HIGH);
}


// -- END OF FILE --
