# ROS2_STM32_Comm

A ROS2 Node for sending commands to and receiving data from an STM32 running the associated firmware

## Description

This node is intended to be modified to add more commands later or change all the commands, SerialComm sends raw commands while StmComm is a wrapper to have nice functions to use

## Getting Started

### Dependencies

- ROS2 Humble
- [libserial](https://github.com/crayzeewulf/libserial)

### Installing

Clone the repository  
```bash
git clone https://github.com/The-Last-Resort-FR/ROS2_STM32_Comm.git
cd ROS2_STM32_Comm
```  
Build  
```bash
colcon build --symlink-install
```
Source the environement  
```bash
source install/setup.bash
```

### Executing program

Run the node  
```bash
ros2 run stm_comm stm_comm
```

## TODO

- Wrapper
- Multiple data
- Resend
- ROS2 integration

## Tested Hardware

- Jetson AGX Orin
- STM32 Nucleo F411RE 

## Version History

- V0.0.0 : Raw comm and structure

## License

This project is licensed under the "The Unlicense" License - see the LICENSE.md file for details

## Acknowledgments

-  