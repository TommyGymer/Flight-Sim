# C++
###### to be read using [Obsidian](https://obsidian.md/)
---
### Setting up a development environment

Following an [OpenGL in C++](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/) tutorial which covers OpenGL 3/4
- IDE: Visual Studio
- Compiler: CMake
- Libraries (beyond built-ins):
	- OpenGL

The tutorial contains guides and examples of all the concepts I will need to implement the 3D renderer for the sim. The only concept not covered is bones, which I want to use for the movable flight surfaces to remove the need for linked objects.

The use of the .obj format and bones will make it easy to load a different file and make use of a different aircraft.

### "Hello, World!"
---
Starting a program in C++ is accomplished using
```C++
int main(void){
	return 0;
}
```

This defines a method `main` with no parameters which returns an int; the returned int is 0 if the program returns with no errors

# Why would anyone do this to themselves

# Time to leave