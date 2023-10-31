int isPalindrome(int num) {
    int reverse = 0, remainder, temp;
    temp = num;
    while(temp > 0) {
        remainder = temp % 10;
        reverse = (reverse * 10) + remainder;
        temp /= 10;
    }
    if(reverse == num)
        return 1;
    else
        return 0;
}