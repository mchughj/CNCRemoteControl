#include <IRremote.h>

// This version of the software uses an Arduino Uno and a client application to interpret the arduino
// serial commands and turn them into keyboard commands.
//
// You only need to get the IRRemote library for this via:
// C:\Users\mchughj\Documents\Arduino\libraries>git clone https://github.com/shirriff/Arduino-IRremote.git IRremote
//
// This program requires a corresponding program on the host computer to read the serial messages and change them
// into actions taken.  I had hoped to use a trinket as a keyboard (via TinketKeyboard library) but the combination
// of the keyboard and IR library did not work together.  I didn't fully debug why but clearly it was an 
// incompatability with the IR library and the TrinketKeyboard library as both by themselves worked fine.

#define DEBUG_OUTPUT

#define RECV_PIN 8
#define LED_PIN 13
#define SPEAKER_PIN 6

#define SHORT_DURATION 500
#define MEDIUM_DURATION 1000
#define LONG_DURATION 2000

IRrecv irrecv(RECV_PIN);

decode_results results;

char tone_names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'   };
int tone_frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

int frequency( char t ) { 
  for (int i = 0; i < 8; i++) {
    if (tone_names[i] == t) {
      return(tone_frequencies[i]); 
    }
  }
  return(0);
} 


void setup()
{
  pinMode(LED_PIN, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver

  Serial.begin(9600);

#ifdef DEBUG_OUTPUT
  Serial.println( "Done with initialize" );
#endif
  tone(SPEAKER_PIN, frequency( 'e' ), MEDIUM_DURATION);
}

void loop() {
  if (irrecv.decode(&results)) {
 
    switch( results.value ) {
      case 0x3d9ae3f7:
        Serial.println( "{UP}");
        tone( SPEAKER_PIN, frequency( 'e' ), SHORT_DURATION);
#ifdef DEBUG_OUTPUT
        Serial.println( "*2 Button on keypad.  Move y+.  Send Up arrow." );
#endif
        break;
      case 0x1bc0157b:
        Serial.println( "{DOWN}");
        tone( SPEAKER_PIN, frequency( 'e' ), SHORT_DURATION);
#ifdef DEBUG_OUTPUT
        Serial.println( "*8 Button on keypad.  Move y-.  Send down arrow." );
#endif
        break;
      case 0x8c22657b:
        Serial.println( "{LEFT}");
        tone( SPEAKER_PIN, frequency( 'e' ), SHORT_DURATION);
#ifdef DEBUG_OUTPUT
        Serial.println( "*4 Button on keypad.  Move x-.  Send left arrow." );
#endif
        break;
      case 0x449E79F:
        Serial.println( "{RIGHT}");
        tone( SPEAKER_PIN, frequency( 'e' ), SHORT_DURATION);
#ifdef DEBUG_OUTPUT
        Serial.println( "*6 Button on keypad.  Move x+.  Send right arrow." );
#endif
        break;
      case 0x32c6fdf7:
        Serial.println( "{PGUP}");
        tone( SPEAKER_PIN, frequency( 'g' ), SHORT_DURATION);
#ifdef DEBUG_OUTPUT
        Serial.println( "*7 Button on keypad.  Move z+.  Send pgup." );
#endif
        break;
      case 0x3ec3fc1b:
        Serial.println( "{PGDN}");
        tone( SPEAKER_PIN, frequency( 'g' ), SHORT_DURATION);
#ifdef DEBUG_OUTPUT
        Serial.println( "*9 Button on keypad.  Move z-.  Send pgdown." );
#endif
        break;
      case 0xf076c13b:
        Serial.println( "-");
        tone( SPEAKER_PIN, frequency( 'd' ), MEDIUM_DURATION);
#ifdef DEBUG_OUTPUT
        Serial.println( "*Minus Button on keypad.  Move slower.  Send minus keypad key." );
#endif
        break;
      case 0xa3c8eddb:
        Serial.println( "=");
        tone( SPEAKER_PIN, frequency( 'd' ), MEDIUM_DURATION);
#ifdef DEBUG_OUTPUT
        Serial.println( "*Plus Button on keypad.  Move faster.  Send = keypad key." );
#endif
        break;
      case 0xe5cfbd7f:
        Serial.println( "0");
        tone( SPEAKER_PIN, frequency( 'a' ), LONG_DURATION);
#ifdef DEBUG_OUTPUT
        Serial.println( "*Equal Button on keypad.  Set x,y,z to zero.  Send 0.");
#endif
        break;
        
      default:
         Serial.print( "*Unknown button" );
         Serial.println(results.value, HEX);
         break;
    }
    
    irrecv.resume(); // Receive the next value   
  }
}
