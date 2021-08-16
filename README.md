# sorting-algorithm-illustrator
This project demo 5 types of sorting algorithm into graphics,
written in C++ and using SFML libraries to realize graphical representation.
Types of sort algorithm in this demo:
1. Bubble Sort
2. Insertion Sort
3. Selection Sort
4. Merge Sort
5. Quick Sort

SortAlgo_illustrator.cpp is the main C++ source and two classes created:
- Engine.h contains an "Engine" class handles all algorithm computation and rendering.
- Button.h contains a "Button" class handles object created to represent button in GUI.
Data sample set size is set by size variable in main function. Current data set size is 30.
Random data is generated using rand() in C++ STL.

Directory
	-- project and source
		- SortAlgo_illustrator.cpp
		- Engine.h
		- Button.h
		...
	-- Release

Steps to access:
1. Select "Download ZIP" ![image](https://user-images.githubusercontent.com/87348560/129514145-cffe5a7d-0b2a-4861-9afd-c1c6ff9b65c1.png)
2. Go to "Release" folder and open .exe to view built application.
3. Go to "project and source" folder and open .sln with Visual Studio to view project and source files.
	*Please make sure "Solution Platform" is set to x86

In case you have any problem linking up SFML libraries, please refer to:
SFML and Visual Studio Setup Tutorial - https://www.sfml-dev.org/tutorials/2.5/start-vc.php

Some screenshots
Bubble Sort:
![image](https://user-images.githubusercontent.com/87348560/129514357-2efb2a09-80f6-49d4-9072-48546c0fd220.png)

Merge Sort:
![image](https://user-images.githubusercontent.com/87348560/129514275-9dec6785-c490-44ca-a002-2bc7cecdd084.png)

