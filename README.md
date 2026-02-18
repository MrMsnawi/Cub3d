# cub3D

A 3D game engine built with raycasting, inspired by [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D). This project renders a first-person perspective inside a maze defined by a `.cub` map file, using the MinilibX graphics library.

## Features

- Real-time raycasting rendering at 1080×720
- Textured walls from `.xpm` files (NO, SO, WE, EA)
- Configurable floor and ceiling colors (RGB)
- Smooth player movement and rotation
- Wall collision detection
- Map validation (flood fill, element checks, enclosure verification)
- Custom garbage-collected memory management

## Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `ESC` | Quit |

## Requirements

- Linux (X11)
- `gcc` or `cc`
- `make`
- X11 development libraries (`libxext-dev`, `libx11-dev`)

Install dependencies on Debian/Ubuntu:
```sh
sudo apt install libxext-dev libx11-dev
```

## Build

```sh
make        # Build the project
make clean  # Remove object files
make fclean # Remove object files and binary
make re     # Full rebuild
```

## Usage

```sh
./cub3D path/to/map.cub
```

### Example

```sh
./cub3D maps/map.cub
```

## Map Format (`.cub`)

A `.cub` file defines textures, colors, and the map layout.

### Elements

| Identifier | Description | Format |
|------------|-------------|--------|
| `NO` | North wall texture | `NO path/to/texture.xpm` |
| `SO` | South wall texture | `SO path/to/texture.xpm` |
| `WE` | West wall texture | `WE path/to/texture.xpm` |
| `EA` | East wall texture | `EA path/to/texture.xpm` |
| `F` | Floor color | `F R,G,B` (0–255) |
| `C` | Ceiling color | `C R,G,B` (0–255) |

### Map Characters

| Char | Meaning |
|------|---------|
| `1` | Wall |
| `0` | Walkable space |
| `N` | Player start (facing North) |
| `S` | Player start (facing South) |
| `E` | Player start (facing East) |
| `W` | Player start (facing West) |

### Example Map

```
NO textures/NO.xpm
SO textures/SO.xpm
WE textures/WE.xpm
EA textures/EA.xpm

F 150,75,0
C 99,124,255

1111111111111111111111
1000000000000000000001
100000000000000E000001
1000000000000000000001
1000000000000000000001
1111111111111111111111
```

### Rules

- The map must be the last element in the file
- The map must be surrounded by walls (`1`)
- Exactly one player start position (`N`, `S`, `E`, or `W`)
- All six elements (NO, SO, WE, EA, F, C) are required, no duplicates
- Textures must be valid `.xpm` files

## Project Structure

```
├── main.c                  # Entry point, game loop, input handling
├── makefile
├── include/
│   └── cub.h               # Header with structs, prototypes, defines
├── parsing/
│   ├── elements.c           # Element validation (duplicates, missing)
│   ├── map.c                # Map loading, flood fill, character checks
│   ├── parse.c              # File reading and parsing entry point
│   ├── rgb.c                # Floor/ceiling color parsing
│   ├── textures.c           # Texture path parsing and loading
│   └── utils/               # Parsing helper functions
├── raycasting/
│   ├── init_data.c          # Player position and orientation setup
│   └── raycasting.c         # DDA raycasting, texture mapping, rendering
├── cub_lib/                 # Custom utility library (malloc, split, etc.)
├── mlx/                     # MinilibX graphics library
├── maps/                    # Example map files
└── textures/                # Wall texture files (.xpm)
```
