/**
* @file main.cpp
* @description Bu sınıf Linear Algebra sınıfının ve onun metodlarının tanımlarını içerir.
* Aynı zamanda Main fonksiyonunu içermektedir ve testler burada yapılmaktadır.
* @assignment 2. Proje
* @date 03.12.2020
* @author Ömer Yasir Önal omeryasir.onal@stu.fsm.edu.tr
*/

#include <iostream>
#include "complex.h"
#include "vector.h"


// LinearAlgebraObject soyut sınıfı
class LinearAlgebraObject {
public:
    virtual ~LinearAlgebraObject() {}
    virtual void print() const = 0;
};

// Matrix sınıfı
class Matrix : public LinearAlgebraObject {
private:
    size_t row, col;
    Complex **elements;

protected:

    // Matrix sınıfının alt sınıfları için kullanılacak
    void setElement(size_t i, size_t j, const Complex& value) {
        if (i >= row || j >= col) {
            throw std::out_of_range("Index out of bounds");
        }
        elements[i][j] = value;
    }


public:
    Complex* getElementAt(size_t i, size_t j) const {
        if (i >= row || j >= col) {
            throw std::out_of_range("Index out of bounds");
        }
        return &elements[i][j];
    }
    Matrix(size_t row, size_t col) : row(row), col(col) {
        elements = new Complex*[row];
        for (size_t i = 0; i < row; ++i) {
            elements[i] = new Complex[col];
        }
    }

    // Destructor
    ~Matrix() {
        for (size_t i = 0; i < row; ++i) {
            delete[] elements[i];
        }
        delete[] elements;
    }

    // Copy constructor
    Complex& operator()(size_t rowIndex, size_t colIndex) {
        return elements[rowIndex][colIndex];
    }

    // LinearAlgebraObject sınıfından kalıtım
    void print() const {
        std::cout << "Matrix:\n";
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                std::cout << elements[i][j].getReal() << " + " << elements[i][j].getImaginary() << "i ";
            }
            std::cout << std::endl;
        }
    }

    // Transpoze alma
    Matrix transpose() const {
        Matrix transposed(col, row);
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                transposed(j, i) = elements[i][j];
            }
        }
        return transposed;
    }

    // Determinant hesaplama
    Complex determinant() const {
        if (row != col) {
            throw std::runtime_error("Determinant can only be calculated for square matrices.");
        }
        // Basit 2x2 matris için determinant hesaplama
        if (row == 2) {
            return elements[0][0] * elements[1][1] - elements[0][1] * elements[1][0];
        }

        // 3x3 matrisler için determinant hesaplama
        if (row == 3) {
            Complex term1 = elements[0][0] * (elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1]);
            Complex term2 = elements[0][1] * (elements[1][0] * elements[2][2] - elements[1][2] * elements[2][0]);
            Complex term3 = elements[0][2] * (elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0]);
            return term1 - term2 + term3;
        }

        Complex det(0, 0);
        int sign = 1;
        for (size_t i = 0; i < col; ++i) {
            Matrix subMatrix(row - 1, col - 1);
            for (size_t j = 1; j < row; ++j) {
                for (size_t k = 0; k < col; ++k) {
                    if (k == i) continue;
                    subMatrix(j - 1, k < i ? k : k - 1) = elements[j][k];
                }
            }
            det = det + (Complex(sign, 0) * elements[0][i] * subMatrix.determinant());
            sign = -sign;
        }
        return det;
    }

    Matrix& operator*=(const Matrix &other) {
        if (row != col || row != other.row || col != other.col) {
            throw std::runtime_error("Matrix multiplication-assignment is only valid for square matrices of the same size.");
        }

        *this = *this * other;
        return *this;
    }

    Matrix operator*(const Matrix &other) const {
        if (col != other.row) {
            throw std::runtime_error("Matrix dimensions do not match for multiplication");
        }
        Matrix result(row, other.col);
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < other.col; ++j) {
                for (size_t k = 0; k < col; ++k) {
                    result(i, j) = result(i, j) + (elements[i][k] * other.elements[k][j]);
                }
            }
        }
        return result;
    }

    Matrix& operator=(const Matrix &other) {
        if (this != &other) {
            for (size_t i = 0; i < row; ++i) {
                delete[] elements[i];
            }
            delete[] elements;

            row = other.row;
            col = other.col;
            elements = new Complex*[row];
            for (size_t i = 0; i < row; ++i) {
                elements[i] = new Complex[col];
                for (size_t j = 0; j < col; ++j) {
                    elements[i][j] = other.elements[i][j];
                }
            }
        }
        return *this;
    }

    size_t getRow() const { return row; }
    size_t getCol() const { return col; }

    // transpose, determinant ve diğer operatörler ve metotlar buraya eklenecek
};

// SquareMatrix sınıfı
class SquareMatrix : public Matrix {
public:

    // Constructors
    SquareMatrix(size_t size) : Matrix(size, size) {
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                setElement(i, j, Complex(rand() % 10, rand() % 10)); // Rastgele değerleri ayarla
            }
        }
    }
    SquareMatrix(const SquareMatrix &other) : Matrix(other) {}

    void print() const override {
        std::cout << "Square Matrix:\n";
        for (size_t i = 0; i < getRow(); ++i) {
            for (size_t j = 0; j < getCol(); ++j) {
                Complex* elem = getElementAt(i, j);
                std::cout << elem->getReal() << " + " << elem->getImaginary() << "i ";
            }
            std::cout << std::endl;
        }
    }

};

// IdentityMatrix sınıfı
class IdentityMatrix : public SquareMatrix {
public:

