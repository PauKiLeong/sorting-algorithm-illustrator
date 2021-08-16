// SortAlgo_illustrator.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include "Engine.h"

void initData(data *arr, const int& size, sf::Vector2u& winSize);

int main()
{
    // window and engine
    const int winH = 600;
    const int winW = 900;
    sf::RenderWindow window(sf::VideoMode(winW, winH), "Sorting Algorithm Illustrator", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    Engine program_engine;

    // data and algorithm
    const int size = 30;
    data arr[size];
    sf::Vector2u winSize = window.getSize();
    
    // main loop. isOpen() returns a bool value
    while (window.isOpen()) {
        program_engine.pollEvent(window, arr, size);
        if (program_engine.getState() == 0) // initial state
        {
            initData(arr, size, winSize);
            program_engine.renderInit(window);
        }
        else if (program_engine.getState() == 1) // sorting state
        {
            // sorting
        }
        else
        {
            program_engine.setState(0);
        }
    }
    //system("pause");
}

void initData(data *arr, const int& size, sf::Vector2u& winSize)
{
    // generate random data set; assign random number between 0~99
    for (int i = 0; i < size; i++)
    {
        arr[i].h = rand() % (winSize.y-100);
        arr[i].p = i * (winSize.x/size);
    }
}