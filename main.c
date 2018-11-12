// File: main.c
//
// Description: This program generates an array of random length and populates it
//      with random values. The totals are assigned to different variable types,
//      including unsigned int and unsigned long long. The running totals are then
//      displayed in a table with column headers. If there is integer overflow 
//      detected in one of the unsigned int variables, the value is replaced with 
//      the word "REJECTED". The other two columns display the running totals, 
//      including rollover if it occurs.
//
// Created: 2017-10-26 (R. Sowers)

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_ARRAY_LENGTH 100
#define MIN_ARRAY_LENGTH 1
#define MIN_ARRAY_VALUE  1
#define RAND_VAL_MAX     1234567890
#define ANSI_COLOR_RED   "\033[31m"     
#define ANSI_COLOR_RESET "\033[0m"  
#define COL_WIDTH        13    

void display(unsigned int *values, unsigned int num_values);

int main(int argc, char const *argv[])
{
        unsigned int arrayLength;
        unsigned int *listStart = NULL;
        errno = 0;

        srandom(time(NULL));    // seed random number generator

        // generate a random number to be the size of the array
        arrayLength = (random() % MAX_ARRAY_LENGTH) + MIN_ARRAY_LENGTH;

        // allocate memory for the array of previously determined size
        listStart = malloc(sizeof(unsigned int) * arrayLength);

        if ((listStart == NULL) || (errno != 0)) {
                perror("malloc failed");
                exit(-1);
        }

        // populate the array with random numbers
        for (int i = 0; i < arrayLength; ++i)
        {
                listStart[i] = (random() % RAND_VAL_MAX) + MIN_ARRAY_VALUE;
        }

        // display the table
        display(listStart, arrayLength);

        // free allocated memory
        free(listStart);
        listStart = NULL;

        return 0;
}

void display(unsigned int *values, unsigned int num_values)
{
        unsigned int totalOverflow = 0;
        unsigned int totalNoOverflow = 0;
        unsigned long long totalNoOverflowLong = 0;

        // create table column headers
        printf("%*s %*s %*s %*s\n", COL_WIDTH, "", COL_WIDTH, "Unsigned", \
                COL_WIDTH, "Unsigned", COL_WIDTH, "Unsigned");
        printf("%*s %*s %*s %*s\n", COL_WIDTH, "", COL_WIDTH, "int", COL_WIDTH, "int", \
                COL_WIDTH, "long long");
        printf("%*s %*s %*s %*s\n", COL_WIDTH, "", COL_WIDTH, "Subtotal", \
                COL_WIDTH, "Subtotal", COL_WIDTH, "Subtotal");
        printf("%*s %*s %*s %*s\n", COL_WIDTH, "Random", COL_WIDTH, "w/ Rollover", \
                COL_WIDTH, "w/o Rollover", COL_WIDTH, "w/o Rollover");
        printf("%*s %*s %*s %*s\n", COL_WIDTH, "Number", COL_WIDTH, "Detection", \
                COL_WIDTH, "Detection", COL_WIDTH, "Detection");
        printf("------------- ------------- ------------- -------------\n");

        // calculate totals and determine if integer overflow occurs
        for (int i = 0; i < num_values; ++i)
        {
                totalNoOverflow += values[i];
                totalNoOverflowLong += values[i];

                // if integer overflow occurs, replace the totalOverflow 
                //      with the word "REJECTED" in red, and print the other totals;
                //      otherwise, print all the totals
                if (totalOverflow > 0 && totalOverflow > UINT_MAX - values[i])
                {
                        printf("%*u %s%*s%s %*u %*llu\n", COL_WIDTH, values[i], \
                                ANSI_COLOR_RED, COL_WIDTH, "REJECTED", ANSI_COLOR_RESET, \
                                COL_WIDTH, totalNoOverflow, COL_WIDTH, totalNoOverflowLong);
                } else {
                        totalOverflow += values[i];
                        printf("%*u %*u %*u %*llu\n", COL_WIDTH, values[i], COL_WIDTH, \
                                totalOverflow, COL_WIDTH, totalNoOverflow, COL_WIDTH, \
                                totalNoOverflowLong);
                }
        }
}

























