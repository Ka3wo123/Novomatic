#pragma once

#include <iostream>
#include <array>
#include <optional>
#include <vector>

template<typename T>
struct Data {
    T value;
    uint8_t count;
};


constexpr size_t sizeX{ 2 };
constexpr size_t sizeY{ 3 };

template<typename T>
using Array2D = std::array<std::array<T, sizeX>, sizeY>;

template<typename T>
using CompressedData = std::optional<std::vector<Data<T>>>;


template<typename T>
CompressedData <T> compressData(const Array2D<T>& input) {    
    std::vector<Data<T>> vec;

    for (int i = 0; i < sizeY; i++) {
        int currEl = input[i][0];
        int size = 1;
        Data<T> newData;

        for (int j = 0; j < sizeX - 1; j++) {
            if (input[i][j + 1] != currEl) {
                newData.value = currEl;
                newData.count = size;
                vec.push_back(newData);

                size = 1;
                currEl = input[i][j + 1];
            }
            else {
                size++;
            }
        }
        newData.value = currEl;
        newData.count = size;
        vec.push_back(newData);
    }

    return (vec.size() < sizeX * sizeY) ? CompressedData<T>{vec} : std::nullopt;
}




