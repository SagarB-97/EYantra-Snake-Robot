# Snake-Robot

## Video

Video of the working Snake robot demonstrated in E-Yantra national finals in IIT Bombay :

[E-Yantra National Finals 2018](https://www.youtube.com/watch?v=MwMsUCSI5WU)

Our robot was declared the winner in the `Spotter Snake` theme.


## E-Yantra

Website : http://www.e-yantra.org/

> E-Ynatra is an initiative by IIT Bombay that aims to create the next generation of embedded systems engineers with a practical outlook to help provide practical solutions to some of the real world problems.

> e-Yantra Robotics Competition (eYRC) is a unique annual competition for undergraduate students in science and colleges. Abstracts of real world problems assigned as "themes" are then implemented by the teams using the robotic kits.

## Our Theme

Our theme was entitiled `Spotter Snake`. The tasks included :
- Designing brackets of the snake robot
- Simulating the snake bot on a simulation environment called V-REP
- 3D printing the robot's brackets
- Assembling the bot and designing circuits for power distribution and snake control
- Designing a wireless joystick to control the robot
- Programming the Wireless joystick to interact with the bot
- Programming the Snake robot to interact with the transmitting Joystick and exhibit various gaits

## Contents

This repository contains all the Embedded C programs associated with our snake bot.

Two Arduino Nano microcontrollers were used in the snake bot. One of them controlled the Servos and the other gathered and processed color sensor values.

The transmitter also used an Arduino nano microcontroller.

`ReceiverSnakeBody` : Module to control the 'snake's body' or the position of the servos at every instant. Code is written to mimic an actual snake's movement including various gaits such as `Caterpillar`, `Serpentine` and `Side Winding`

`RodentDetection` : Module to detect colored 'rodents'  

`Caliberation` : Module to automatically caliberate the color sensor used in detection of 'rodents'

`WirelessJoystick` : Code on the wireless joystick that interacts with the snake bot.

