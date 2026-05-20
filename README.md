*This project has been created as part of the 42 curriculum by fhanuise, radib.*

# Cub3D

> My first RayCaster with miniLibX

![C](https://img.shields.io/badge/language-C-blue)
![42](https://img.shields.io/badge/school-42-black)
![norm](https://img.shields.io/badge/norminette-passing-brightgreen)

---

## Description

Cub3D is a 42 school project inspired by **Wolfenstein 3D**, the world's first FPS. The goal is to build a 3D first-person perspective renderer from a 2D map using the **raycasting** technique — a rendering method that casts rays from the player's viewpoint to calculate wall distances and simulate a 3D environment.

The project is implemented in C using the **miniLibX** graphics library provided by 42, and covers the following topics: ray-wall intersection math, texture mapping, map parsing and validation, and real-time keyboard input handling.

**Features:**
- 3D rendering via raycasting with perspective correction
- Distinct wall textures per orientation (North, South, East, West)
- Configurable floor and ceiling colors (RGB)
- Player movement (WASD) and camera rotation (arrow keys)
- Full `.cub` file parser with descriptive error messages
- Map validation: closed walls, valid characters, unique player spawn

---

## Instructions

### Requirements

- GCC or Clang
- Make
- X11 libraries (Linux):

```bash
sudo apt install libx11-dev libxext-dev
```

### Compilation

```bash
make        # build the project
make re     # full rebuild
make clean  # remove object files
make fclean # remove object files and binary
```

### Execution

```bash
./cub3D path/to/map.cub
```

The program takes exactly one argument: a `.cub` configuration file.

### Map file format

The `.cub` file must declare textures and colors before the map, which must always be last:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

11111111
10000001
1000N001
10000001
11111111
```

| Element | Description |
|---------|-------------|
| `NO` `SO` `WE` `EA` | Path to `.xpm` wall textures |
| `F` | Floor color as R,G,B |
| `C` | Ceiling color as R,G,B |
| `1` | Wall |
| `0` | Empty walkable space |
| `N` `S` `E` `W` | Player start position and facing direction |

Map rules: every walkable tile must be fully surrounded by walls. The map must be the last element in the file.

### Controls

| Key | Action |
|-----|--------|
| `W` / `Z` | Move forward |
| `S` | Move backward |
| `A` / `Q` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Quit |

---

## Resources

**Documentation & references:**
- [miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) — official 42 miniLibX guide
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the reference tutorial for raycasting in C
- [Wolfenstein 3D (Wikipedia)](https://en.wikipedia.org/wiki/Wolfenstein_3D) — original game that inspired this project
- [DDA Algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)) — line-drawing algorithm used for ray traversal

**AI usage:**

- Claude (Anthropic) was mainly used to speed up the documentation phase of the project and as a debugging tool
- No part of the project is AI only built, we always wrote the code ourselves