   IdentityMatrix(size_t size) : SquareMatrix(size) {
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                if (i == j) {
                    (*this)(i, i) = Complex(1, 0); // Ana köşegende 1 değeri
                } else {
                    (*this)(i, j) = Complex(0, 0); // Diğer tüm elemanlar 0 değeri
                }
            }
        }
    }

    // Copy constructor
    IdentityMatrix(const IdentityMatrix &other) = default;


    void print() const override {
        std::cout << "Identity Matrix:\n";
        for (size_t i = 0; i < getRow(); ++i) {
            for (size_t j = 0; j < getCol(); ++j) {
                Complex* elem = getElementAt(i, j);
                std::cout << elem->getReal() << " + " << elem->getImaginary() << "i ";
            }
            std::cout << std::endl;
        }
    }
};

// TriangleMatrix sınıfı
class TriangleMatrix : public SquareMatrix {
public:
    TriangleMatrix(size_t size) : SquareMatrix(size) {
        for (size_t i= 0; i < size; ++i) {
            for (size_t j = i + 1; j < size; ++j) {
                (*this)(i, j) = Complex(0, 0);
            }
        }
    }



    TriangleMatrix(const TriangleMatrix &other) = default;

    void print() const override {
        std::cout << "Triangle Matrix:\n";
        for (size_t i = 0; i < getRow(); ++i) {
            for (size_t j = 0; j < getCol(); ++j) {
                Complex* elem = getElementAt(i, j);
                std::cout << elem->getReal() << " + " << elem->getImaginary() << "i ";
            }
            std::cout << std::endl;
        }
    }
};

// Testler
int main() {
    // Complex sınıfı testleri
    std::cout << "----- Complex Sınıfının Testleri -----\n";
    Complex c1(2, 3), c2(4, -1);
    Complex cToplam = c1 + c2;
    Complex cFark = c1 - c2;
    Complex cCarpim = c1 * c2;
    Complex cBolum = c1 / c2;
    c1 += c2; // c1 = c1 + c2
    c1 -= c2; // c1 = c1 - c2
    c1 *= c2; // c1 = c1 * c2
    c1 /= c2; // c1 = c1 / c2

    std::cout << "Toplam: " << cToplam.getReal() << " + " << cToplam.getImaginary() << "i\n";
    std::cout << "Fark: " << cFark.getReal() << " + " << cFark.getImaginary() << "i\n";
    std::cout << "Carpim: " << cCarpim.getReal() << " + " << cCarpim.getImaginary() << "i\n";
    std::cout << "Bolum: " << cBolum.getReal() << " + " << cBolum.getImaginary() << "i\n";

    // Vector sınıfı testleri
    std::cout << "\n----- Vector Sınıfının Testleri -----\n";
    Vector v1(2), v2(2);
    v1[0] = Complex(1, 2); v1[1] = Complex(3, 4);
    v2[0] = Complex(5, 6); v2[1] = Complex(7, 8);

    Vector vToplam = v1 + v2;
    Vector vFark = v1 - v2;
    Complex vDotCarpim = v1.dot(v2);
    v1 += v2;
    v1 -= v2;
    v1 *= v2;

    std::cout << "Toplam: " << vToplam[0].getReal() << " + " << vToplam[0].getImaginary() << "i, "
              << vToplam[1].getReal() << " + " << vToplam[1].getImaginary() << "i\n";

    std::cout << "Fark: " << vFark[0].getReal() << " + " << vFark[0].getImaginary() << "i, "
              << vFark[1].getReal() << " + " << vFark[1].getImaginary() << "i\n";

    std::cout << "Vector Dot Carpim: " << vDotCarpim.getReal() << " + " << vDotCarpim.getImaginary() << "i\n";

    // Matrix sınıfı ve türetilmiş sınıfların testleri
    std::cout << "\n----- Matrix ve Türetilmiş Sınıfların Testleri -----\n";
    Matrix m1(2, 2), m2(2, 2);
    m1(0, 0) = Complex(1, 1); m1(0, 1) = Complex(2, -1);
    m1(1, 0) = Complex(3, 2); m1(1, 1) = Complex(4, 0);

    m2(0, 0) = Complex(0, 1); m2(0, 1) = Complex(-1, 1);
    m2(1, 0) = Complex(2, 0); m2(1, 1) = Complex(1, -1);

    Matrix mProd = m1 * m2;
    Matrix mTranspose = m1.transpose();

    std::cout << "Matrix 1:\n";
    for (size_t i = 0; i < m1.getRow(); ++i) {
        for (size_t j = 0; j < m1.getCol(); ++j) {
            Complex* elem = m1.getElementAt(i, j);
            std::cout << elem->getReal() << " + " << elem->getImaginary() << "i ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix Carpim:\n";
    for (size_t i = 0; i < mProd.getRow(); ++i) {
        for (size_t j = 0; j < mProd.getCol(); ++j) {
            Complex* elem = mProd.getElementAt(i, j);
            std::cout << elem->getReal() << " + " << elem->getImaginary() << "i ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix Transpose:\n";
    for (size_t i = 0; i < mTranspose.getRow(); ++i) {
        for (size_t j = 0; j < mTranspose.getCol(); ++j) {
            Complex* elem = mTranspose.getElementAt(i, j);
            std::cout << elem->getReal() << " + " << elem->getImaginary() << "i ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix Determinant: " << m1.determinant().getReal() << " + " << m1.determinant().getImaginary() << "i\n";


    // SquareMatrix, IdentityMatrix ve TriangleMatrix testleri
    SquareMatrix sqMatrix(5);
    IdentityMatrix idMatrix(3);
    TriangleMatrix trMatrix(3);

    sqMatrix.print();
    idMatrix.print();
    trMatrix.print();

    return 0;
}
