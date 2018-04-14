#include <FastLED.h>

#define LED_PIN     7
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    8

#define BRIGHTNESS  200

#define FRAMES_PER_SECOND 60

CRGB leds[NUM_LEDS];

long randNumber;
long maxLED;
long randColor;
int saturation;
int intensity;
int dot;
int minDelay; //  lower limit used to increase the delay between led updates the further up the stick you go
int maxDelay; //  upper limit used to increase the delay between led updates the further up the stick you go

void setup() {

  Serial.begin(115200);  
  delay(2000); // sanity delay
  randomSeed(analogRead(0));
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  
}

void loop() {


   
    //Serial.println(maxLED);
    
    // for the first led (base of the candle) we want a little blue in the flame

    //leds[0] = CHSV( random(20,30), random(140,255), random (180,255)); // set a little blue and allow some "heat" to effect the saturation
    leds[0] = CHSV( 32, random8(180,240), random8 (150,200)); // set a little blue and allow some "heat" to effect the saturation
    FastLED.show(); // update display
    
    //randColor = random8 (25,35); // allow color to range from reddish to orange-ish
    // now do the rest of the leds

    
    
    maxLED = random8(3,NUM_LEDS); // this will determine how many leds get turned on for the current cycle.
    intensity = random8(210,255);   // randomize intensity a bit
    for(dot = 1; dot <= maxLED; dot++) // this will make the higher tips seem whiter
    {     
        if (dot == NUM_LEDS-1)// this part changes the saturation of the tip of the flame and makes it appear more white at the tip
        {
          saturation = 200;  // make the tip very white
        }
        else if (dot == NUM_LEDS-2)
        {
          saturation = 220;   // less white
        }  
        else if (dot == NUM_LEDS-3)
        {
          saturation = 240;   // less white
        }  
        else
        {
          saturation = 255;   // not white
        }
          
        
         // format for color is Hue, Saturation, Value (intensity)
          leds[dot] = CHSV( random8 (25,35), saturation, intensity); // light them up
          FastLED.show(); // show them
          //minDelay = 20 + pow(dot,2); // set min delay which increases as you move up the stick
          maxDelay = 30 + pow(dot,2); // set max delay which increases as you move up the stick
          FastLED.delay(random8(10,maxDelay));  // wait a sec
    } 
         
    // delay at peak of flame for a short period
    randNumber = random8(3,maxLED*3);
    FastLED.delay(randNumber);

    
 //********************************************************
 // Now we dim the leds starting towards the bottom and working up. Doing it this way creates the "disconnected" tip of the flame sometimes
 // which adds realism.
 // I randomize which led we start dimming at
 //********************************************************
    
    for(dot = random8(2,NUM_LEDS-3); dot < NUM_LEDS ; dot++) 
    {     
          //leds[dot] = CRGB::Black; // old way -set the leds to black meaning turn them all the way off
          
          leds[dot].nscale8_video( random8(1,128)); // this dims the led.  The number passed sets the percentage of brightness, ie x/256.  Example - Setting value to 192 = 192/256 = 75% of brightness
          FastLED.show(); // update
          //maxDelay = 30 + pow(dot,2); // set max delay which increases as you move up the stick
          FastLED.delay(random8(10,20));  // wait a sec
    }      
    
    
    
}         
          
          
    


