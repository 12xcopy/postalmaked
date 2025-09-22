hello. this is postalsauce / postalmaked.

this is a fork of Postal (1997). Check out the original

what is postalmaked:
    postalmaked is just the original postal source with CMake support, and other fixes.

what is postalsauce:
    saucy postal. postal with some bonuses

im planning on having sauce and maked be their own branches, postalmaked is gonna be as close to the original as possible, while postalsauce can have some experimental stuff.

the main goal of this project is to backport modern features to Postal, and convert most of the rendering systems to OpenGL.


building:
    Dependencies: SDL2

    if you're on linux, just make a directory 'build' and cd into it. then run 'cmake build ..', then 'make'.
    if you're on windows then good luck man. but cmake might work, im not sure how you'd get the deps though

running:
    you can run the compiled binary in your postal steam folder, or copy it into 'working' and run it there.
    theres a script 'run.sh' that could give you an idea