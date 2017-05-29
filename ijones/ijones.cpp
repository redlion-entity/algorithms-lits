#include <stdio.h>
#include <stdlib.h>
#include <iostream>


int main(int argc, char *argv[]) {
    const char *input_file, *output_file;
    FILE *fp = NULL;


    if (argc >= 2) {
        input_file = argv[1];
    } else {
        //input_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/ijones/inputData/07.in";
        input_file = "ijones.in";
    }

    if (argc >= 3) {
        output_file = argv[2];
    } else {
        //output_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/ijones/ijones.out";
        output_file = "ijones.out";
    }

    // read data from file
    /*fp = fopen(input_file, "r");
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
    fclose(fp);*/







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




    /*if (keys_transformed_odd != NULL) {
        delete [] keys_transformed_odd;
    }
    if (keys_transformed_even != NULL) {
        delete [] keys_transformed_even;
    }*/

    fp = fopen(output_file, "w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    fprintf(fp, "%d", 0);
    fclose(fp);

    return 0;
}