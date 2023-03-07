#ifndef STL_GENERIC_ALGORITHMS_CAR_H
#define STL_GENERIC_ALGORITHMS_CAR_H

#include <string>

class Car {
public:
    Car() = default;
    Car(std::string&& name, double speed);
    bool operator==(const Car& rhs) const;

    std::string getName() const;
    double getSpeed() const;

private:
    std::string m_name;
    double m_speed;
};

#endif