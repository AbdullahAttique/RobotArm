# RobotArm

A robot that can move using its on-board controls or using a wireless controller. It is controlled in terms of cartesian coordinates rather than simply rotating each of the joints. Features a gripper as its end effector. Largely 3D printable requires minimal extra hardware.
## Features

- On-board control and wireless control option.
- 3 degrees of freedom + gripper.
- Moves in cartesian coordinate space using inverse kinematics


## Images
The Robot
![A picture of the robot](https://github.com/AbdullahAttique/RobotArm/blob/main/robot%20photograph.jpg?raw=true)
Wireless Controller
![wireless controller](https://github.com/AbdullahAttique/RobotArm/blob/main/wireless%20controller.jpg?raw=true)
![wireless controller exposed](https://github.com/AbdullahAttique/RobotArm/blob/main/wireless%20controller%20exposed.jpg?raw=true)
CAD model
![CAD Model](https://github.com/AbdullahAttique/RobotArm/blob/main/CAD%20picture.png?raw=true)



## Technical Details
- driven by an arduino uno board.
- moves and grips using 4 SG90 servos.
- geared 1:2 to increase torque
- limited to 90 degrees movement per joint due to servos and gearing
- Uses nRF24L01 module for wireless control
## Libraries Used
- Wireless communication - RF24
