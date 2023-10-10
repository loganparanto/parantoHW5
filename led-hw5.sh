#!/bin/bash
#Script Description:
# This script blinks the USR3 LED on a BeagleBone Black n times with a 1-second ON and 1-second OFF duration.
# It accepts two command line arguments: "blink" and an integer n.
# Example invocation:
# ./led-hw5.sh blink 5

# Check if the script has two arguments
if [ "$#" -ne 2 ]; then
	  echo "Usage: $0 blink <n>"
	    echo "Where <n> is the number of times to blink the LED."
	      exit 1
fi

# Define the LED3 path
LED3_PATH="/sys/class/leds/beaglebone:green:usr3"

# Check if the LED3 path exists
if [ ! -d "$LED3_PATH" ]; then
	  echo "Error: LED3 path not found. Make sure you are running this script on a BeagleBone Black."
	    exit 1
fi

# Extract the command and number of blinks from command line arguments
COMMAND="$1"
NUM_BLINKS="$2"

# Function to turn the LED on
turn_on_led() {
	  echo "1" > "$LED3_PATH/brightness"
  }

# Function to turn the LED off
turn_off_led() {
	  echo "0" > "$LED3_PATH/brightness"
  }

# Blink the LED n times
if [ "$COMMAND" == "blink" ]; then
	  echo "Starting the LED Bash Script"
	    echo "The LED command that was passed is: $COMMAND"
	      echo "Blinking the LED $NUM_BLINKS times"
	        
	        for ((i = 0; i < NUM_BLINKS; i++)); do
			    turn_on_led
			        sleep 1
				    turn_off_led
				        sleep 1
					  done
					    
					    echo "End of the LED Bash Script"
				    elif [ "$COMMAND" == "off" ]; then
					      # Turn the LED off
					        turn_off_led
						  echo "LED turned off"
					  elif [ "$COMMAND" == "flash" ]; then
						    # Flash the LED once
						      turn_on_led
						        sleep 1
							  turn_off_led
							    echo "LED flashed once"
						    else
							      echo "Invalid command: $COMMAND. Valid commands are 'blink', 'off', or 'flash'."
							        exit 1
					  fi
