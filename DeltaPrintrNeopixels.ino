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
  mode = 4;
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
     else if(mode == 4)
        {
        //setMaster(PIXEL_COUNTL,200,255,255);
        //outputMaster();
        //strip.show();
        //delay(100);
        }
     else if(mode == 5)
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
        case 4: Firework(PIXEL_COUNTL,200,200,255, random(1,255), random(1,255), random(1,255), 1.1, 1.14, 1.4);
            delay(20);
            mSecTime = mSecTime + 20;
            break;
        case 5: Firework(PIXEL_COUNTL,random(1,255),random(1,255),random(1,255), random(1,255), random(1,255), random(1,255), 1.4, 1.1, 1.2);
            delay(20);
            mSecTime = mSecTime + 20;
            break;
        }
            
            
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

void Firework(unsigned char numPixels, unsigned char R,unsigned char G, unsigned char B,unsigned char Rt,unsigned char Gt, unsigned char Bt, float Kr, float Kg, float Kb)
{
// Many of these parameters should be bounded randoms for extra special effects =D

// velMax without going off screen is 17.2 pixels/sec with gravity set to 4.
// Total air time is 8.6 seconds. 
// Apogee is at 4.3 seconds. 
// 5 second fuse seems good

// velMidpoint is 12 pixels/sec with gravity set to 4
// Total air time is 6 seconds
// Apogee is at 3 seconds
// 4 second fuse seems good

static char state=0,shellPos=0;
static int fuseTime=0,splosionSize=0,timeShell0=0;
static float vel0=0,KrSplosion,KgSplosion,KbSplosion;
float gravity=.000004; //pixels per second per second

//shellPos = shellPos + sign; 
//if(shellPos >= numPixels || eyePos < 0)
//   sign = sign * -1;  
switch(state)
   {
   case 0: //Init
      shellPos=0;
      vel0 = random(1200,1720)/100000.0;
      //vel0 = .015;
      //vel0 = vel0+vel0*random(-1*1000,1*1000)/1000.0*.15; //10 percent variation of velocity
      //vel0 = vel0+vel0*(1-0.5)*2.0*.1; //10 percent variation of velocity
      //fuseTime = 5000; 
      //fuseTime = fuseTime+fuseTime*random(-1*1000,1*1000)/1000.0*.15; //10 percent variation of velocity
      fuseTime = random(3000,7000);
      timeShell0 = mSecTime; //Log start time for zero ref
      splosionSize = random(2,10);
      state=1;
      break;
      
   case 1: //Fire Shell
      //shellPos = -(1/2)      *g*t^2+v0t+y0
      shellPos = -0.5*gravity*(mSecTime-timeShell0)*(mSecTime-timeShell0)+(mSecTime-timeShell0)*vel0;
      if(shellPos < 0 || (mSecTime-timeShell0) > fuseTime)
         state=2;
      break;
      
   case 2: //Shell exploding
      for(int i=shellPos-splosionSize; i <= shellPos+splosionSize; i++)
         {
         if( i > 0 && i < numPixels)
            {
            masterR[i] = Rt+(ZeroClip(random(-2*1000,2*1000)/1000.0)-1)*75.0; //create random number, chop off botton half to zero to make sparse sparkles
            masterG[i] = Gt+(ZeroClip(random(-2*1000,2*1000)/1000.0)-1)*75.0;
            masterB[i] = Bt+(ZeroClip(random(-2*1000,2*1000)/1000.0)-1)*75.0;
            }
         }   
      KrSplosion = random(1.01*1000,1.2*1000)/1000.0;
      KgSplosion = random(1.01*1000,1.2*1000)/1000.0;
      KbSplosion = random(1.01*1000,1.2*1000)/1000.0;
      
      Kr = KrSplosion;
      Kg = KgSplosion;
      Kb = KbSplosion;
      
      state = 3;
      break;
      
   case 3: //Shell fading
      for(int i=shellPos-splosionSize; i <= shellPos+splosionSize; i++)
         {
         if( i > 0 && i < numPixels)
            { //sparkle needs works because per color sparkle is so improbable it will only affect R G or B, never other colors...
              //maybe calc distributed color THEN dice roll to implement instead?
            float sparkle = ZeroClip(random(-1000,10))/7.5; //bound between 0 and 10/7.5=1.3x increase
            masterR[i] = masterR[i]+masterR[i]*(sparkle+ZeroClip(random(-4000,10))/2.0); //per color sparkle bounded between 0 and 5x
            masterG[i] = masterG[i]+masterG[i]*(sparkle+ZeroClip(random(-4000,10))/2.0); //per color sparkle too
            masterB[i] = masterB[i]+masterB[i]*(sparkle+ZeroClip(random(-4000,10))/2.0); //per color sparkle too
            }
         }   
         
      Kr = KrSplosion;
      Kg = KgSplosion;
      Kb = KbSplosion;
      if((mSecTime-timeShell0) > 8000)
         state = 0;
      break;
   }
        
for( int i = 0; i < numPixels;  i++ )
   {
   if(state == 1 && i < shellPos)  //only sparkle under rising shell
      {
      float sparkle = ZeroClip(random(-1000,10))/7.5; //bound between 0 and 10/7.5=1.3x increase
      masterR[i] = masterR[i]+masterR[i]*(sparkle+ZeroClip(random(-4000,10))/2.0); //per color sparkle bounded between 0 and 5x
      masterG[i] = masterG[i]+masterG[i]*(sparkle+ZeroClip(random(-4000,10))/2.0); //per color sparkle too
      masterB[i] = masterB[i]+masterB[i]*(sparkle+ZeroClip(random(-4000,10))/2.0); //per color sparkle too
      }
   
   masterR[i] = masterR[i] / Kr;
   masterG[i] = masterG[i] / Kg;
   masterB[i] = masterB[i] / Kb;
      
   if(i == shellPos && state == 1)
      {
      masterR[i] = R;
      masterG[i] = G;
      masterB[i] = B;
      }
   }
}

float ZeroClip(float input)
{
  if( input < 0)
     return 0;
  else
     return input;
}
