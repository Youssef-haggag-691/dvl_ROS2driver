## Vortex A50-DVL driver <ROS2 C++ Package>

## Table of contents
* [Description](#Description)
* [Prerequisites](#Prerequisites)
* [Wiring](#Wiring)
* [Installation](#Installation)
* [Usage](#Usage)
* [Technical Details](#Technical-Details)

## Description
ROS2 package for serial-interfacing with waterlinked A50  DVL. 
There is also an associated custom-ros2-message for DVL measurement data.

![a50_side](./img/a50_front.jpeg)

## Prerequisites
* Linux distributions Bionic (Ubuntu 18.04)
* C++ 11 compiler or newer.
* ROS2 - Eloquent 

## Wiring
![wiring_dvl](./img/wiring_dvl.png)

## Installation
Inside the src folder of your ROS2 workspace, clone the package 
```
$ cd ~/vortex_ws/src
$ git clone git clone https://github.com/MoMagDii/dvl_ROS2driver.git
```
## Usage
1-Build the package
```
$ cd ~/vortex_ws
$ colcon build --packages-select dvl_message dvl_interface
```
2- Open a new terminal and source the workspace and execute the Rx node,
```
$ cd ~/vortex_ws
$ . install/setup.bash
$ ros2 run dvl_interface Rx
```
3- Open a new terminal and source the ws and execute the Parser node.
```
$ cd ~/vortex_ws
$ . install/setup.bash
$ ros2 run dvl_interface Parser
```
4- Open a new terminal and source the ws and execute the Dvl node.
```
$ cd ~/vortex_ws
$ . install/setup.bash
$ ros2 run dvl_interface Dvl
```
![a50](./img/a50.gif)




