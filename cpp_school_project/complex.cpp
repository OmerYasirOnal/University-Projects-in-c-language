/**
* @file complex.cpp
* @description Complex ve Imaginary sınıfının metodlarının tanımlarını içerir.
* @assignment 2. Proje
* @date 03.12.2020
* @author Ömer Yasir Önal omeryasir.onal@stu.fsm.edu.tr
*/

#include "complex.h"

// Imaginary sınıfı metodları
Imaginary::Imaginary(double im) : im(im) {}

double Imaginary::getImaginary() const {
    return im;
}

void Imaginary::setImaginary(double im) {
    this->im = im;
}

// Complex sınıfı metodları
Complex::Complex(double re, double im) : Imaginary(im), re(re) {}

double Complex::getReal() const {
    return re;
}

void Complex::setReal(double re) {
    this->re = re;
}

Complex Complex::operator+(const Complex &other) const {
    return Complex(re + other.re, getImaginary() + other.getImaginary());
}

Complex Complex::operator-(const Complex &other) const {
    return Complex(re - other.re, getImaginary() - other.getImaginary());
}

Complex Complex::operator*(const Complex &other) const {
    double newRe = re * other.re - getImaginary() * other.getImaginary();
    double newIm = re * other.getImaginary() + getImaginary() * other.re;
    return Complex(newRe, newIm);
}

Complex Complex::operator/(const Complex &other) const {
    double denominator = other.re * other.re + other.getImaginary() * other.getImaginary();
    if (denominator == 0) {
        throw std::runtime_error("Sıfıra bölme hatası");
    }
    double newRe = (re * other.re + getImaginary() * other.getImaginary()) / denominator;
    double newIm = (getImaginary() * other.re - re * other.getImaginary()) / denominator;
    return Complex(newRe, newIm);
}

Complex Complex::operator~() const {
    return Complex(re, -getImaginary());
}
Complex& Complex::operator=(const Complex &other) {
    re = other.re;
    setImaginary(other.getImaginary());
    return *this;
}

bool Complex::operator==(const Complex &other) const {
    return re == other.re && getImaginary() == other.getImaginary();
}

bool Complex::operator!=(const Complex &other) const {
    return !(*this == other);
}

Complex& Complex::operator+=(const Complex &other) {
    re += other.re;
    setImaginary(getImaginary() + other.getImaginary());
    return *this;
}

Complex& Complex::operator-=(const Complex &other) {
    re -= other.re;
    setImaginary(getImaginary() - other.getImaginary());
    return *this;
}

Complex& Complex::operator*=(const Complex &other) {
    double tempRe = re * other.re - getImaginary() * other.getImaginary();
    double tempIm = re * other.getImaginary() + getImaginary() * other.re;
    re = tempRe;
    setImaginary(tempIm);
    return *this;
}

Complex& Complex::operator/=(const Complex &other) {
    *this = *this / other;
    return *this;
}