/*функция ограничиващая значения в задднном диапазоне*/


#include <iostream>

template <typename T>
constexpr const T& clamp(const T& value, const T& low, const T& high) {
    return (value < low) ? low : (value > high) ? high : value;
}