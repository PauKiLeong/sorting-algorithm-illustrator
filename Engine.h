#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
#include "Button.h"
#include <iostream>
#include <string>

struct data {
	float h = 0;
	float p = 0;
};

class Engine
{
protected:
	// variables
	sf::Event m_event;
	sf::Vector2i m_mousePOS = { 0,0 };
	sf::Vector2f m_mousePOSView = { 0,0 };
	sf::Text m_text;
	sf::RectangleShape m_bar;
	Button BubbleSort;
	Button InsertionSort;
	Button SelectionSort;
	Button MergeSort;
	Button QuickSort;
	Button Return;

	// state
	// 0 = initialize
	// 1 = sorting
	int state = 0;

public:
	// Constructor & Destructor
	Engine()
	{
		state = 0;
		m_mousePOS = { 0,0 };
		m_mousePOSView = { 0,0 };
		//std::cout << "Engine Constructor" << std::endl;
		if (!m_font.loadFromFile("Font/calibri-regular.ttf"))
			std::cout << "Error: Failed to load font! " << std::endl;
		initButton();
	}
	virtual ~Engine()
	{
		//std::cout << "Engine Destructor" << std::endl;
	}
	void setState(const int& main_state)
	{
		state = main_state;
	}
	int getState()
	{
		return state;
	}

	// Variables
	sf::Font m_font;
	//static const int m_count = 100;
	//data m_line[m_count];

	// Public Functions
	void pollEvent(sf::RenderWindow& win1, data *arr, const int& size)
	{
		getMousePOS(win1);
		// event polling
		while (win1.pollEvent(m_event))
		{
			// event type
			switch (m_event.type)
			{
			case sf::Event::Closed: // close button pressed
				win1.close();
				break;
			case sf::Event::KeyPressed: // Escape pressed
				if (m_event.key.code == sf::Keyboard::Escape)
					win1.close();
				break;
				
			case sf::Event::MouseButtonPressed:
				if (BubbleSort.isPressed(m_mousePOSView))
				{
					setState(1);
					f_BubbleSort(arr, size, win1);
				}
				if (InsertionSort.isPressed(m_mousePOSView))
				{
					setState(1);
					f_InsertionSort(arr, size, win1);
				}
				if (SelectionSort.isPressed(m_mousePOSView))
				{
					setState(1);
					f_SelectionSort(arr, size, win1);
				}
				if (MergeSort.isPressed(m_mousePOSView))
				{
					setState(1);
					f_MergeSort(win1, arr, size, 0, size-1);
				}
				if (QuickSort.isPressed(m_mousePOSView))
				{
					setState(1);
					f_QuickSort(win1, arr, size, 0, size - 1);
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (Return.isPressed(m_mousePOSView))
						setState(0); 
				}
				break;
			}
		}
	}

	void pollSorting(sf::RenderWindow& win1)
	{
		getMousePOS(win1);
		// event polling
		while (win1.pollEvent(m_event))
		{
			// event type
			switch (m_event.type)
			{
			case sf::Event::Closed: // close button pressed
				win1.close();
				break;
			case sf::Event::KeyPressed: // Escape pressed
				if (m_event.key.code == sf::Keyboard::Escape)
					win1.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (Return.isPressed(m_mousePOSView))
						setState(0);
				}
				break;
			}
		}
	}

	void renderInit(sf::RenderWindow& win1)
	{
		/*
		* clear old frame
		* render initial interface
		* display new frame
		*/
		win1.clear(sf::Color(50, 50, 50, 1)); // clear old frame
		// draw content here
		BubbleSort.renderButton(win1);
		InsertionSort.renderButton(win1);
		SelectionSort.renderButton(win1);
		MergeSort.renderButton(win1);
		QuickSort.renderButton(win1);
		win1.display(); // done drawing
	}

	void renderSort(sf::RenderWindow& win1, const int& size, data *arr, const float& width, const int& current_id, const bool& BS)
	{
		/*
		* clear old frame
		* render sorting algorithm
		* display new frame
		*/
		bool highlight = false;
		pollSorting(win1);
		win1.clear(sf::Color(50, 50, 50, 1)); // clear old frame
		// draw content here
		Return.renderButton(win1);
		for (int id = 0; id < size; id++)
		{
			highlight = false;
			if (BS) // only highlight 2 when bubblesort
			{
				if (id == current_id || id == current_id + 1)
					highlight = true;
			}
			else
			{
				if (id == current_id)
					highlight = true;
			}
			initBar(arr, id, width, highlight);
			win1.draw(m_bar);
		}
		win1.display();
	}

	void renderQS(sf::RenderWindow& win1, const int& size, data* arr, const float& width, const int& head_id, const int& tail_id, const int& current_id, const bool& swap)
	{
		// Color Switch
		// 1 = Cyan; 2 = Red; 3 = Green
		int ColorSW = 0;
		pollSorting(win1);
		win1.clear(sf::Color(50, 50, 50, 1)); // clear old frame
		// draw content here
		Return.renderButton(win1);
		for (int id = 0; id < size; id++)
		{
			initQSBar(arr, id, width, 0);
			if (id >= head_id && id <= tail_id)
				initQSBar(arr, id, width, 1);
			if (id == current_id)
				initQSBar(arr, id, width, 2);
			if (swap && (id == current_id || id==tail_id)) // highlight green for pivot position and tail element
				initQSBar(arr, id, width, 3);
			win1.draw(m_bar);
		}
		win1.display();
		//if (current_id < head_id | current_id > tail_id)
			//std::cout << " out of scope " << std::endl;
	}

