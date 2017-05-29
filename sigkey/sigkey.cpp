#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "qsort.h"


void transformKeys(char** keys, unsigned int* keys_transformed, const int quantity, int* bit_table, int* odd, int* even) {
    for (int i = 0; i < quantity; i++) {
        int length = strlen(keys[i]);
        keys_transformed[i] = 0;
        for (int j = 0; j < length; j++) {
            keys_transformed[i] += bit_table[(int)keys[i][j] - 97];
        }

        if (keys_transformed[i] % 2 == 0) {
            (*even)++;
        } else {
            (*odd)++;
        }
    }
}

void separateKeys(unsigned int* odd_keys, unsigned int* even_keys, unsigned int* keys, const int quantity) {
    int odd = 0, even = 0;

    for (int i = 0; i < quantity; i++) {
        if (keys[i] % 2 == 0) {
            even_keys[even++] = keys[i];
        } else {
            odd_keys[odd++] = keys[i];
        }
    }
}

int findMaskIndex(unsigned int key, int* bit_table) {
    int left = 0, right = 25, middle;

    while (left < right) {
        middle = (right + left) / 2;

        if (key <= bit_table[middle]) {
            right = middle;
        } else {
            left = middle;
        }

        if (right - left == 1) {
            break;
        }
    }

    return right;
}

int indexOf(unsigned int value, unsigned int* keys, const int quantity) {
    int left = 0, right = quantity - 1, middle;
    int result = -1;

    do {
        middle = (right + left) / 2;

        if (value < keys[middle]) {
            right = middle;
        } else if (keys[middle] < value) {
            left = middle;
        } else {
            result = middle;
            break;
        }

        if (right - left == 1) {
            if (left == middle) {
                left = right;
            } else {
                right = left;
            }
        }
    } while (middle != left || middle != right);

    return result;
}

unsigned int nextPossibleNumber(unsigned int value, int* bit_index, int* bit_table) {
    return value + bit_table[(*bit_index)++];
}

bool hasKeyPair(unsigned int key, unsigned int* keys, const int quantity, int* bit_table) {
    int maskIndex = findMaskIndex(key, bit_table);
    int bit_index = maskIndex;
    unsigned int pairKeyMinValue = (bit_table[maskIndex] - 1) ^ key;
    unsigned int pairKeyMaxValue = keys[quantity - 1];
    unsigned int keyValue = pairKeyMinValue;
    bool result = false;

    while (pairKeyMinValue <= keyValue && keyValue <= pairKeyMaxValue) {
        if (indexOf(keyValue, keys, quantity) >= 0) {
            result = true;
            break;
        }

        if (bit_index >= 26) break;

        keyValue = nextPossibleNumber(keyValue, &bit_index, bit_table);
    }

    return result;
}

int main(int argc, char *argv[]) {
    const char *input_file, *output_file;
    FILE *fp = NULL;
    int key_quantity, odd_quantity = 0, even_quantity = 0, pairs_number = 0;
    char **keys = NULL;
    unsigned int *keys_transformed = NULL;
    unsigned int *keys_transformed_odd = NULL;
    unsigned int *keys_transformed_even = NULL;
    int bit_table[26];
    int i = 0;
    char str[27];


    if (argc >= 2) {
        input_file = argv[1];
    } else {
        //input_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/sigkey/inputData/07.in";
        input_file = "sigkey.in";
    }

    if (argc >= 3) {
        output_file = argv[2];
    } else {
        //output_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/sigkey/sigkey.out";
        output_file = "sigkey.out";
    }

    // read data from file
    fp = fopen(input_file, "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    fscanf(fp, "%d", &key_quantity);

    keys = new char*[key_quantity];
    keys_transformed = new unsigned int[key_quantity];

    while(fscanf(fp, "%s", str) != EOF) {
        keys[i] = new char[27];
        strcpy(keys[i], str);
        i++;
    }
    fclose(fp);

    // initialize bit table
    for (i = 0; i < 26; i++) {
        bit_table[i] = 1 << i;
    }

    transformKeys(keys, keys_transformed, key_quantity, bit_table, &odd_quantity, &even_quantity);
    qSort(keys_transformed, key_quantity);
    if (keys != NULL) {
        delete [] keys;
    }

    keys_transformed_odd = new unsigned int[odd_quantity];
    keys_transformed_even = new unsigned int[even_quantity];
    separateKeys(keys_transformed_odd, keys_transformed_even, keys_transformed, key_quantity);
    if (keys_transformed != NULL) {
        delete [] keys_transformed;
    }

    // calculating the number of pairs
    if (odd_quantity <= even_quantity) {
        for (i = odd_quantity - 1; i >= 0; i--) {
            if (hasKeyPair(keys_transformed_odd[i], keys_transformed_even, even_quantity, bit_table)) {
                pairs_number++;
            }
        }
    } else {
        for (i = even_quantity - 1; i >= 0; i--) {
            if (hasKeyPair(keys_transformed_even[i], keys_transformed_odd, odd_quantity, bit_table)) {
                pairs_number++;
            }
        }
    }





    /*printf("Key quantity: %d\n", key_quantity);
//    for (i = 0; i < key_quantity; i++) {
//        printf("%s\n", keys[i]);
//    }
    printf("Odd: %d\n", odd_quantity);
    printf("Even: %d\n", even_quantity);
//    for (i = 0; i < odd_quantity; i++) {
//        printf("%d\n", keys_transformed_odd[i]);
//    }
//    for (i = 0; i < even_quantity; i++) {
//        printf("%d\n", keys_transformed_even[i]);
//    }
    printf("Pairs count: %d\n", pairs_number);*/




    if (keys_transformed_odd != NULL) {
        delete [] keys_transformed_odd;
    }
    if (keys_transformed_even != NULL) {
        delete [] keys_transformed_even;
    }

    fp = fopen(output_file, "w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    fprintf(fp, "%d", pairs_number);
    fclose(fp);

    return 0;
}