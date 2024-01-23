/**
* @file vector.h
* @description Bu sınıf Vector sınıfının ve onun metodlarının tanımlarını içerir.
* @assignment 2. Proje
* @date 03.12.2020
* @author Ömer Yasir Önal omeryasir.onal@stu.fsm.edu.tr
*/
#ifndef PROJECT2TEST_VECTOR_H
#define PROJECT2TEST_VECTOR_H
#include "complex.h"



class Vector {
private:
    size_t size;
    Complex *elements;

public:
    // Constructors and destructor
    Vector(size_t size);

    Vector(const Vector &other);

    ~Vector();

    // operators
    Vector &operator=(const Vector &other);
    Complex &operator[](size_t index);
    Vector operator+(const Vector &other) const;
    Vector operator-(const Vector &other) const;
    Vector &operator+=(const Vector &other);
    Vector &operator-=(const Vector &other);
    Complex dot(const Vector &other) const;
    Vector &operator*=(const Vector &other);
    bool operator==(const Vector &other) const;

    // Additional methods
    size_t getSize() const;
    void setSize(size_t size);
};


#endif //PROJECT2TEST_VECTOR_H
