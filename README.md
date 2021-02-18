# SomeFrickinMediocreLemons
My personal favorite explication for SFML.

This project is about a yet-unnamed card game.
It is, as the name implies, built using only the SFML and standard c++ library.
To build this, you'll first need to install SFML. 
You will also need the assets to run this properly, which i couldn't be bothered to make public,
so expect a bunch of error messages about missing files and a pretty empty window when running.
To install SFML, just follow the how-to here: www.sfml-dev.org/  
CMake is already integrated, to build it simply clone/download the repo and run the following in a terminal:

cd \<path-of-project\>  
mkdir Build  
cd Build  
cmake ..  
make  

This will create an executable called main, which can simply be run using "./main.cpp" in the Build directory.
Behaviour withour any assets is mostly untestet though.