protected: // Private Functions
	// Text
	void initText(const std::string& msg)
	{
		m_text.setFont(m_font);
		m_text.setCharacterSize(20);
		m_text.setFillColor(sf::Color::Blue);
		m_text.setPosition(447.f,5.f);
		m_text.setString(msg);
	}
	void updateText(const std::string& msg)
	{
		m_text.setString(msg);
	}
	void renderText(sf::RenderTarget& target)
	{
		target.draw(m_text);
	}

	// Button
	void initButton()
	{
		const int line = 150;
		BubbleSort.setName("Bubble Sort");
		BubbleSort.setPosition(sf::Vector2f(line-60,100));
		BubbleSort.updateButton();

		InsertionSort.setName("Insertion Sort");
		InsertionSort.setPosition(sf::Vector2f((2*line)-60, 100));
		InsertionSort.updateButton();

		SelectionSort.setName("Selection Sort");
		SelectionSort.setPosition(sf::Vector2f((3*line)-60, 100));
		SelectionSort.updateButton();

		MergeSort.setName("Merge Sort");
		MergeSort.setPosition(sf::Vector2f((4*line)-60, 100));
		MergeSort.updateButton();

		QuickSort.setName("Quick Sort");
		QuickSort.setPosition(sf::Vector2f((5*line)-60, 100));
		QuickSort.updateButton();

		Return.setName("Return to Main Menu");
		Return.setPosition(sf::Vector2f(360, 10));
		Return.updateButton();
	}

	// rectangle bar
	void initBar(data *arr, const int& id, const float& width, const bool& highlight)
	{
		m_bar.setFillColor(sf::Color::Cyan);
		if (highlight)
			m_bar.setFillColor(sf::Color::Green);
		m_bar.setOutlineColor(sf::Color::Black);
		m_bar.setOutlineThickness(2.f);
		m_bar.setSize(sf::Vector2f(width, arr[id].h));
		m_bar.setPosition(arr[id].p+width,590);
		m_bar.setRotation(180);
	}
	void initQSBar(data* arr, const int& id, const float& width, const int& ColorSW)
	{	// Color Switch
		// 1 = Cyan; 2 = Red; 3 = Green
		m_bar.setFillColor(sf::Color::White);
		switch (ColorSW)
		{
		case 1:
			m_bar.setFillColor(sf::Color::Cyan);
			break;
		case 2:
			m_bar.setFillColor(sf::Color::Red);
			break;
		case 3:
			m_bar.setFillColor(sf::Color::Green);
			break;
		}
		m_bar.setOutlineColor(sf::Color::Black);
		m_bar.setOutlineThickness(2.f);
		m_bar.setSize(sf::Vector2f(width, arr[id].h));
		m_bar.setPosition(arr[id].p+width, 590);
		m_bar.setRotation(180);
	}

	void getMousePOS(sf::RenderWindow& win1)
	{
		//internal function: get mouse position relative to the position of window created
		sf::Vector2u winSize = win1.getSize();
		m_mousePOS.x = sf::Mouse::getPosition(win1).x;
		m_mousePOS.y = sf::Mouse::getPosition(win1).y;
		m_mousePOSView = win1.mapPixelToCoords(m_mousePOS);
		if (m_mousePOSView.x < 0 || m_mousePOSView.y < 0 || m_mousePOSView.x > winSize.x || m_mousePOSView.y > winSize.y) {
			//std::cout << "Mouse position: " << "Cursor is out of window" << std::endl;
		}
		else {
			//std::cout << "Mouse position: " << m_mousPOSView.x << " " << m_mousPOSView.y << std::endl;
		}
	}

	bool delayswitch() // delay for 30 milliseconds
	{
		sf::Clock clock; // starts the clock
		sf::Time elapsed = clock.getElapsedTime();
		while (elapsed.asMilliseconds() < 100)
		{
			elapsed = clock.getElapsedTime(); // update elapsed time
		}
		//std::cout << "Time is " << elapsed.asMicroseconds() << std::endl;
		//clock.restart();
		return true;
	}

	void swap(float *a, float *b)
	{
		float temp=0;
		temp = *a;
		*a = *b;
		*b = temp;
	}

	void f_BubbleSort(data* arr, const int& size, sf::RenderWindow& win1) 
	{
		float width = win1.getSize().x / size;
		for (int pass = 0; pass < size - 1; pass++) 
		{
			for (int j = 0; j < size - pass - 1; j++) 
			{
				if (state != 1)
					break;
				// process pair of numbers
				if (arr[j].h > arr[j + 1].h) 
				{ // swapping
					swap(&arr[j + 1].h, &arr[j].h);
					//float temp = arr[j + 1].h;
					//arr[j + 1].h = arr[j].h;
					//arr[j].h = temp;
					if (delayswitch())
						renderSort(win1, size, arr, width, j, true);
				}
			}
		}
		renderSort(win1, size, arr, width, -2, true);
	}

	void f_InsertionSort(data* arr, const int& size, sf::RenderWindow& win1) 
	{
		/*
		* Start from 1 as key, until n-1
		* if key < LHS element, move element to right;
		* until key > LHS element, insert key
		* Takes O(n^2) time and O(1) space.
		*/
		float width = win1.getSize().x / size;
		for (int i = 1; i < size; i++)
		{
			int j = i - 1;
			data key = arr[i];
			while (j >= 0 && arr[j].h > key.h)
			{
				if (state != 1)
					break;
				arr[j + 1].h = arr[j].h;
				arr[j].h = key.h;
				if (delayswitch())
					renderSort(win1, size, arr, width, j, false);
				j--;
			}
			if (state != 1)
				break;
			arr[j + 1].h = key.h;
			if (delayswitch())
				renderSort(win1, size, arr, width, j+1, false);
		}
		renderSort(win1, size, arr, width, -2, false);
	}

	void f_SelectionSort(data* arr, const int& size, sf::RenderWindow& win1)
	{
		/*
		* Find and sort the min. element among (unsorted part) to (sorted part) in each iteration
		* start from left-one position of unsorted part as first min. element
		* Takes O(n^2) time and O(1) space
		*/
		float width = win1.getSize().x / size;
		int min_id = 0;
		for (int i = 0; i < size - 1; i++) // 0~n-2
		{
			min_id = i;
			if (state != 1)
				break;
			for (int j = i + 1; j < size; j++) // 1~n-1
			{
				if (arr[j].h < arr[min_id].h)
				{
					min_id = j;
					if (delayswitch())
						renderSort(win1, size, arr, width, min_id, false);
				}
			}
			if (min_id != i) // only swap when smallest element, arr[min_id], is not arr[i]
			{
				swap(&(arr[min_id].h), &(arr[i].h));
				if (delayswitch())
					renderSort(win1, size, arr, width, i, false);
			}
		}
		renderSort(win1, size, arr, width, -2, false);
	}

	void merge(data *arr, const int& size, const int& mid_id, const int& head_id, const int& tail_id, sf::RenderWindow& win1, const float& width)
	{
		/*
		* 1) create temporary array
		* 2) compare and assign, [head:mid] vs [mid+1:tail]
		* 3) update original array with temp array value
		*/
		data *temp_arr = new data[size];
		int left_index = head_id;  // head:mid
		int right_index = mid_id + 1; // mid+1:tail
		int new_index = head_id; // head:tail

		// compare when left and right both are not done
		while (left_index <= mid_id && right_index <= tail_id)
		{
			if (state != 1)
				break;
			if (arr[left_index].h <= arr[right_index].h)
			{
				temp_arr[new_index].h = arr[left_index].h;
				left_index++;
			}
			else
			{
				temp_arr[new_index].h = arr[right_index].h;
				right_index++;
			}
			new_index++;
		}
		// compare when right are done
		while (left_index <= mid_id)
		{
			if (state != 1)
				break;
			temp_arr[new_index].h = arr[left_index].h;
			left_index++;
			new_index++;
		}
		// compare when left are done
		while (right_index <= tail_id)
		{
			if (state != 1)
				break;
			temp_arr[new_index].h = arr[right_index].h;
			right_index++;
			new_index++;
		}

		// update original array
		for (int index = head_id; index < tail_id + 1; index++)
		{
			if (state != 1)
				break;
			arr[index].h = temp_arr[index].h;
			if (delayswitch())
				renderSort(win1, size, arr, width, index, false);
		}
		// release memory
		//temp_arr = nullptr;
		delete[] temp_arr;
	}

	void f_MergeSort(sf::RenderWindow& win1, data* arr, const int& size, const int& head_id, const int& tail_id)
	{
		/*
		* 1) compute middle element, m
		* 2) split array[head:tail] to array[head:m] and array[m+1:tail]
		* 3) recursively split array until array become array[a:a], which is the base case
		* 4) start merging and sort until array[head:tail] is returned
		* Takes  O(n lg n) time
		*/
		float width = win1.getSize().x / size;
		if (head_id < tail_id && state == 1) // loop until head=tail
		{
			int m = (head_id + tail_id) / 2;
			f_MergeSort(win1, arr, size, head_id, m);
			f_MergeSort(win1, arr, size, m+1, tail_id);
			merge(arr, size, m, head_id, tail_id, win1, width);
			renderSort(win1, size, arr, width, -2, false);
		}
	}

	int partition(sf::RenderWindow& win1, data *arr, const int& size, const float& width, const int& head_id, const int& tail_id)
	{
		//int pivot = arr[tail_id].h; // select last element as pivot
		int pivot_position = head_id; // start with head_id
		for (int i = head_id; i < tail_id + 1; i++)
		{
			if (state != 1)
				break;
			if (arr[i].h < arr[tail_id].h) // if current value smaller than pivot value
			{
				swap(&arr[i].h, &arr[pivot_position].h); // this will move smaller element to left
				renderQS(win1, size, arr, width, head_id, tail_id, pivot_position, false);
				pivot_position++;
			}
		}
		if (tail_id != pivot_position && state==1) // skip cases of pivot = tail
		{
			// here mark when pivot_position is finished compute
			// highlight swapping element as red
			renderQS(win1, size, arr, width, head_id, tail_id, pivot_position, true);
			delayswitch(); delayswitch(); delayswitch();
			// swapping
			swap(&arr[tail_id].h, &arr[pivot_position].h); // swap pivot(last element) to pivot_position
			renderQS(win1, size, arr, width, head_id, tail_id, -2, false);
		}
		return pivot_position;
	}

	void f_QuickSort(sf::RenderWindow& win1, data* arr, const int& size, const int& head_id, const int& tail_id)
	{
		/*
		* 1) Pick pivot (last element in this case)
		* 2) Partition array into "(A)smaller than pivot ; pivot ; (B)bigger than pivot"
		* 3) Recurssively sort A and B parts
		* Takes O(n^2) worst case time, O(n lg n) average timing
		*/
		float width = win1.getSize().x / size;
		if (head_id < tail_id && (tail_id - head_id)>1 && state==1)
		{
			int pivot_id = partition(win1, arr, size, width, head_id, tail_id);
			f_QuickSort(win1, arr, size, 0, pivot_id - 1); // 0 ~ pivot
			f_QuickSort(win1, arr, size, pivot_id + 1, tail_id); // pivot+1 ~ last element
		}
		if (tail_id - head_id == 1) // if range is only 2, e.g. 0~1
		{
			if (arr[head_id].h > arr[tail_id].h)
			{
				swap(&arr[head_id].h, &arr[tail_id].h);
			}
			renderQS(win1, size, arr, width, head_id, tail_id, tail_id, false);
		}
		renderSort(win1, size, arr, width, -2, false);
	}
};

