<h4 align="center">Control your Tello Ryze from your computer !</h4>

## Purpose

The goal of this documentation is to help anyone wanting to study this code. If you want to implement your own program, or help writing this one, this documentation is for you !
Some things are not explained as they are trivial. If you have a question regarding the code, or the way things are implement, you can open an issue to ask your question.
You are also more than welcome to fork the project, and improve things. Just make sure to write unit tests, and document everything you do if you want to open a Pull Request.

## How to compile the documentation ?

Open this directory in a terminal, and type `make`. You can then open up the documentation with the browser of your choice by typing :
```
$BROWSER ./builds/html/index.html
```

## Commands

You may be looking at the documentation to check what commands are used to control the drone.
Although it is not possible at this time to configure the commands, it is added to the `In The Works` list.

Here are the current supported commands:
```
"battery?"          -> b        #query battery status
"cw 90"             -> q        #turn clockwise 90 degrees
"ccw 90"            -> e        #turn counter-clockwise 90 degrees
"delay 5"           -> x        #waits for 5 seconds
"flip front"        -> o        #performs a front flip
"flip back"         -> l        #performs a back flip
"flip left"         -> k        #performs a left flip
"flip right"        -> ;        #performs a right flip
"height?"           -> h        #query height
"land"              -> m        #lands the drone
"move up"           -> SPACE    #moves the drone up
"move down"         -> z        #moves the drone down
"move forward"      -> w        #moves the drone forward
"move backward"     -> s        #moves the drone backward
"move left"         -> d        #moves the drone left
"move right"        -> a        #moves the drone right
"takeoff"           -> r        #initiates takeoff
"time?"             -> t        #query flight time
NULL                -> c        #quits the program (and automatically lands the drone)
```

The reason we can only use ascii-supported characters is because the program currently reads `FILENO_STDIN` to get the user input.
A better IO handler is in the works, but in the meantime, this solution "works".


# Socket handler

The Tello Ryze drone has a WIFI router installed on the drone, and to interact with it, you have to connect to the router.
The drone then sends command-related data to port `3000` of your local ip (`0.0.0.0`). It also expects data from this IP: `127.168.1.10:8889`.
The expected protocol is UDP, using DATAGRAM sockets.
