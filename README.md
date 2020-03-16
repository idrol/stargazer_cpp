# Discontinued project
Assets and dependencies are missing due to file size issues

My personal game engine project.
[Imgur album](https://imgur.com/a/7JU3NqY)

# Render engine
The render engine uses physically based lighting and is based on code from [Learn OpenGL](https://learnopengl.com/PBR/Theory).  
The render engine runs on its own seperate thread and accepts pre programmed commands to be submitted to the rendering engine or opengl calls in a custom command.  
It also includes a basic post processing pipeline which can be used to implement bloom and gaussian blur.

# WIP features

## Editor
The editor provides a basic interface to manipulate and design a game level.
The editor ui uses ImGui as a ui framework.

## Scripting
The scripting is very basic at the moment only allowing to change transform properties of game objects.

## Physics
Physics is implemented using the [Bullet](https://github.com/bulletphysics/bullet3) physics library. 