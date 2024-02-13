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
- ~~Convert it into a pi Pico ROS build~~
- ~~Add the Potentiometer~~
- Add the Servo Target
- Split the project into two targets




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

> Note: If you are using VSCode's "Remote Explore" to code over SSH, then make sure to reboot after setting up environment variables otherwise CMake will not be able to locate PICO_SDK_PATH



## Setup [Picotool](https://github.com/raspberrypi/picotool)

1. Install dependencies

```
sudo apt install build-essential pkg-config libusb-1.0-0-dev cmake
```

2. Clone picotool into your home directory

```
git clone git@github.com:raspberrypi/picotool.git ~/picotool
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
sudo cp ~/picotool/build/picotool /usr/local/bin/
```

5. Now you can run picotool from any terminal!
```
sudo picotool info
sudo picotool load build/src/hello/hello.uf2
```

6. You can also remove the picotool repository from your home directory. We don't need that anymore.

```
rm -rf ~/picotool
```



## Setup ROS Humble

This project uses ROS 2 Humble. You can set that up by following the procedure documented [here](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html).

And to source your ROS2 Environment on every session, run this command

```
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
```

## Setup micro-ros-agent

1. Follow the instructions for Building the micro-ros-setup package on ROS2 [here](https://github.com/micro-ROS/micro_ros_setup?tab=readme-ov-file#building)

2. Follow the instructions for Building and running the micro-ros-agent [here](https://github.com/micro-ROS/micro_ros_setup?tab=readme-ov-file#building-micro-ros-agent)

#TODO:DS: Example
```
ros2 run micro_ros_agent micro_ros_agent serial -D /dev/ttyACM0
```

#TODO:DS: Redo this for our project. Simplify the steps from the repo and specify it for humble. Or should we just use the docker container?


## TODO: What else needs to be set up?
- Loading the uf2, monitoring the PI PICO minicom -b 115200 -o -D /dev/ttyACM0
- How do I use that debugger probe too?
- micro-ros-agent? https://ubuntu.com/blog/getting-started-with-micro-ros-on-raspberry-pi-pico


# Build this project

3. Select the **GCC arm-none-eabi** kit under Configure, and Build using the CMake extension. Voila!


# Sub Directories (rename this, please)

- [hello](src/hello/hello.md)
- [potentiometer_reader](src/potentiometer_reader/potentiometer_reader.md)

# TODO
- Should I just automatically fetch pico-sdk as well? Seems easier... :P
- Add wiring diagrams for the projects