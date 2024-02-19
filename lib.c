// Team 33's Botball library for 2024
// Feel free to look at and study the code as much as you like!
///////////////////////////////////////////////////////////////

#include <stdio.h>
#include <kipr/wombat.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define left 3
#define right 0
#define sensorPort 1

void line_follow(char *side, int distance, int speed, float intensity) {
  // Parameter 1: direction of line relative to robot (either "r" for right or "l" for left)
  // Parameter 2: distance to travel, in ticks
  // Parameter 3: speed, in ticks
  // Parameter 4: intensity of line follow from 0-1 (e.x: 0.5)
  //////////////////////////////////////////////////////////////////////////////////////////

 cmpc(right);
 bool touchedLine = false;
 if (*side == 'r'){
   while (abs(gmpc(right)) < distance) {
     if (analog(sensorPort) > 4000) {
       if (touchedLine == false) {
         printf("Touched line!\n");
         touchedLine = true;
         ao();
         cmpc(right);
         msleep(500);
       }else {
         mav(right,speed);
         mav(left,speed*(1-intensity));
       }
     }else {
       if (touchedLine == false) {
         mav(right,-1*speed);
         mav(left,speed);
       } else {
         mav(right,speed*(1-intensity));
         mav(left,speed);
       }
     }
   }
  } else if (*side == 'l'){
   while (abs(gmpc(right)) < distance) {
     if (analog(sensorPort) > 3000) {
       if (touchedLine == false) {
         printf("Touched line!\n");
         touchedLine = true;
         ao();
         cmpc(right);
         msleep(500);
       }else {
         mav(right,speed*(1-intensity));
         mav(left,speed);
       }
      }else {
        if (touchedLine == false) {
         mav(right,speed);
         mav(left,-1*speed);
       } else {
         mav(right,speed);
         mav(left,speed*(1-intensity));
       }
     }
   }
   }else {
    printf("ERROR: function \"line_follow\" needs its first parameter to either be \"r\" or \"l\"\n");
  }
}

void drive(char *direction, int distance, int speed) {
  // Parameter 1: direction to travel in ("f" for forward, and "b" for backward)
  // Parameter 2: distance to travel, in ticks
  // Parameter 3: speed to travel, in ticks
  /////////////////////////////////////////

  cmpc(right);
  if (*direction == 'f') {
    while (abs(gmpc(right)) < distance) {
      mav(right, speed);
      mav(left, speed);
    }
    ao();
    msleep(250);
  } else if (*direction == 'b') {
    while (abs(gmpc(right)) < distance) {
      mav(right, -1*speed);
      mav(left, -1*speed);
    }
    ao();
    msleep(250);
  } else {
    printf("ERROR: function \"drive\" needs its first parameter to either be \"f\" or \"b\"\n");
  }
}
