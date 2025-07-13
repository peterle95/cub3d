# cub3d - 3D Raycasting Engine

A simple 3D raycasting engine inspired by Wolfenstein 3D, built using the miniLibX graphics library.

## Overview

cub3d is a first-person perspective maze game where players navigate through a 3D environment rendered using raycasting techniques. The project implements fundamental principles of computer graphics, including:

- Raycasting rendering
- Texture mapping
- Player movement and rotation
- Wall collision detection
- Minimap visualization

## Features

- First-person 3D navigation in a maze
- Textured walls, floors, and ceilings
- Collision detection system
- Configurable maps using simple text files
- Keyboard controls for movement and camera rotation
- Screenshot capability

## Installation

### Prerequisites
- GCC compiler
- Make
- X11 development libraries
- miniLibX library

### Building
```bash
git clone https://github.com/peterle95/cub3d.git
cd cub3d
make
```

## Usage

```bash
./cub3d maps/map.cub
```

### Map Format

Maps are defined in `.cub` files with the following elements:
- `R` - Screen resolution
- `NO`, `SO`, `WE`, `EA` - Path to wall textures
- `F`, `C` - Floor and ceiling colors
- Map layout using characters:
  - `0` - Empty space
  - `1` - Wall
  - `N`, `S`, `E`, `W` - Player starting position and orientation

Example map:
```
R 1920 1080
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

11111111
10000001
10N00001
10000001
10000001
10000001
11111111
```

## Controls

- `W`, `A`, `S`, `D` - Move player
- Left/Right arrow keys - Rotate camera
- `ESC` - Exit game
- `Space` - Take screenshot

## Implementation Details

- Written in C
- Uses miniLibX for graphics rendering
- Ray casting algorithm for 3D perspective
- DDA (Digital Differential Analysis) for ray calculations

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgements

- Inspired by Wolfenstein 3D and the raycasting techniques developed by id Software
- Based on the 42 School curriculum project specifications
