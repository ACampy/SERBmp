# Mobile Robotics Project

## This is the repo for Alex and Lissett's Mobile Robotics project.
It contains code written for Python 2.7 and Arduino. 

## Goal
In python we generate a shortest path from one node into another in a graph and convert those into commands for the SERB robot run by the arduino. These commands are store in a queue which get sent using PySerial to the Arduino.
The Arduino reads the dequeued commands over the USB and performs the corresponding actions.

### The graph we are using
![Graph](https://github.com/ACampy/SERBmp/blob/master/Reference/pastedImage0.png)

### Problems
Currently we are having difficulty with PySerial communicating with the the arduino. 
To test the rest of the project we have hard coded 2 sample command queues in an array. Un commenting one of these will allow the SERB to run those commands 

The following is the repo structure:
## SERB directory contains project files
  `SERBmp.ino` is Arduino code for SERB motion control. 
  `SortestPathSearch.py` generates a graph, finds the shortest path, and creates appropriate motion plan.

## Reference files in Reference directory
  Reference files for PySerial, SERB, and Line Following template code.
