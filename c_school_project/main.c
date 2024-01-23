/*
 * @file main.c
 * @description Bu sınıf, öğrencilerin ve aldıkları derslerin bilgilerinin oluşturulduğu sınıftır.
 *              Ayrıca öğrencilerin ortalamaları, standart sapmaları, kovaryansları ve dosyaya yazılması
 *              gibi fonksiyonların çağırılıp test edildiği sınıftır.
 * @assignment 1
 * @date 2023-12-04
 * @author Ömer Yasir Önal
 */

#include "Project1.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(int argc, char *argv[])
{
    // Dersler oluşturuluyor
    Ders matematik = createDers("Matematik", 4);
    Ders fizik = createDers("Fizik", 4);
    Ders kimya = createDers("Kimya", 3);
    Ders biyoloji = createDers("Biyoloji", 2);

    // Öğrenciler için dersler ve puanlar belirleniyor
    Ders ogrenci1Dersler[4] = {matematik, fizik, kimya, biyoloji};
    ogrenci1Dersler[0].puan = 50;
    ogrenci1Dersler[1].puan = 100;
    ogrenci1Dersler[2].puan = 100;
    ogrenci1Dersler[3].puan = 100;

    Ders ogrenci2Dersler[4] = {matematik, fizik, kimya, biyoloji};
    ogrenci2Dersler[0].puan = 50;
    ogrenci2Dersler[1].puan = 100;
    ogrenci2Dersler[2].puan = 0;
    ogrenci2Dersler[3].puan = 0;

    Ders ogrenci3Dersler[3] = {matematik, fizik, kimya};
    ogrenci3Dersler[0].puan = 80;
    ogrenci3Dersler[1].puan = 20;
    ogrenci3Dersler[2].puan = 80;

    // Öğrenciler oluşturuluyor ve dersler atılıyor
    Ogrenci ogrenci1 = createOgrenci("Ahmet", "Yilmaz", "Bilgisayar Muhendisligi", ogrenci1Dersler, 4);
    Ogrenci ogrenci2 = createOgrenci("Mehmet", "Kaya", "Yazilim Muhendisligi", ogrenci2Dersler, 4);
    Ogrenci ogrenci3 = createOgrenci("Ali", "Demir", "Bilgisayar Muhendisligi", ogrenci3Dersler, 3);

    // Öğrencilerin ortalamaları hesaplanıyor
    int ogrenci1DersSayisi = sizeof(ogrenci1Dersler) / sizeof(Ders);
    int ogrenci2DersSayisi = sizeof(ogrenci2Dersler) / sizeof(Ders);
    int ogrenci3DersSayisi = sizeof(ogrenci3Dersler) / sizeof(Ders);
    ogrenci1.ortalama = calculateStudentAverage(ogrenci1, ogrenci1DersSayisi);
    ogrenci2.ortalama = calculateStudentAverage(ogrenci2, ogrenci2DersSayisi);
    ogrenci3.ortalama = calculateStudentAverage(ogrenci3, ogrenci3DersSayisi);

    int sizeofOgrenciler = 3;
    Ogrenci *ogrenciler = malloc(sizeofOgrenciler * sizeof(Ogrenci));
    ogrenciler[0] = ogrenci1;
    ogrenciler[1] = ogrenci2;
    ogrenciler[2] = ogrenci3;

    // Öğrencilerin bilgileri yazdırılıyor
    printf("Öğrenci bilgileri:\n\n");
    printf("Öğrenci 1 Bilgileri:\n");
    printOgrenci(ogrenci1, ogrenci1DersSayisi);
    printf("\nÖğrenci 2 Bilgileri:\n");
    printOgrenci(ogrenci2, ogrenci2DersSayisi);
    printf("\nÖğrenci 3 Bilgileri:\n");
    printOgrenci(ogrenci3, ogrenci3DersSayisi);

    printf("\nÖğrenci dizisinin bilgileri:\n\n");
    printOgrenciDizi(ogrenciler, sizeofOgrenciler);

    // Ortalamalar hesaplanıyor
    float matematikOrtalama = calculateAverage("Matematik", ogrenciler, sizeofOgrenciler);
    printf("Matematik Ortalaması: %.2f\n", matematikOrtalama);
    float fizikOrtalama = calculateAverage("Fizik", ogrenciler, sizeofOgrenciler);
    printf("Fizik Ortalaması: %.2f\n", fizikOrtalama);
    float kimyaOrtalama = calculateAverage("Kimya", ogrenciler, sizeofOgrenciler);
    printf("Kimya Ortalaması: %.2f\n", kimyaOrtalama);
    float biyolojiOrtalama = calculateAverage("Biyoloji", ogrenciler, sizeofOgrenciler);
    printf("Biyoloji Ortalaması: %.2f\n", biyolojiOrtalama);

    // Standart sapmalar hesaplanıyor
    printf("\nÖğrencilerin standart sapmaları:\n\n");
    printf("Matematik dersinin standart sapması: %.2f\n", calculateStandardDeviation("Matematik", ogrenciler, sizeofOgrenciler));
    printf("Fizik dersinin standart sapması: %.2f\n", calculateStandardDeviation("Fizik", ogrenciler, sizeofOgrenciler));
    printf("Kimya dersinin standart sapması: %.2f\n", calculateStandardDeviation("Kimya", ogrenciler, sizeofOgrenciler));
    printf("Biyoloji dersinin standart sapması: %.2f\n", calculateStandardDeviation("Biyoloji", ogrenciler, sizeofOgrenciler));

    printf("\nMatematik ve Fizik derslerinin kovaryansı: %.2f\n", calculateCovariance(ogrenciler, sizeofOgrenciler, "Matematik", "Fizik"));

    printf("\nMatematik dersinde ortalamanın üstündeki öğrenciler:\n");
    listStudentsAboveAverage(ogrenciler, sizeofOgrenciler, "Matematik");

    // Dosyaya yazılıyor
    printf("\nÖğrenci bilgileri 'ogrenciler.txt' dosyasına yazılıyor...\n");
    writeStudentsToFile(ogrenciler, sizeofOgrenciler, "ogrenciler.txt");

    printf("\nÖğrenci bilgileri okunuyor...\n");
    Ogrenci **dosyadanOkunanOgrenciler = NULL;
    char *dosyaAdi = argv[1];

    // Dosyadan okunuyor
    int dosyadanOkunanSayi = readStudentsFromFile(dosyaAdi, &dosyadanOkunanOgrenciler);
    printf("Dosyadan okunan öğrenci sayısı: %d\n", dosyadanOkunanSayi);

    printf("\nDosyadan okunan öğrenci bilgileri:\n");
    for (int i = 0; i < dosyadanOkunanSayi; i++)
    {
        printOgrenciDersOlmadan(*dosyadanOkunanOgrenciler[i]);
    }

    // Bellekten siliniyor
    free(ogrenciler);
    ogrenciler = NULL;
    return 0;
}
