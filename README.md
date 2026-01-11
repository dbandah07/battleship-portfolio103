# Portfolio: Battleship

## Overview
This program is a **text-based implementation of the classic game Battleship for the course: Introduction to Programming** written in C++.  
It supports **Two-Player mode (PvP)**, handling ship placement, turn-based attacks, hit/miss tracking, and win detection through console interaction.

The project emphasizes **object-oriented design, game-state management, and modular C++ architecture**, separating responsibilities across classes for the board, players, and ships.

## Features
- Game mode:
  - **Two-Player (PvP)**
- Turn-based gameplay with repeated attacks on hits (miss ends the turn)
- Ship placement with validation:
  - Bounds checking
  - Length checking per ship type
  - Collision checking (no overlapping ships)
  - Horizontal/vertical orientation support
- Board rendering with clear symbols:
  - `S` = ship (revealed only on your own board)
  - `*` = open water (placement view)
  - `.` = unknown (fog of war)
  - `X` = hit ship
  - `O` = miss
- Ship system using inheritance/polymorphism:
  - `Ship` base class
  - `Small`, `Med`, `Large` ship types with different sizes
 
## Notes
Completed during Spring 2025. 
