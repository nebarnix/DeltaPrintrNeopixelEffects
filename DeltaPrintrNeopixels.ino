// Jasper Nance 2016
// Made for deltaprintr neopixel effects. 
// Based on buttoncycler

#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   2    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNTL 37
#define PIXEL_COUNTR 37
#define PIXEL_COUNTB 36

#define CYCLETIME_MS 30000
//#define CYCLETIME_MS 3000
// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNTL+PIXEL_COUNTR+PIXEL_COUNTB, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

unsigned char masterR[PIXEL_COUNTL];
unsigned char masterG[PIXEL_COUNTL];
unsigned char masterB[PIXEL_COUNTL];

bool oldState = HIGH;
int mode;
unsigned int mSecTime;

void setup() {
  memset(masterR, 0, sizeof(masterR));
  memset(masterG, 0, sizeof(masterG));
  memset(masterB, 0, sizeof(masterB));
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  mode = 0;
  mSecTime = 0;
  setMaster(PIXEL_COUNTL,255,255,255);
  strip.show();
}

void loop() {
  
  updateMaster(PIXEL_COUNTL, mode);
  outputMaster();
  strip.show();
  
  if(mSecTime > CYCLETIME_MS)
     { 
     mSecTime = 0;
     mode++;
     if(mode == 0) //set transition effect
        {
        setMaster(PIXEL_COUNTL,255,255,255);
        outputMaster();
        strip.show();
        delay(50);
        }
     else if(mode == 1)
        {
        setMaster(PIXEL_COUNTL,200,128,255);
        outputMaster();
        strip.show();
        delay(50);
        }
     else if(mode == 2)
        {
        setMaster(PIXEL_COUNTL,200,255,255);
        outputMaster();
        strip.show();
        delay(50);
        }
     else if(mode == 3)
        {
        //setMaster(PIXEL_COUNTL,200,255,255);
        //outputMaster();
        //strip.show();
        //delay(100);
        }
     else
        mode = 0;
     }
}

void updateMaster(char numPixels, char mode)
{
  switch(mode){
    case 0: Cylon1(PIXEL_COUNTL,255,255,255, 1.2, 1.3, 2);    // Black/off
            delay(30);
            mSecTime = mSecTime + 30;
            break;
     case 1: Cylon1(PIXEL_COUNTL,200,128,255, 1.2, 1.75, 1.25);    // Black/off
            delay(10);
            mSecTime = mSecTime + 10;
            break;
      case 2: Cylon2(PIXEL_COUNTL,200,255,255, 3, 1.8, 1.75);    // Black/off
            delay(20);
            mSecTime = mSecTime + 20;
            break;
       case 3: Rainbow(PIXEL_COUNTL);
            delay(20);
            mSecTime = mSecTime + 20;
            break;
  }
}

void outputMaster()
{
// We must use Master for left, 1, 
// We must use Master inverted top to bottom for right, 2
// We must use Master-1 for back,3
for( int i = 0; i < PIXEL_COUNTL;  i++ )
   {
   strip.setPixelColor(i, masterR[i],masterG[i],masterB[i]);
   //strip.setPixelColor(i, 0,0,255);
   }
for( int i = 0; i < PIXEL_COUNTR;  i++ )
   {
   strip.setPixelColor((PIXEL_COUNTR-i)+PIXEL_COUNTL-1, masterR[i],masterG[i],masterB[i]);
   //strip.setPixelColor((PIXEL_COUNTR-i)+PIXEL_COUNTL, 0,255,0);
   }
   
for( int i = 0; i < PIXEL_COUNTB;  i++ )
   {
   strip.setPixelColor(PIXEL_COUNTR+PIXEL_COUNTL+i, masterR[i],masterG[i],masterB[i]);
   //strip.setPixelColor(PIXEL_COUNTR+PIXEL_COUNTL+i, 255,0,0);
   }
}

void Cylon1(unsigned char numPixels, unsigned char R,unsigned char G, unsigned char B, float Kr, float Kg, float Kb)
{
static char eyePos=0, sign=1; 
eyePos = eyePos + sign;
   
if(eyePos >= numPixels || eyePos < 0)
   sign = sign * -1;  
      
for( int i = 0; i < numPixels;  i++ )
   {
   masterR[i] = masterR[i] / Kr;
   masterG[i] = masterG[i] / Kg;
   masterB[i] = masterB[i] / Kb;
      
   if(i == eyePos)
      {
      masterR[i] = R;
      masterG[i] = G;
      masterB[i] = B;
      }
   }
}

void Cylon2(unsigned char numPixels, unsigned char R,unsigned char G, unsigned char B, float Kr, float Kg, float Kb)
{
static char eyePos=0, sign=1; 
eyePos = eyePos + sign;
   
if(eyePos >= numPixels || eyePos < 0)
   sign = sign * -1;  
      
for( int i = 0; i < numPixels;  i++ )
   {
   masterR[i] = masterR[i] / Kr;
   masterG[i] = masterG[i] / Kg;
   masterB[i] = masterB[i] / Kb;
      
   if(i == eyePos || eyePos == (numPixels-1-i))
      {
      masterR[i] = R;
      masterG[i] = G;
      masterB[i] = B;
      }
   }
}

void Rainbow(int numPixels)
{
  static int j=0;
  unsigned char WheelPos;
    for(unsigned char i=0; i<numPixels; i++) {
       WheelPos = i+j;
       WheelPos = 255 - WheelPos;
       if(WheelPos < 85) 
          {
          masterR[i]=255 - WheelPos * 3;
          masterG[i]=0;
          masterB[i]=WheelPos * 3;
          }
       else if(WheelPos < 170)
          {
          WheelPos -= 85;
          masterR[i]=0;
          masterG[i]=WheelPos * 3;
          masterB[i]= 255 - WheelPos * 3;
          }
       else
         {
          WheelPos -= 170;
          masterR[i]=WheelPos * 3;
          masterG[i]= 255 - WheelPos * 3;
          masterB[i]=0;
         }
    }
    j++;
}

void setMaster(int numPixels,unsigned char Rin,unsigned char Bin,unsigned char Gin)
{
for(unsigned char i=0; i<numPixels; i++) 
   {
   masterR[i]=Rin;
   masterG[i]=Gin;
   masterB[i]=Bin;
   }
}

