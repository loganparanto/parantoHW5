/** Simple On-board LED flashing program - written in C by Derek Molloy
*    simple functional struture for the Exploring BeagleBone book
*
*    This program uses USR LED 3 and can be executed in three ways:
*         makeLED on
*         makeLED off
*         makeLED flash  (flash at 100ms intervals - on 50ms/off 50ms)
*         makeLED status (get the trigger status)
*
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */



void writeLED(char filename[], char value[]);
void removeTrigger();

int main(int argc, char* argv[]){
   if(argc!=2){
	printf("Usage is makeLEDC and one of:\n");
        printf("   on, off, flash or status\n");
	printf(" e.g. makeLED flash\n");
        return 2;
   }
   printf("Starting the makeLED program\n");
   printf("The current LED Path is: " LED3_PATH "\n"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to control the LED (write to the GPIO file)
void writeLED(char* ledTrigger, char* state) {
    FILE* fp = fopen(ledTrigger, "w");
    if (fp == NULL) {
        perror("Error opening LED trigger file");
        exit(1);
    }
    fprintf(fp, "%s", state);
    fclose(fp);
}

// Function to remove the trigger file to allow manual control of the LED
void removeTrigger(char* ledPath) {
    char triggerPath[256];
    sprintf(triggerPath, "%s/trigger", ledPath);
    writeLED(triggerPath, "none");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        fprintf(stderr, "Valid commands: on, off, flash\n");

        // Flash the LED at a rate of 1 second ON, 1 second OFF (for invalid command)
        while (1) {
            writeLED("/sys/class/leds/beaglebone:green:usr3/trigger", "none");
            sleep(1);
            writeLED("/sys/class/leds/beaglebone:green:usr3/trigger", "timer");
            sleep(1);
        }

        exit(1);
    }

    char* command = argv[1];

    if (strcmp(command, "on") == 0) {
        // Turn the LED on
        writeLED("/sys/class/leds/beaglebone:green:usr3/brightness", "1");
        removeTrigger("/sys/class/leds/beaglebone:green:usr3");
    } else if (strcmp(command, "off") == 0) {
        // Turn the LED off
        writeLED("/sys/class/leds/beaglebone:green:usr3/brightness", "0");
        removeTrigger("/sys/class/leds/beaglebone:green:usr3");
    } else if (strcmp(command, "flash") == 0) {
        // Flash the LED at a rate of 1 second ON, 1 second OFF
        while (1) {
            writeLED("/sys/class/leds/beaglebone:green:usr3/brightness", "1");
            sleep(1);
            writeLED("/sys/class/leds/beaglebone:green:usr3/brightness", "0");
            sleep(1);
        }
    } else {
        fprintf(stderr, "Invalid command: %s\n", command);
        fprintf(stderr, "Valid commands: on, off, flash\n");

        // Flash the LED at a rate of 1 second ON, 1 second OFF (for invalid command)
        while (1) {
            writeLED("/sys/class/leds/beaglebone:green:usr3/trigger", "none");
            sleep(1);
            writeLED("/sys/class/leds/beaglebone:green:usr3/trigger", "timer");
            sleep(1);
        }

        exit(1);
    }

    return 0;
}

