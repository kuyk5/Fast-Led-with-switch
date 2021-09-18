/*  This sketch is a compilation of the FastLED ColorPalette and a button press. 
  There are a bunch of mode options to choose from within the sketch. 
  
  Note: Codebender might not support some parts required by this sketch 
  as the version of FastLED may be out of date. 
  Copy to & upload via Java IDE if you run into this issue.
  
  Have fun!
*/

#include <FastLED.h>
#include "colorutils.h"
#include "colorpalettes.h"

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

//This is where we adjust things to match our unique project:
#define NUM_LEDS    90      // adjust this to the number of LEDs you have: 16 or more
#define LED_TYPE    WS2811 // adjust this to the type of LEDS. This is for Neopixels
#define DATA_PIN    6       // adjust this to the pin you've connected your LEDs to   
#define BRIGHTNESS  255      // 255 is full brightness, 128 is half
#define SATURATION  255     // 0-255, 0 is pure white, 255 is fully saturated color
#define BUTTON_PIN  1      // Connect the button to GND and one of the pins.
#define UPDATES_PER_SECOND 100

#define COLOR_ORDER GRB

#define NUM_MODES 18 //Update this number to the highest number of "cases"

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

uint16_t STEPS = 30;// STEPS set dynamically once we've started up
uint16_t SPEED = 30;// SPEED set dynamically once we've started up

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

int ledMode = 0;

uint8_t       colorLoop = 1;

const TProgmemPalette16 MyColors_p PROGMEM =
{
  CRGB:: DarkBlue,
  CRGB:: HotPink,
  CRGB:: Teal,
  CRGB:: BlueViolet,
 
  CRGB:: DodgerBlue,    
  CRGB:: DeepPink,
  CRGB:: Turquoise,
  CRGB:: Indigo,
 
  CRGB:: DarkBlue,
  CRGB:: HotPink,
  CRGB:: Teal,
  CRGB:: BlueViolet,
 
  CRGB:: DodgerBlue,    
  CRGB:: DeepPink,
  CRGB:: Turquoise,
  CRGB:: Indigo,
};

byte prevKeyState = HIGH;         // button is active low


