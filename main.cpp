#include "Car.h"
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>

struct Print {
    void operator()(const Car& car) const {
        std::cout << "Name: " << car.getName() << "\tSpeed: " << car.getSpeed() << '\n';
    }
};

struct IsGreater {
    constexpr bool operator()(const Car& car) const {
        return car.getSpeed() > 280.0;
    }
};

/*
struct CompSpeed {
	constexpr bool operator()(const Car& lhs, const Car& rhs) const {
		return lhs.getSpeed() == rhs.getSpeed();
	}
};*/

struct BinOp {
    constexpr double operator()(const double lhs, const Car& rhs) const {
        return lhs + rhs.getSpeed();
    }
};

struct UnOp {
    constexpr double operator()(const Car& car) const {
        return car.getSpeed();
    }
};

struct Func {
    explicit Func(double mean) : m_mean(mean) {}
    constexpr double operator()(const double val) const {
        return val - m_mean;
    }
private:
    double m_mean;
};

int main() {
    std::mt19937 rng((uint32_t)std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> urd(200.0, 350.0);
    constexpr size_t SIZE = 3;

    Car carr[SIZE] = {
    Car("Audi", urd(rng)),
    Car("Mercedes", urd(rng)),
    Car("Porsche", urd(rng))
    };

    std::vector<Car> cars(carr, carr + sizeof(carr) / sizeof(carr[0]));


    std::cout << "1.\n";
    Print print;
    std::for_each(cars.begin(), cars.end(), print);


    std::cout << "\n2.\n";
    auto it = std::find_if(cars.begin(), cars.end(), IsGreater());
    if (it != cars.end()) {
        std::cout << "Found:\n";
        print(*it);
    }
    else {
        std::cout << "No match found\n";
    }


    std::cout << "\n3.\n";
    it = std::adjacent_find(cars.begin(), cars.end());
    if (it != cars.end()) {
        std::cout << "First of adjacent elements:\n";
        print(*it);
    }
    else {
        std::cout << "No adjacent elements found\n";
    }


    std::cout << "\n4.\n";
    std::cout << (std::equal(cars.begin(), cars.end(), carr)
        ? "The contents are equal\n" : "The contents differ\n");


    std::cout << "\n5.\n";
    it = std::search(cars.begin(), cars.end(), carr + 1, carr + SIZE);
    std::cout << "Subsequence found:\n";
    std::for_each(it, cars.end(), print);


    std::cout << "\n6.\n";
    double sum = std::accumulate(cars.begin(), cars.end(), 0.0, BinOp());
    double mean = sum / cars.size();
    std::cout << "Mean speed: " << mean << '\n';


    std::vector<double> v2(cars.size());
    std::transform(cars.begin(), cars.end(), v2.begin(), UnOp());


    std::transform(v2.begin(), v2.end(), v2.begin(), Func(mean));


    std::cout << "\nLast.\n";
    std::sort(v2.begin(), v2.end());
    std::cout << "Elements in ascending order:\n";
    std::for_each(v2.begin(), v2.end(), [](const double val) -> void {
        std::cout << val << " ";
    });
    std::cout << '\n';

    return 0;
}