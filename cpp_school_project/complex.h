/**
* @file complex.h
* @description Bu sınıf Complex sınıfının ve onun metodlarının tanımlarını içerir.
* @assignment 2. Proje
* @date 03.12.2020
* @author Ömer Yasir Önal omeryasir.onal@stu.fsm.edu.tr
*/

#ifndef PROJECT2TEST_COMPLEX_H
#define PROJECT2TEST_COMPLEX_H
#include "iostream"


class Imaginary {
    private:
        double im;

    public:
    Imaginary(double im = 0);
    double getImaginary() const;
    void setImaginary(double im);
    };

class Complex : public Imaginary {
    private:
        double re;

    public:
        Complex(double re = 0, double im = 0);

        double getReal() const;
        void setReal(double re);

        // Operatör Overloading
        Complex operator+(const Complex &other) const;
        Complex operator-(const Complex &other) const;
        Complex operator*(const Complex &other) const;
        Complex operator/(const Complex &other) const;
        Complex operator~() const;
        Complex& operator=(const Complex &other);
        bool operator==(const Complex &other) const;
        bool operator!=(const Complex &other) const;
        Complex& operator+=(const Complex &other);
        Complex& operator-=(const Complex &other);
        Complex& operator*=(const Complex &other);
        Complex& operator/=(const Complex &other);


    };



#endif //PROJECT2TEST_COMPLEX_H
