#include <iostream>
#include <random>
#include "Compress/Compress.hpp"

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> draw(0, 10);

	Array2D<int> arr;

	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			arr[i][j] = draw(gen);
		}
	}	

	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			std::cout << arr[i][j] << " ";
		}
		std::cout << "\n";
	}

	CompressedData<int> res = compressData(arr);

	if (res.has_value()) {
		std::cout << "{";					
			for (auto& data : res.value()) {
				std::cout << "{" << data.value << "," << static_cast<int>(data.count) << "},";
			}				
		std::cout << "}\n";
	}
	else {
		std::cout << "Compression has larger size than original array\n";
	}

	std::cout << "Press Enter to exit...";
	std::cin.get();
}
