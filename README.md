# CSnake

A classic Snake game implemented in C++ as a console application.

## Build Instructions

### Premake

The project uses Premake as the build system. Premake binaries exists in ```vendor\premake``` folder.

- To generate Visual Studio 2022 Solution on Windows run ```win_generate.bat```.
- To generate Make files on Unix run ```unix_generate.sh```.
- Feel free to use any other build system as you need using ```vendor/premake/<your-platform>/premake <supported-build-system>```, Look up Premake documentation for more details.

## Customizations

- You can Adjust the frame rate, width and height of the game board by editing this line in ```main.cpp``` folder.
```
Game* game = new Game(<width>, <height>, <fps>);
```
- Increasing the FPS results in smoother game play but eventually a higher moving speed, you may want to increase the width and height along with it. 

## Important Note

This project may or may not contain bugs. If you encounter issues, please report them, and contributions are welcome.

### To-Do List

- [ ] Make the game more colorful.
- [ ] Add the ability to specify width, height, and fps through a configuration file or command line arguments.

Feel free to contribute and improve the game!