//------------------SETUP------------------
void setup() {
  delay( 2000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness( BRIGHTNESS );
 
  currentBlending = LINEARBLEND; //all of these will be blended unless I tell them not to be

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

//------------------MAIN LOOP------------------
void loop() {

  byte currKeyState = digitalRead(BUTTON_PIN);

  if ((prevKeyState == LOW) && (currKeyState == HIGH)) {
    shortKeyPress();
  }
  prevKeyState = currKeyState;

  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  switch (ledMode) {

//FastLED has a bunch of built-in "palettes" to choose from:
//RainbowColors_p     is all the colors of the rainbow
//PartyColors_p     is all the colors of the rainbow minus greens
//RainbowStripeColors_p is all the colors of the rainbow divided into stripes
//HeatColors_p      is reds and yellows, white, and black
//LavaColors_p      is more reds and orangey colors
//ForestColors_p    is greens and yellows
//OceanColors_p     is lots of blues and aqua colors
//CloudColors_p     is blues and white
//MyColors_p        is whatever you define above

//The group of colors in a palette are sent through a strip of LEDS in speed and step increments youve chosen
//You can change the SPEED and STEPS to make things look exactly how you want
//SPEED refers to how fast the colors move.  Higher numbers = faster motion
//STEPS refers to how wide the bands of color are. Based on the palette & number of LEDs, some look better at different steps

  case 0:
  {currentPalette = RainbowColors_p;  SPEED = 40;  STEPS = 2;currentBlending = LINEARBLEND;}
  break;
  
  case 1:
  {currentPalette = RainbowColors_p;  SPEED = 40;  STEPS = 300;currentBlending = LINEARBLEND;}
  break;
  
  case 2: 
  { currentPalette = LavaColors_p;    SPEED = 40;   STEPS = 2; currentBlending = LINEARBLEND;} 
  break;
  
 case 3: 
  { currentPalette = LavaColors_p;    SPEED = 40;   STEPS = 300; currentBlending = LINEARBLEND;} 
  break;

  case 4:
  {currentPalette = PartyColors_p;   SPEED = 150;   STEPS = 2; currentBlending = LINEARBLEND;}
  break;
  
  case 5:
  {currentPalette = PartyColors_p;   SPEED = 150;   STEPS = 300; currentBlending = LINEARBLEND;}
  break;

  case 6:
  {currentPalette = MyColors_p;     SPEED = 40;   STEPS = 2; currentBlending = LINEARBLEND;} 
  break;

   case 7:
  {currentPalette = MyColors_p;     SPEED = 40;   STEPS = 300; currentBlending = LINEARBLEND;} 
  break;

  case 8:
  {currentPalette = HeatColors_p;     SPEED = 40;   STEPS = 2; currentBlending = LINEARBLEND;} 
  break;

 case 9:
  {currentPalette = HeatColors_p;     SPEED = 40;   STEPS = 300; currentBlending = LINEARBLEND;} 
  break;
  
  case 10:
  {SetupWatermelonPalette(); SPEED = 40; STEPS = 2; currentBlending = LINEARBLEND;}
  break;
  
 case 11:
  {SetupWatermelonPalette(); SPEED = 40; STEPS = 300; currentBlending = LINEARBLEND;}
  break;
  
  case 12:
  {currentPalette = ForestColors_p;     SPEED = 40;   STEPS = 2; currentBlending = LINEARBLEND;} //
  break;

case 13:
  {currentPalette = ForestColors_p;     SPEED = 40;   STEPS = 300; currentBlending = LINEARBLEND;} //
  break;
  
  case 14:
  {currentPalette = OceanColors_p;    SPEED = 40;   STEPS = 2; currentBlending = LINEARBLEND;} //
  break; 

  case 15:
  {currentPalette = OceanColors_p;    SPEED = 40;   STEPS = 300; currentBlending = LINEARBLEND;} //
  break; 
 
  case 16:
{currentPalette = CloudColors_p;    SPEED = 40;   STEPS = 2; currentBlending = LINEARBLEND;} //
  break; 

    case 17:
{currentPalette = CloudColors_p;    SPEED = 40;   STEPS = 300; currentBlending = LINEARBLEND;} //
  break; 
  
   case 18: 
  {  SetupBlackAndWhiteStripedPalette();    SPEED = 150;   STEPS = 120; currentBlending = LINEARBLEND;} 
  break;
  } 

  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
  FastLED.delay(1000 / SPEED);  
}


void shortKeyPress() {
  ledMode++;
  if (ledMode > NUM_MODES) {
    ledMode=0; 
  }  
}

void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    colorIndex += STEPS;              
  }
}

void SetupNewPalette()
{
    fill_solid( currentPalette, 16, CRGB::Black);
    //  set half of the LEDs to the color selected here
    //  Play with the color, steps, and speed to get different results. 
    currentPalette[0] = CRGB::DodgerBlue;
    currentPalette[1] = CRGB::DodgerBlue;
    currentPalette[2] = CRGB::DodgerBlue;
    currentPalette[3] = CRGB::DodgerBlue;

    currentPalette[8] = CRGB::DodgerBlue;
    currentPalette[9] = CRGB::DodgerBlue;
    currentPalette[10] = CRGB::DodgerBlue;
    currentPalette[11] = CRGB::DodgerBlue;
 
}

void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}
//  This function sets up a palette of purple and green stripes.
//  Play with the color, steps, and speed to get different results. 
void SetupWatermelonPalette()
{
    CRGB Pink = CHSV(HUE_PINK, 255, 255);
    CRGB Green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   Green,  Green,  Green,  Green,
                                   Pink, Pink,  Pink, Pink,
                                   Green,  Green,  Green,  Green,
                                   Pink, Pink,  Pink, Pink );
}
