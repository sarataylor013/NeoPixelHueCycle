#include <Adafruit_NeoPixel.h>

// C++ code
//

  #define LED_PIN    2
  #define LED_COUNT	 2
  
  Adafruit_NeoPixel strip(LED_COUNT, LED_PIN);


void setup()
{
  strip.begin();
  strip.show();
}

void loop() {

  wheelCycle();

}

void wheelCycle(){
  
  uint8_t count = LED_COUNT;
  
  static uint16_t hue = 80; //60-180
  uint8_t sat = 100; //0-100
  uint8_t light = 50; //0-100
  
  uint32_t color;
  uint8_t i;
 
    while(hue < 140){
      for(i = 0; i < count; i++){
  		color = hsl(hue++, sat, light);
    	strip.setPixelColor(i, color);
    	strip.show();
    	delay(40);
      }
    }
    while(hue > 80){
      for(i = 0; i < count; i++){
  		color = hsl(hue--, sat, light);
    	strip.setPixelColor(i, color);
    	strip.show();
    	delay(40);
      }
    } 	
}

/**
 * Map HSL color space to RGB
 * 
 * Totally borrowed from:
 * http://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/ 
 * 
 * Probably not the most efficient solution, but 
 * it get's the job done.
 */
uint32_t hsl(uint16_t ih, uint8_t is, uint8_t il) {

  float h, s, l, t1, t2, tr, tg, tb;
  uint8_t r, g, b;

  h = (ih % 360) / 360.0;
  s = constrain(is, 0, 100) / 100.0;
  l = constrain(il, 0, 100) / 100.0;

  if ( s == 0 ) { 
    r = g = b = 255 * l;
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
  } 
  
  if ( l < 0.5 ) t1 = l * (1.0 + s);
  else t1 = l + s - l * s;
  
  t2 = 2 * l - t1;
  tr = h + 1/3.0;
  tg = h;
  tb = h - 1/3.0;

  r = hsl_convert(tr, t1, t2);
  g = hsl_convert(tg, t1, t2);
  b = hsl_convert(tb, t1, t2);

  // NeoPixel packed RGB color
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
/**
 * HSL Convert
 * Helper function
 */
uint8_t hsl_convert(float c, float t1, float t2) {

  if ( c < 0 ) c+=1; 
  else if ( c > 1 ) c-=1;

  if ( 6 * c < 1 ) c = t2 + ( t1 - t2 ) * 6 * c;
  else if ( 2 * c < 1 ) c = t1;
  else if ( 3 * c < 2 ) c = t2 + ( t1 - t2 ) * ( 2/3.0 - c ) * 6;
  else c = t2;
  
  return (uint8_t)(c*255); 
}
