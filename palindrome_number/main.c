#include "stdio.h"
#include "library.h"

int main(){
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(isPalindrome(num)==1)
        printf("%d is a palindrome number.", num);
    else
        printf("%d is not a palindrome number.", num);
    return 0;
}
