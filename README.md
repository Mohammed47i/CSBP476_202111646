# Line Following Robot – Group 2

This is our final project for the Robotics and Intelligent Systems course at UAEU. In this project, we built a small mobile robot that can follow a black line on its own — no remote control needed. The robot reads the path using sensors and makes real-time decisions to stay on track.

---

## About the Project

We were tasked with building a robot that could complete a course by following a black line. The robot needed to move smoothly, handle turns, and stop when it reached the end. We used a 4-wheel drive robot kit controlled by an Arduino, and we wrote code that helps it understand where the line is and how to react.

This project was completed during **Spring 2025** as part of the CSPB476 course.

---

## Meet the Team – Group 2

- Abdullah Al Amoodi – 202119525  
- Fadel Al Shamsi – 202102655  
- Khalifa Al Dhaheri – 202103159  
- Mohammed Al Nuaimi – 202111646  
- Obaid Alkaabi – 202102854  

**Instructor:** Dr. Munkhjargal Gochoo  
**University:** United Arab Emirates University

---

## What We Used

Our robot was built using:

- An Arduino board (ATmega328P)
- A 4-wheel drive car chassis from Keyestudio
- 3 infrared sensors to detect the line
- 4 DC motors (2 on each side)
- A motor driver to control speed and direction
- A power supply for mobility
- 
<img width="375" alt="image" src="https://github.com/user-attachments/assets/d188299c-8518-460e-a609-21e74421abc9" /> <img width="391" alt="image" src="https://github.com/user-attachments/assets/e775eacc-ace7-4753-be56-e5a72b31c4d3" />


---

## How the Robot Works

The robot is always checking what the sensors detect underneath it:

- If the center sensor sees the line → go forward.
- If the line is more on the left → turn left.
- If it’s more on the right → turn right.
- If the line disappears completely → stop.

This happens continuously so the robot can follow the path accurately and adjust its movement as needed.
Flowchart 
<img width="367" alt="image" src="https://github.com/user-attachments/assets/b2b275dd-62a9-403d-9a91-4b4577a8d4e6" />


---

## See It in Action

We recorded a short demo of the robot in action:

**Line Following Video:**  
[Watch on YouTube](https://youtube.com/shorts/pLUg5A0LoIw?feature=share)

**Obstacle Avoidance Video:**  
[Watch on YouTube](https://youtube.com/shorts/XBXTdoTMkBw)

---

## What’s in the Code

We wrote functions to control how the robot moves based on the sensors:

- `front()` – move forward
- `left()` – turn left
- `right()` – turn right
- `back()` – reverse if it goes off track
- `stop()` – stop all movement
- `tracking()` – ties it all together and makes decisions based on sensor input

The full code is available in the `code/` folder of this repository.

---

## What We Learned

We learned a lot from this project, including:

- How to work with sensors and motors
- How to use Arduino for real-time decision making
- How to troubleshoot problems and work as a team

We also learned how small adjustments in logic and motor control can make a big difference in performance.

---

## References

Here are some of the resources we used:

- [Keyestudio Wiki](https://wiki.keyestudio.com)
- [Arduino Code Guide](https://www.arduinogetstarted.com)
- [ATmega328P Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)

---

## A Note About the Code

This project was built for academic purposes at UAEU. Feel free to check out the code and build your own version.

Thanks for visiting!
