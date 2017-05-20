#include <stdio.h>
#include <stdlib.h>
#include "qsort.h"

#define MAX(a, b)   ((a > b) ? a : b)
#define MIN(a, b)   ((a < b) ? a : b)

int getJokerQuantity(int *A, int length) {
    int i, quantity = 0;

    for (i = 0; i < length; i++) {
        if (A[i] == 0) {
            quantity++;
        } else {
            break;
        }
    }

    return quantity;
}

int** uniqueSorted(int *A, int length, int *quantity) {
    int **temp = new int*[length], **result;
    int i, lastValue = 0;

    *quantity = 0;
    result = NULL;

    for (i = 0; i < length; i++) {
        if (A[i] != lastValue) {
            lastValue = A[i];
            temp[(*quantity)++] = &A[i];
        }
    }

    if (*quantity != length) {
        result = new int*[*quantity];

        for (i = 0; i < *quantity; i++) {
            result[i] = temp[i];
        }

        delete [] temp;
    } else {
        result = temp;
    }

    return result;
}

int findSequence(int **A, int *start_index, int *end_index, int length, int *free_jokers, int sequence_length) {
    int i, difference, quantity = sequence_length;
    int temp;

    // try to shift end index
    while (true) {
        i = *end_index + 1;
        if (i >= length) break;

        difference = *A[i] - *A[*end_index] ;
        if (difference == 1) {
            *end_index = i;
            quantity++;
        } else if (difference - 1 <= *free_jokers) {
            *end_index = i;
            *free_jokers = *free_jokers - (difference - 1);
            quantity = difference  + quantity;
        } else if (*free_jokers > 0) {
            temp = *A[*end_index] + *free_jokers;

            if (temp <= 1000000) {
                quantity += *free_jokers;
                *free_jokers = 0;
            } else {
                temp = 1000000 - *A[*end_index];
                quantity += temp;
                *free_jokers = *free_jokers - temp;
            }
        } else {
            break;
        }
    }

    // if the end is already reached and there are still jokers
    if (i >= length && *free_jokers > 0) {
        quantity += MIN(*free_jokers, *A[*start_index] - 1);
    }

    return quantity;
}

int findNextStartIndex(int **A, int start_index, int length) {
    int i;

    for (i = start_index + 1; i < length; i++) {
        if (A[i] - A[i - 1] > 1) {
            break;
        }
    }

    return i;
}

int main(int argc, char *argv[]) {
    char *input_file, *output_file;
    FILE *fp = NULL;
    int cards[100000], quantity = 0, card;
    int **sorted_uniqued_cards;
    int i, joker_quantity, free_joker_quantuty, sorted_uniqued_cards_quantity;
    int start_index = 0, end_index = 0, sequence_length = 1, max_sequence_length = 0, next_start_index;

    if (argc >= 2) {
        input_file = argv[1];
    } else {
        //input_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/lngpok/inputData/04.in";
        input_file = "lngpok.in";
    }

    if (argc >= 3) {
        output_file = argv[2];
    } else {
        //output_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/lngpok/discnt.out";
        output_file = "lngpok.out";
    }

    // read data from file
    fp = fopen(input_file, "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    while(fscanf(fp, "%d", &card) == 1) {
        cards[quantity++] = card;
    }
    fclose(fp);

    // sort cards
    qSort(cards, quantity);

    // unique cards
    joker_quantity = getJokerQuantity(cards, quantity);
    sorted_uniqued_cards = uniqueSorted(&cards[joker_quantity], quantity - joker_quantity, &sorted_uniqued_cards_quantity);

    free_joker_quantuty = joker_quantity;
    while (end_index < sorted_uniqued_cards_quantity - 1) {
        sequence_length = findSequence(sorted_uniqued_cards, &start_index, &end_index, sorted_uniqued_cards_quantity, &free_joker_quantuty, sequence_length);
        max_sequence_length = MAX(max_sequence_length, sequence_length);

        // count first index of next sub sequence without jokers
        next_start_index = findNextStartIndex(sorted_uniqued_cards, start_index, sorted_uniqued_cards_quantity);
        if (next_start_index > end_index) {
            end_index = next_start_index;
        }

        // count free jokers
        if (joker_quantity > 0 && next_start_index > 0 && next_start_index < sorted_uniqued_cards_quantity) {
            free_joker_quantuty = MIN(*sorted_uniqued_cards[next_start_index] - *sorted_uniqued_cards[next_start_index - 1] - 1 + free_joker_quantuty, joker_quantity);
        }

        // count next sequence length
        if (end_index == next_start_index) {
            sequence_length = 0;
        } else {
            sequence_length = next_start_index - start_index + (*sorted_uniqued_cards[next_start_index] - *sorted_uniqued_cards[next_start_index - 1] - 1);
        }

        start_index = next_start_index;
    }


    /*printf("Sorted cards: ");
    for (i = 0; i < quantity; i++) {
        printf("%d ", cards[i]);
    }
    printf("\nlength: %d\n", quantity);
    if (sorted_uniqued_cards != NULL) {
        printf("Uniqued cards: ");
        for (i = 0; i < sorted_uniqued_cards_quantity; i++) {
            printf("%d ", *sorted_uniqued_cards[i]);
        }
    }
    printf("\njokers: %d\n", joker_quantity);
    printf("Max sequence length: %d\n", max_sequence_length);*/




    delete [] sorted_uniqued_cards;

    fp = fopen(output_file, "w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    fprintf(fp, "%d", max_sequence_length);
    fclose(fp);

    return 0;
}