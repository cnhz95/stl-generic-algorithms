#include "Car.h"

Car::Car(std::string&& name, double speed) : m_name(std::move(name)), m_speed(speed) {}

bool Car::operator==(const Car& rhs) const {
    return m_name == rhs.m_name;
}

std::string Car::getName() const {
    return m_name;
}

double Car::getSpeed() const {
    return m_speed;
}