/*
 * @file Project1.c
 * @description Bu sınıf, Öğrenci ve Ders yapılarının oluşturulduğu sınıftır.
 *               Ayrıca ilgili fonksiyonların oluşturulduğu sınıftır.
 * @assignment 1
 * @date 2023-12-04
 * @author Ömer Yasir Önal
 */

#include <string.h>
#include "Project1.h"
#include "math.h"
#define MAX_DERS_SAYISI 10

Ders createDers(char *dersAdi, unsigned short int kredi)
{
    Ders ders;
    ders.dersAdi = (char *)malloc(256 * sizeof(char));
    strncpy(ders.dersAdi, dersAdi, 256);
    ders.kredi = kredi;
    return ders;
}

Ogrenci createOgrenci(char *adi, char *soyadi, char *bolumu, Ders *aldigiDersler, int dersSayisi)
{
    Ogrenci ogrenci;
    ogrenci.ogrAdi = (char *)malloc(256 * sizeof(char));
    strncpy(ogrenci.ogrAdi, adi, 256);
    ogrenci.ogrSoyAdi = (char *)malloc(256 * sizeof(char));
    strncpy(ogrenci.ogrSoyAdi, soyadi, 256);
    ogrenci.bolumu = (char *)malloc(256 * sizeof(char));
    strncpy(ogrenci.bolumu, bolumu, 256);
    ogrenci.aldigiDersler = (Ders *)malloc(dersSayisi * sizeof(Ders));
    for (int i = 0; i < dersSayisi; i++)
    {
        ogrenci.aldigiDersler[i] = aldigiDersler[i];
    }

    return ogrenci;
}

void printOgrenciDersOlmadan(Ogrenci ogrenci)
{
    printf("Ogrenci Adi: %s\n", ogrenci.ogrAdi);
    printf("Ogrenci Soyadi: %s\n", ogrenci.ogrSoyAdi);
    printf("Ogrenci Bolumu: %s\n", ogrenci.bolumu);
    printf("Ogrenci Ortalamasi: %.2f\n", ogrenci.ortalama);
}

void printOgrenci(Ogrenci ogrenci, int dersSayisi)
{
    printf("Ogrenci Adi: %s\n", ogrenci.ogrAdi);
    printf("Ogrenci Soyadi: %s\n", ogrenci.ogrSoyAdi);
    printf("Ogrenci Bolumu: %s\n", ogrenci.bolumu);
    printf("Ogrenci Ortalamasi: %.2f\n", ogrenci.ortalama);
    printf("Aldigi Dersler:\n");

    for (int i = 0; i < dersSayisi; i++)
    {
        if ((ogrenci.aldigiDersler + i)->dersAdi != NULL)
            printf("\tDers Adi: %s\n", (ogrenci.aldigiDersler + i)->dersAdi);
    }
}

void printOgrenciDizi(Ogrenci *ogrenci, int size)
{ // Pointerlarda size alamıyoruz. Bu yüzden size parametresini alıyoruz.
    for (int i = 0; i < size; i++)
    {
        printf("Ogrenci %d\n", i + 1);
        printf("Adi: %s, Soyadi: %s\n", ogrenci[i].ogrAdi, ogrenci[i].ogrSoyAdi);
        printf("Bolumu: %s\n", ogrenci[i].bolumu);
        printf("Ortalamasi: %.2f\n\n", ogrenci[i].ortalama);
    }
}

float calculateAverage(char *dersAdi, Ogrenci *ogrenciler, int size)
{
    float toplamPuan = 0;
    int toplamDersSayisi = 0;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < MAX_DERS_SAYISI; j++)
        {
            // Ders adının NULL olmadığını kontrol et.
            if ((ogrenciler + i)->aldigiDersler[j].dersAdi == NULL)
            {
                break; // NULL değerine ulaşıldı, döngüyü kır.
            }

            if (strcmp((ogrenciler + i)->aldigiDersler[j].dersAdi, dersAdi) == 0)
            {
                toplamPuan += (ogrenciler + i)->aldigiDersler[j].puan;
                toplamDersSayisi++;
                break; // Aynı dersi birden fazla kez almaz, bu yüzden döngüyü kır.
            }
        }
    }

    if (toplamDersSayisi > 0)
    {
        return toplamPuan / toplamDersSayisi;
    }
    else
    {
        return 0;
    }
}

float calculateStandardDeviation(char *dersAdi, Ogrenci *ogrenciler, int size)
{
    float ort = calculateAverage(dersAdi, ogrenciler, size);
    float sum = 0;
    int ogrNum = 0;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < MAX_DERS_SAYISI; j++)
        {
            // Ders adının NULL olmadığını kontrol et.
            if ((ogrenciler + i)->aldigiDersler[j].dersAdi == NULL)
            {
                break; // NULL değerine ulaşıldı, döngüyü kır.
            }

            if (strcmp((ogrenciler + i)->aldigiDersler[j].dersAdi, dersAdi) == 0)
            {
                float fark = (ogrenciler + i)->aldigiDersler[j].puan - ort;
                sum += fark * fark;
                ogrNum++;
                break; // Aynı dersi birden fazla kez almaz, bu yüzden döngüyü kır.
            }
        }
    }

    if (ogrNum > 1)
    {
        return sqrt(sum / (ogrNum - 1)); // Standart sapma formülü
    }
    else
    {
        return 0;
    }
}

