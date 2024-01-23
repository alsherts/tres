# TCP Reversed Echo Server
## Prerequisites

Packages:
- g++
- cmake
- libpoco-dev
  
## Source code

Check out the code using:

    git clone https://github.com/alsherts/tres.git

and build it using:

    cd tres
    cmake -B build && cmake --build build
    
## Run and test

Run server application with:

    build/tres
    
open another console and run:

    telnet localhost 28888

