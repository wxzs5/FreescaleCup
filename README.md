# WesternCom
***
## Introduction
***
The repository's source code is the 11th(2016) National Undergraduates' Smart Car Competition(i.e. The NXP Cup Smart Car Competition) code of Sichuan University's School Team: **PassCet6**. The team has three members, and I am one of this team. We build a smart car can trace black line on the ground. Finally this car can run at about 3 m/s and we won the first prize in the western district of China, Representing Sichuan University to join the National Finals Competition.

![Award](http://b268.photo.store.qq.com/psb?/32570f55-05ef-4138-8cb3-992ef63b0503/xz*SCRpF6uBXKL4zXea9BhKK.5vf8SCM*mp9pjpjd2g!/b/dAwBAAAAAAAA&bo=OASgBQAAAAAFALo!&rf=viewer_311)

This is our car running video in the Competition:

[![PassCet6]](http://v.youku.com/v_show/id_XMTY0NTcyNDgzMg==.html?spm=a2h0k.8191407.0.0&from=s1.8-1-1.2)
[PassCet6]:https://github.com/wxzs5/WesternCom/blob/master/Photos/Running.PNG?raw=true

## Hardware
***
We mainly used following hardware build the car:<br>
* 1*Freescale K60 MCU
* 2*TSL1401CL CCD Camera(acquire track image)
* 2*Self-made PCBs(motor driver borad and signal processing board)
* 1*Competition committee provided type C car model
* 3*Phototube(detect stop line)
* 1*Gyroscope(detect ramp)
* 1*Battery
* 1*Steer Servo
* 2*Speed Encoder

![Car](https://github.com/wxzs5/WesternCom/blob/master/Photos/Car.jpg?raw=true)

## About The Code
***
The code is based on [vcan](http://www.vcan123.com/forum.php)'s K60 Library. We referred some code from LDPY(零度偏移)-a 2014 competition team from UESTC. Our almost written code in the folder /User. I also use Qt wrote a computer GUI program using serial port(Bluetooth) to interact with the car for debugging. You Can see in my other [repository](https://github.com/wxzs5/Car_View).

## Mainly Idea
***
### Get Track Information
We use CCD get gray-scale(8-bit) image, then we gained every row of image(actually this CCD only can get one line for each time). We can find the gray-scale value break position, this is the black line and white track's interface, this process is called **Binaryzation** .Finally average left break and right break we can get center position of the car. Then we can using PID control algorithm to drive steer eliminate car position error.

In the competition track has 6 status: straight line, big curve, little curve, ramp, obstacle and crossing road, these status are finite and have casual association. So we used all sensors' data implement a state-machine to judge the car ruing status.
