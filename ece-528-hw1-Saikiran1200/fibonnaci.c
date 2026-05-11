/*
 * fibonacci.c
 * Prints the Fibonacci sequence up to N terms (iterative)
 * Author: Sai Kiran
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    long long input;
    unsigned int n;
    unsigned long long prev = 0, curr = 1, next;
    unsigned int i;

    printf("ECE 528/L - Sai Kiran - HW1\n");
    printf("Enter N (2 or greater): ");

    // Validate integer input
    if (scanf("%lld", &input) != 1) {
        printf("Invalid input. Please enter a valid integer.\n");
        return 0;
    }

    // Check N >= 2
    if (input < 2) {
        printf("Invalid input. N must be 2 or greater.\n");
        return 0;
    }

    n = (unsigned int) input;

    printf("Fibonacci sequence up to %u terms:\n", n);

    // Print first two terms
    printf("0 1 ");

    // Compute remaining terms iteratively
    for (i = 3; i <= n; i++) {
        next = prev + curr;
        printf("%llu ", next);
        prev = curr;
        curr = next;
    }

    printf("\n");

    return 0;
}
