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
- ~~Build a Hello World Pi Pico build~~
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



# Useful Pi Pico Documentation

- [Getting Started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)
- [Pi Pico Pinout Diagram](https://pico.pinout.xyz/)



# Setup for development on Linux!
## Setup Pico Development Workspace with [Pico-SDK](https://github.com/raspberrypi/pico-sdk)

1. Install the Toolchain

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



## Setup VSCode

1. Install VSCode

```
sudo apt install code
```

2. Install VSCode Extensions

```
code --install-extension marus25.cortex-debug code --install-extension ms-vscode.cmake-tools code --install-extension ms-vscode.cpptools
```



## Setup [Picotool](https://github.com/raspberrypi/picotool)

1. Install dependencies

```
sudo apt install build-essential pkg-config libusb-1.0-0-dev cmake
```

2. Clone picotool into your home directory

```
git clone git@github.com:raspberrypi/picotool.git ~/
cd ~/picotool
```

3. Build Picotool!

```
mkdir build
cd build
cmake ../
make
```

4. Copy the CLI binary into your local binaries directory

```
sudo cp picotool/build/picotool /usr/local/bin/
```

5. Now you can run picotool from any terminal!
```
sudo picotool info
sudo picotool load src/hello/hello.uf2
```

6. You can also remove the picotool repository from your home directory. We don't need that anymore.

```
rm -rf ~/picotool
```



## Setup ROS Humble

This project uses ROS 2 Humble. You can set that up by following the procedure documented [here](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html).



## Setup [Micro-ROS for Pico](https://github.com/micro-ROS/micro_ros_raspberrypi_pico_sdk)

1. Clone the micro-ros for pico repository

```
git clone git@github.com:micro-ROS/micro_ros_raspberrypi_pico_sdk.git --branch humble lib/micro-ros
```

TODO: https://github.com/micro-ROS/micro_ros_raspberrypi_pico_sdk/tree/humble

## TODO: What else needs to be set up?
- Loading the uf2, monitoring the PI PICO minicom -b 115200 -o -D /dev/ttyACM0
- How do I use that debugger probe too?


# Build this project

3. Select the **GCC arm-none-eabi** kit under Configure, and Build using the CMake extension. Voila!