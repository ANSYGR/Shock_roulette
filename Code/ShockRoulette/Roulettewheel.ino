/*
* Name: Shock Roulette
* Author:  Andy Granfors
* Date: 2025-02-07
* Description: Shock Roulette is an interactive game designed for multiple players, 
 * utilizing a NeoPixel LED ring and various hardware components to create a 
 * random selection game. When a button is pressed, the game initiates a spinning 
 * sequence on the LED ring. Players use a potentiometer to select their position 
 * on the strip. The game randomly stops on one of the LEDs. If the stopped LED 
 * matches the player's chosen position, a relay triggers a high voltage shock module. 
 * The purpose of the game is to provide an entertaining and engaging way to select 
 * a 'random loser' among participants. The game features debounced button inputs 
 * to ensure stable and reliable operation, while the Adafruit NeoPixel library 
 * controls the visual display. This project is perfect for social gatherings and 
 * can be adapted for various fun and interactive applications.
*/

// Include Libraries
#include <Adafruit_NeoPixel.h>

#define PIN_NEO_PIXEL  2
#define NUM_PIXELS     24

// Init constants
const int potPin = A0;
const int neoPin = 2;
const int btnPin = 3;
const int randomSeedPin = A5;
const int relayPin = 7;

// Init global variables
int spinValue = 0;
int chosenValue = 0;
int previousValue = -1;
bool spinning = false;

// construct objects
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  // init communication
  strip.begin();
  Serial.begin(9600);
  // Init Hardware
  pinMode(potPin, INPUT);
  pinMode(btnPin, INPUT);
  randomSeed(analogRead(randomSeedPin));
  idle(); 
}

/*
 * Main program loop that handles the game logic based on user input and game state.
 * Parameters: None
 * Returns: None
 */
void loop(){

  if (spinning == false){
     Serial.println(digitalRead(btnPin));
    selection();
  }
   if ((debouncedRead(3)) == true) {
     Serial.println(digitalRead(btnPin));
    spinning = true;
    spin ();
  }
}

/*
*This function reads the input of a pushbutton and outputs a state if the button is stable HIGH, this ensures a stable and debounced signal.
*Parameters: Void
*Returns: True or False, if button is pressed
*/
bool debouncedRead(int pin) {
  for (int i = 0; i < 300; i++) { // Repeat the check 300 times to confirm the button state is stable

    if (digitalRead(pin) != HIGH) {
    return false;
    }
    delay(5);
    }
    return true;
}

/*
 * Controls the spinning sequence of the LED strip and handles game outcome.
 * Parameters: None
 * Returns: None
 */
void spin() {
  idle();
  int stopAt = rand() % NUM_PIXELS;  // Generate a random stop position between 0 and 23

  for (int i = 0; i < 200; i++) { 
    int spinValue = i % NUM_PIXELS;
    strip.setPixelColor(spinValue, strip.Color(100, 100, 100));
    strip.show();
    delay(i * 4);

    if (spinValue == stopAt && i >= NUM_PIXELS) {
      delay(100);
      break;
    }

    idle();
    strip.show();
    delay(50 + i * 2);
  }

  strip.setPixelColor(stopAt, strip.Color(100, 100, 100));
  strip.show();
  
  if (stopAt == chosenValue) {
    trigger();
    relay();
    idle();
    delay(100);
    trigger();
    delay(100);
    idle();
    delay(100);
    trigger();
    delay(100);
    idle();
    delay(100);
    trigger();
    delay(100);
  }

  spinning = false;
}

/*
 * Selects the LED based on the analog potentiometer value.
 * Parameters: None
 * Returns: None
 */
void selection() {
  int potValue = analogRead(potPin);
  int mappedValue = map(potValue, 0, 1023, 0, 23);
  chosenValue = round(mappedValue);
  blinker();
}

/*
 * Blinks the chosen LED to indicate the current selection.
 * Parameters: None
 * Returns: None
 */
void blinker(){
  strip.setPixelColor(chosenValue, strip.Color(5, 15, 5));
  strip.show();
  delay(350);
  idle();
  strip.show();
  delay(350);
  
}