float calculateStudentAverage(Ogrenci ogrenci, int ogrenci1DersSayisi)
{
    float toplamPuan = 0;
    int toplamDersSayisi = 0;

    for (int i = 0; i < ogrenci1DersSayisi; i++)
    {
        toplamPuan += ogrenci.aldigiDersler[i].puan;
        toplamDersSayisi++;
    }

    if (toplamDersSayisi > 0)
    {
        return toplamPuan / toplamDersSayisi;
    }
    else
    {
        return 0;
    }
}

float calculateCovariance(Ogrenci *ogrenciler, int ogrenciSayisi, char *dersAdi1, char *dersAdi2)
{
    float ders1Ort = calculateAverage(dersAdi1, ogrenciler, ogrenciSayisi);
    float ders2Ort = calculateAverage(dersAdi2, ogrenciler, ogrenciSayisi);
    float sum = 0;
    int count = 0;

    for (int i = 0; i < ogrenciSayisi; i++)
    {
        float puan1 = -1, puan2 = -1;

        for (int j = 0; j < 2; j++)
        {
            if (strcmp((ogrenciler + i)->aldigiDersler[j].dersAdi, dersAdi1) == 0)
            {
                puan1 = (ogrenciler + i)->aldigiDersler[j].puan;
            }
            if (strcmp((ogrenciler + i)->aldigiDersler[j].dersAdi, dersAdi2) == 0)
            {
                puan2 = (ogrenciler + i)->aldigiDersler[j].puan;
            }
        }

        if (puan1 != -1 && puan2 != -1)
        {
            sum += (puan1 - ders1Ort) * (puan2 - ders2Ort);
            count++;
        }
    }

    return sum / count;
}

void listStudentsAboveAverage(Ogrenci *ogrenciler, int ogrenciSize, char *dersAdi)
{
    float dersOrt = calculateAverage(dersAdi, ogrenciler, ogrenciSize);

    for (int i = 0; i < ogrenciSize; i++)
    {
        float puan = -1;

        for (int j = 0; j < MAX_DERS_SAYISI; j++)
        {
            if (ogrenciler[i].aldigiDersler[j].dersAdi != NULL)
            {
                if (strcmp((ogrenciler + i)->aldigiDersler[j].dersAdi, dersAdi) == 0)
                {
                    puan = (ogrenciler + i)->aldigiDersler[j].puan;
                }
            }
            else
            {
                break; // Ders adı NULL ise döngüyü kır
            }
        }

        if (puan > dersOrt)
        {
            printf("%s %s\n", ogrenciler[i].ogrAdi, ogrenciler[i].ogrSoyAdi);
        }
    }
}

void writeStudentsToFile(Ogrenci *ogrenci, int size, char *filename)
{
    FILE *file = fopen(filename, "w"); // Dosyayı ekleme modunda aç

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%s, %s, %s, Ortalaması: %.2f\n", ogrenci[i].ogrAdi, ogrenci[i].ogrSoyAdi, ogrenci[i].bolumu, ogrenci[i].ortalama);
    }

    fclose(file);
}

int readStudentsFromFile(const char *dosyaAdi, Ogrenci ***ogrenciler)
{
    FILE *file = fopen(dosyaAdi, "r");
    if (!file)
    {
        printf("Dosya açılamadı.\n");
        return 0;
    }

    // Ogrenci dizisi için başlangıç kapasitesini ayarla
    int kapasite = 10;
    int ogrenciSayisi = 0;
    *ogrenciler = malloc(kapasite * sizeof(Ogrenci *));

    if (!*ogrenciler)
    {
        printf("Bellek ayrılamadı.\n");
        fclose(file);
        return 0;
    }

    char satir[1024];
    while (fgets(satir, sizeof(satir), file))
    {
        if (ogrenciSayisi >= kapasite)
        {
            // Dizi kapasitesini genişlet
            kapasite *= 2;
            *ogrenciler = realloc(*ogrenciler, kapasite * sizeof(Ogrenci *));
            if (!*ogrenciler)
            {
                printf("Bellek yeniden ayrılamadı.\n");
                fclose(file);
                return 0;
            }
        }

        Ogrenci *ogrenci = malloc(sizeof(Ogrenci)); // Yeni Ogrenci için bellek ayır
        if (ogrenci == NULL)
        {
            printf("Bellek ayrılamadı.\n");
            // Burada daha önce ayrılmış belleği serbest bırakmalısınız
            fclose(file);
            return 0;
        }

        // Okunan satırı ayrıştır
        char adi[256], soyadi[256], bolumu[256];
        float ortalama;
        if (sscanf(satir, "%[^,], %[^,], %[^,], Ortalaması: %f", adi, soyadi, bolumu, &ortalama) == 4)
        {
            // Ogrenci bilgilerini ayarla
            ogrenci->ogrAdi = strdup(adi);
            ogrenci->ogrSoyAdi = strdup(soyadi);
            ogrenci->bolumu = strdup(bolumu);
            ogrenci->ortalama = ortalama;
            ogrenci->aldigiDersler = NULL;

            (*ogrenciler)[ogrenciSayisi++] = ogrenci;
        }
        else
        {
            free(ogrenci); // sscanf başarısız oldu, bu yüzden belleği serbest bırak
        }
    }

    fclose(file);
    return ogrenciSayisi;
}
