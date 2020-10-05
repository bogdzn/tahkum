<p align="center">
  <img src="https://images.unsplash.com/photo-1499808624579-3471e371ce50?ixlib=rb-1.2.1&ixid=eyJhcHBfaWQiOjEyMDd9&auto=format&fit=crop&w=1350&q=80" width=500 />
</p>

<div align="center">
  <a href="https://github.com/bogdzn/tahkum/actions">
    <img src="https://img.shields.io/endpoint.svg?url=https://actions-badge.atrox.dev/bogdzn/tahkum/badge?ref=master" alt="build status" />
  </a>
  <a href="https://codecov.io/gh/bogdzn/tahkum">
    <img src="https://codecov.io/gh/bogdzn/tahkum/branch/master/graph/badge.svg" />
  </a>
  <a href="https://github.com/bogdzn/tahkum/releases">
    <img src="https://img.shields.io/github/release/bogdzn/tahkum.svg" alt="Latest version" />
  </a>
</div>

<h4 align="center">Control your Tello Ryze from your computer !</h4>

## About

This program is compatible with the Tello Ryze. It allows you to send commands to your drone, from your computer.
It is still under very active development, and will receive many features soon !

## Feature

- can interact with a Tello Ryze, through its private API, and the use of DGRAM sockets
- minimalistic debug mode, and log file handler. 


## In the works

- better UI
- multi-threading support
- sending commands in real time

## How to use ?

To compile the program, you will first need to `clone` the repository, and compile the project:
```bash
git clone https://github.com/bogdzn/tahkum && cd tahkum/app && make
```

You can then type `./tahkum -h` to check the available options for the program and how to use it.
You can also check the documentation, doing `make doc` and, opening `./doxygen/build/html/index.html` with your favorite browser.