/*
 * Activates the relay for a specified duration.
 * Parameters: None
 * Returns: None
 */
void relay() {
  digitalWrite(relayPin, HIGH);
  delay(250);
  digitalWrite(relayPin, LOW);
}

/*
 * Updates the display to show a idle pattern on the NEOPIXEL in the visual of a roulette wheel.
 * Parameters: None
 * Returns: None
 */
void idle() {
    strip.setPixelColor(0, strip.Color(50, 0, 0));
    strip.setPixelColor(1, strip.Color(0, 0, 0));
    strip.setPixelColor(2, strip.Color(50, 0, 0));
    strip.setPixelColor(3, strip.Color(0, 0, 0));
    strip.setPixelColor(4, strip.Color(50, 0, 0));
    strip.setPixelColor(5, strip.Color(0, 0, 0));
    strip.setPixelColor(6, strip.Color(50, 0, 0));
    strip.setPixelColor(7, strip.Color(0, 0, 0));
    strip.setPixelColor(8, strip.Color(50, 0, 0));
    strip.setPixelColor(9, strip.Color(0, 0, 0));
    strip.setPixelColor(10, strip.Color(50, 0, 0));
    strip.setPixelColor(11, strip.Color(0, 50, 0));
    strip.setPixelColor(12, strip.Color(0, 0, 0));
    strip.setPixelColor(13, strip.Color(50, 0, 0));
    strip.setPixelColor(14, strip.Color(0, 0, 0));
    strip.setPixelColor(15, strip.Color(50, 0, 0));
    strip.setPixelColor(16, strip.Color(0, 0, 0));
    strip.setPixelColor(17, strip.Color(50, 0, 0));
    strip.setPixelColor(18, strip.Color(0, 0, 0));
    strip.setPixelColor(19, strip.Color(50, 0, 0));
    strip.setPixelColor(20, strip.Color(0, 0, 0));
    strip.setPixelColor(21, strip.Color(50, 0, 0));
    strip.setPixelColor(22, strip.Color(0, 0, 0));
    strip.setPixelColor(23, strip.Color(0, 50, 0));
    strip.show(); 
}

/*
 * Triggers a visual alert pattern across all LEDs to indicate the losing mode in the game.
 * Parameters: None
 * Returns: None
 */
void trigger() {
    strip.setPixelColor(0, strip.Color(200, 0, 0));
    strip.setPixelColor(1, strip.Color(200, 0, 0));
    strip.setPixelColor(2, strip.Color(200, 0, 0));
    strip.setPixelColor(3, strip.Color(200, 0, 0));
    strip.setPixelColor(4, strip.Color(200, 0, 0));
    strip.setPixelColor(5, strip.Color(200, 0, 0));
    strip.setPixelColor(6, strip.Color(200, 0, 0));
    strip.setPixelColor(7, strip.Color(200, 0, 0));
    strip.setPixelColor(8, strip.Color(200, 0, 0));
    strip.setPixelColor(9, strip.Color(200, 0, 0));
    strip.setPixelColor(10, strip.Color(200, 0, 0));
    strip.setPixelColor(11, strip.Color(200, 0, 0));
    strip.setPixelColor(12, strip.Color(200, 0, 0));
    strip.setPixelColor(13, strip.Color(200, 0, 0));
    strip.setPixelColor(14, strip.Color(200, 0, 0));
    strip.setPixelColor(15, strip.Color(200, 0, 0));
    strip.setPixelColor(16, strip.Color(200, 0, 0));
    strip.setPixelColor(17, strip.Color(200, 0, 0));
    strip.setPixelColor(18, strip.Color(200, 0, 0));
    strip.setPixelColor(19, strip.Color(200, 0, 0));
    strip.setPixelColor(20, strip.Color(200, 0, 0));
    strip.setPixelColor(21, strip.Color(200, 0, 0));
    strip.setPixelColor(22, strip.Color(200, 0, 0));
    strip.setPixelColor(23, strip.Color(200, 0, 0));
    strip.show(); 
}