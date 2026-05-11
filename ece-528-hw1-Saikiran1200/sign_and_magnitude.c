#include <stdio.h>

int main() {
    int num;

    // Input from user
    printf("Enter a number: ");
    scanf("%d", &num);

    // Check if number is positive, negative, or zero
    if (num > 0) {
        printf("The number is positive.\n");
    } else if (num < 0) {
        printf("The number is negative.\n");
    } else {
        printf("The number is zero.\n");
    }

    // Print absolute value
    if (num < 0) {
        printf("Absolute value: %d\n", -num);
    } else {
        printf("Absolute value: %d\n", num);
    }

    return 0;
}
