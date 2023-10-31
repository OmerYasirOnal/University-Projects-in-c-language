#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int sort(int size,int arr[]);
void kaydir(int arr[], int n);
int main(){


    // 1. soru
//
//    char str[100];
//
//    printf("Bir yazı girin: ");
//    scanf("%99[^\n]", str);
//
//    for (int i = 0; str[i] != '\0'; i++)
//    {
//        if (str[i] >= 'a' && str[i] <= 'z')
//        {
//            str[i] -= 32;
//        }
//    }
//
//    printf("Büyük harfe dönüştürülmüş hali: %s", str);



    // 2. soru

//    int counts[10] = {0};
//    srand(time(NULL));
//
//    for(int i = 0; i<1000; i++)
//    {
//    int randomNum = (rand() % 10)+1;
//    counts[randomNum - 1]++;
//
//    }
//
//    for (int i = 0; i < 10; i++)
//    {
//    printf("Sayı %d: %d\n", i + 1, counts[i]);
//    }
//

    // 3. soru

//    int arr[] = {1,5,3,4,5};
//    int arr2[] = {1,2,3,4,5};
//    int arr3[] = {5,4,3,2,1,};
//
//
//    int size = sizeof(arr) / sizeof(arr[0]);
//
//    printf("%d\n", sort(size, arr));
//    printf("%d\n", sort(size, arr2));
//    printf("%d\n", sort(size, arr3));
//

    // 4. soru

    int counts[] = {10,20,30,40,50,60,70,80,90,100};

    srand(time(NULL));
    int n;
    printf("Bir yazı girin: ");
    scanf("%d", &n);



    printf("Kaydırma işlemi yapılmadan önce: \n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", counts[i]);
    }

    kaydir(counts, n);
    printf("Kaydırma işlemi yapıldıktan sonra: \n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", counts[i]);
    }


    return 0;
}




    // 3. soru
int sort(int size,int arr[])
{
    int increase = 1 ;
    int decrese = 1;

    for (int i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            increase = 0;

        }
        else if (arr[i] < arr[i + 1])
        {
            decrese = 0;
        }

    }

    if(increase && decrese)
    {
        return 0;
    } else if(increase)
    {
        return 1;
    } else if(decrese)
    {
        return 2;
    }
    return 0;
}

    // 4. soru
void kaydir(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int temp = arr[0];
        for (int j = 0; j < 10 - 1; j++)
        {
            arr[j] = arr[j + 1];
        }
        arr[10 - 1] = temp;
    }
}