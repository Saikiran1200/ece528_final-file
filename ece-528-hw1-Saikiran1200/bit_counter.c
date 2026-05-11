/*
 * bit_counter.c
 * Counts the number of set bits (1s) in an unsigned 32-bit integer
 * Author: Sai Kiran
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    long long input;          // To validate signed input first
    uint32_t number;          // 32-bit unsigned integer
    int count = 0;

    printf("ECE 528 / Sai Kiran - HW1\n");
    printf("Enter a non-negative integer: ");

    // Check if input is a valid integer
    if (scanf("%lld", &input) != 1) {
        printf("Invalid input. Please enter a valid integer.\n");
        return 0;
    }

    // Check if input is within valid unsigned 32-bit range
    if (input < 0 || input > 4294967295ULL) {
        printf("Invalid input. Please enter a non-negative 32-bit integer.\n");
        return 0;
    }

    number = (uint32_t) input;

    // Count set bits using n &= (n - 1)
    while (number != 0) {
        number &= (number - 1);
        count++;
    }

    printf("Number of set bits: %d\n", count);

    return 0;
}
