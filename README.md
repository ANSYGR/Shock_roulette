# Shock Roulette

## Description

Shock Roulette is an interactive, Arduino-based game designed to entertain and engage participants by selecting a random 'loser' through a visually appealing LED display sequence. The game uses a NeoPixel LED strip and incorporates a button and potentiometer for player interactions, along with a relay to trigger a mild shock or other physical signal when the game finds a 'loser.'

## Features

- NeoPixel LED strip visualization
- Debounced button for reliable operation
- Analog input via potentiometer for player selection
- Relay output for signaling game outcome

## Hardware Requirements

- Arduino Uno or similar microcontroller
- Adafruit NeoPixel LED Strip
- Pushbutton
- Potentiometer
- Relay Module
- High voltage module
- Power supply for Arduino and LED strip
- 3D printed casing

## Software Requirements

- Arduino IDE
- Adafruit NeoPixel Library

## Usage

To play Shock Roulette:

1. Power on the device.
2. Each player selects their position using the potentiometer.
3. Press the button to start the spinning sequence.
4. Watch as the LED stops at a random position.
5. If the position matches your selection, the relay will activate, signaling a 'loss.'

## Acknowledgements

- Adafruit for NeoPixel library
- Arduino Community
- etc.
