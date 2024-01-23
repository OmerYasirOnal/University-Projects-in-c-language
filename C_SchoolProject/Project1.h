/*
 * @file Project1.h
 * @description Bu sınıf, Ders ve Ogrenci yapılarının oluşturulduğu sınıftır.
 *              Ayrıca ilgili fonksiyon imzalarının oluşturulduğu sınıftır.
 * @assignment 1
 * @date 2023-12-04
 * @author Ömer Yasir Önal
 */

#ifndef PROJE1_H
#define PROJE1_H

#include <stdio.h>
#include <stdlib.h>

// Ders structure
typedef struct
{
    char *dersAdi;
    unsigned short int kredi;
    unsigned short int puan;
} Ders;

// Ogrenci structure
typedef struct
{
    char *ogrAdi;
    char *ogrSoyAdi;
    char *bolumu;
    float ortalama;
    Ders *aldigiDersler;
} Ogrenci;

// Fonksiyon prototipleri

Ders createDers(char *dersAdi, unsigned short int kredi);
Ogrenci createOgrenci(char *adi, char *soyadi, char *bolumu, Ders *aldigiDersler, int dersSayisi);
void printOgrenci(Ogrenci ogrenci, int dersSayisi);
float calculateStudentAverage(Ogrenci ogrenci, int dersSayisi);
void printOgrenciDizi(Ogrenci *ogrenci, int size);
float calculateAverage(char *dersAdi, Ogrenci *ogrenciler, int size);
float calculateStandardDeviation(char *dersAdi, Ogrenci *ogrenciler, int size);
float calculateCovariance(Ogrenci *ogrenciler, int ogrenciSayisi, char *dersAdi1, char *dersAdi2);
void listStudentsAboveAverage(Ogrenci *ogrenciler, int ogrenciSize, char *dersAdi);
void writeStudentsToFile(Ogrenci *ogrenci, int size, char *filename);
int readStudentsFromFile(const char *dosyaAdi, Ogrenci ***ogrenciler);
void printOgrenciDersOlmadan(Ogrenci ogrenci);

#endif // PROJE1_H