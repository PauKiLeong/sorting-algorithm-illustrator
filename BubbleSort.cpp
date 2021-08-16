#pragma once
namespace algorithm {
	void BubbleSort(data* bar[], const int& size) {
		for (int i = 0; i < size; i++)
		{
			std::cout << bar[i]->height << " ";
		}
		for (int pass = 0; pass < size - 1; pass++) {
			for (int j = 0; j < size - pass - 1; j++) {
				// process pair of numbers
				//if (delaypipe()) { // delay some time with a cycle counter
				if (bar[j]->height > bar[j + 1]->height) {
					// swapping
					int temp = bar[j + 1]->height;
					bar[j + 1]->height = bar[j]->height;
					bar[j]->height = temp;
				}
				//}

			}
		}
	}
}



