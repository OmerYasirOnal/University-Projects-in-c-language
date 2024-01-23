/**
* @file vector.cpp
* @description Bu sınfı Vector sınıfının metodlarının tanımlarını içerir.
* @assignment 2. Proje
* @date 03.12.2020
* @author Ömer Yasir Önal omeryasir.onal@stu.fsm.edu.tr
*/
#include "vector.h"
#include <stdexcept>

// Constructor
Vector::Vector(size_t size) : size(size), elements(new Complex[size]) {}

// Copy constructor
Vector::Vector(const Vector& other) : size(other.size), elements(new Complex[other.size]) {
    for (size_t i = 0; i < size; ++i) {
        elements[i] = other.elements[i];
    }
}

// Destructor
Vector::~Vector() {
    delete[] elements;
}


Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] elements;
        size = other.size;
        elements = new Complex[size];
        for (size_t i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }
    return *this;
}

// Erisim operatorleri
Complex& Vector::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return elements[index];
}


// Aritmatik islemler
Vector Vector::operator+(const Vector& other) const {
    if (size != other.size) {
        throw std::runtime_error("Vector sizes do not match");
    }
    Vector result(size);
    for (size_t i = 0; i < size; ++i) {
        result[i] = elements[i] + other.elements[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (size != other.size) {
        throw std::runtime_error("Vector sizes do not match");
    }
    Vector result(size);
    for (size_t i = 0; i < size; ++i) {
        result[i] = elements[i] - other.elements[i];
    }
    return result;
}

Vector& Vector::operator+=(const Vector& other) {
    if (size != other.size) {
        throw std::runtime_error("Vector boyutları eşit değil");
    }
    for (size_t i = 0; i < size; ++i) {
        elements[i] += other.elements[i];
    }
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    if (size != other.size) {
        throw std::runtime_error("Vector boyutları eşit değil");
    }
    for (size_t i = 0; i < size; ++i) {
        elements[i] -= other.elements[i];
    }
    return *this;
}

Complex Vector::dot(const Vector& other) const {
    if (size != other.size) {
        throw std::runtime_error("Vector boyutları eşit değil");
    }
    Complex result;
    for (size_t i = 0; i < size; ++i) {
        result += elements[i] * other.elements[i];
    }
    return result;
}

Vector& Vector::operator*=(const Vector& other) {
    Complex result = this->dot(other);
    for (size_t i = 0; i < size; ++i) {
        elements[i] = result;
    }
    return *this;
}

bool Vector::operator==(const Vector& other) const {
    if (size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (elements[i] != other.elements[i]) {
            return false;
        }
    }
    return true;
}

size_t Vector::getSize() const {
    return size;
}

void Vector::setSize(size_t size) {
    delete[] elements;
    this->size = size;
    elements = new Complex[size];
}

