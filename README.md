# Doomukem Map Editor
## Introduction

The **DoomNukem Map Editor** is a custom level editor for a Doom-like game engine built in C. It allows users to create maps for use within the game, including defining walls, floors, ceilings and textures. Inspired by the classic game **DOOM**, this editor provides a simple interface for designing complex maps.

## Features

- **Create a layout
- **Texturing**: Assign textures to walls, floors, and ceilings.
- **Save Maps**: Export map data to .obj format.
  
## Installation

### Compiling

1. Clone the repository:
   ```bash
   git clone https://github.com/glecler/doom-nukem.git
   cd doom-nukem
   ```

2. Compile the project using `make`:
   ```bash
   make
   ```

3. Run the map editor:
   ```bash
   ./doom_editor
   ```

## Usage

Once the map editor is running, you can create new levels. The map editor starts in a 2D top-down view, where you can click to create floors.

### Basic Steps:
1. **Create Floors**: Click to place floor vertexes. The shapes are then automatically generated. You can then choose to connect either floor, wall or ceiling vertexes. 
3. **Assign Textures**: Select a texture from the texture menu and apply it to a segment.
4. **Export Map**: You can export the map by pressing `FILE` and then `EXPORT`.
