# hello-pico-ros
An introduction to running ROS 2 on the PI Pico



Hello! :D

So what is this project?
- Hello world to using Micro-ROS
- I want to Pi picos running micro ros, talking to each other
- I want a PI to be able to join the conversation for monitoring
- PI Pico #1 has a potentiometer
- PI Pico #2 has a Servo
- Potentiometer Position -> Servo Position

# Notes
So we have two targets to build, one for the controller and another for the outputs

# Tasks
- Build a Hello World Pi Pico build
- Convert it into a pi Pico ROS build
- Add the Potentiometer
- Split the project into two targets
- Add the Servo Target




# Pico Setup Steps
- Clone the project into home directory
- Add to bashrc the SDK Path
- Make sure Makefiles check the $ENV(SDK PATH)
- voila!
- Add steps for setting up your workspace: clone 

# Setup for development on Linux!
## Setup Pico Development workspace

1. Install the necessary packages

```
sudo apt update
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

2. Clone the pico-sdk repository into your home directory

```
git clone https://github.com/raspberrypi/pico-sdk.git --branch master ~/pico-sdk
cd ~/pico-sdk
git submodule update --init
```

3. Add PICO_SDK_PATH to your bashrc

```
echo "export PICO_SDK_PATH=$HOME/pico-sdk" >> ~/.bashrc
source ~/.bashrc
```