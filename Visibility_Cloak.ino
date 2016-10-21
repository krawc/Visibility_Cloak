/***************************************************
* IR Thermometer Sensor-MLX90614
* ****************************************************
* This example is to get the ambient temperature and object temperature by the IIC bus
  
* @author jackli(Jack.li@dfrobot.com)
* @version  V1.0
* @date  2016-2-2
  
* GNU Lesser General Public License.
* See <http://www.gnu.org/licenses/> for details.
* All above must be included in any redistribution
* ****************************************************/

#include <PololuLedStrip.h>
#include <Wire.h>
#include <IR_Thermometer_Sensor_MLX90614.h>

IR_Thermometer_Sensor_MLX90614 MLX90614 = IR_Thermometer_Sensor_MLX90614();



// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 60
rgb_color colors[LED_COUNT];


void setup() {
  Serial.begin(9600);
  MLX90614.begin();  

  // set all LEDs to be off ("black")
  for(byte i = 0; i < LED_COUNT; i++)
  {
    colors[i] = (rgb_color){0, 0, 0};
  }
}

// Converts a color from HSV to RGB.
// h is hue, as a number between 0 and 360.
// s is the saturation, as a number between 0 and 255.
// v is the value, as a number between 0 and 255.
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
  uint8_t f = (h % 60) * 255 / 60;
  uint8_t p = (255 - s) * (uint16_t)v / 255;
  uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t r = 0, g = 0, b = 0;
  switch ((h / 60) % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }
  return (rgb_color) {
    r, g, b
  };
}


void loop() {
 
Serial.print(MLX90614.GetObjectTemp_Celsius()); 
  Serial.println();
  delay(500);

  // Update the colors.
  uint16_t time = millis() >> 2;
  for (uint16_t i = 0; i < LED_COUNT; i++)
  {
    if (MLX90614.GetObjectTemp_Celsius() <=29){
    byte x = (time >> 2) - (i << 3);
    colors[i] = hsvToRgb((uint32_t)x * 359 / 256, 255, 255);
    } else {
    colors[i] = (rgb_color){0, 0, 0};
    }
  }

  // Write the colors to the LED strip.


  ledStrip.write(colors, LED_COUNT);

  

  delay(10);

 
  
}
