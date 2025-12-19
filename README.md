🚀 SPACE INVADER – 2D Arcade Shooter Game

Name: Palli Ritvik
Roll Number: 240150023
Language: C++
Graphics Library: SFML

📌 Project Overview

Space Invader is a 2D top-down arcade shooter game developed using C++ and SFML.
The player controls a ground-based cannon and must destroy enemy planes flying across the screen while avoiding falling bombs. The game focuses on real-time action, energy management, and score optimization.

This project demonstrates fundamental game development concepts, including event handling, collision detection, object-oriented design, and rendering using SFML.

🎮 Game Features

2D top-down arcade shooter gameplay

Player-controlled cannon with left/right movement

Shooting bullets to destroy enemy planes

Enemy planes drop bombs randomly

Energy-based health system (starts at 100%)

Energy reduces on bomb impact

Score increases by destroying enemies

Game ends when energy reaches zero

Simple and smooth difficulty progression

🕹️ Controls
Action	Key
Move Left	Left Arrow
Move Right	Right Arrow
Shoot	Spacebar / Up Arrow
Exit	Close Window
🔋 Energy System

Player starts with 100% energy

Each bomb hit reduces energy by 20%

Energy bar visually displays remaining energy

Game ends when energy reaches 0%

This system provides smoother difficulty scaling compared to fixed lives.

🧠 Game Architecture

The project follows an Object-Oriented Programming (OOP) approach.

Key Classes:

Game (main loop) – Handles rendering, events, and updates

Player – Manages movement, shooting, and energy

Enemy – Controls plane movement and bomb dropping

Bullet – Handles bullet movement and collision

Bomb – Handles bomb falling and collision

🛠️ Technologies Used

C++ (C++17 standard)

SFML (Simple and Fast Multimedia Library)

Object-Oriented Programming

2D Graphics Rendering

Event-Driven Game Loop
