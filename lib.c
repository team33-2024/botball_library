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

void line_follow(int distance, int speed, int port, float intensity, char *side) {
  // Parameter 1: distance to travel, in ticks
  // Parameter 2: speed, in ticks
  // Parameter 3: port of analog sensor that follows line
  // Parameter 4: intensity of line follow from 0-1 (e.x: 0.5)
  // Parameter 5: direction of line relative to robot (either "r" for right or "l" for left)
  //////////////////////////////////////////////////////////////////////////////////////////
  
  bool touchedLine = false;
  if (*side == 'r'){
    cmpc(right);
    while (abs(gmpc(right)) < distance) {
      if (analog(port) > 4000) {
        if (touchedLine == false) {
          printf("Touched line!\n");
          touchedLine = true;
          ao();
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
  } else {
    if (*side == 'l'){
    cmpc(right);
    while (abs(gmpc(right)) < distance) {
      if (analog(port) > 3000) {
        if (touchedLine == false) {
          printf("Touched line!\n");
          touchedLine = true;
          ao();
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
      printf("ERROR: function \"line_follow\" needs its fifth parameter to either be \"r\" or \"l\"\n");
    }
  } 
}
