#include <iostream>

#define MAX(a, b)   ((a > b) ? a : b)
#define MIN(a, b)   ((a < b) ? a : b)

int median(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned int max;
    unsigned int min;

    max = MAX(a, MAX(b,c));
    min = MIN(a, MIN(b,c));

    return (a + b + c) - min - max;
}

int partition(unsigned int* A, int left, int right) {
    int idx = left;
    unsigned int lambda = median(A[(left + right)/2], A[left], A[right]);

    while (left < right) {
        while (A[left] < lambda) {
            left = left + 1;
        }

        if (left <= right) {
            idx = left;
        } else {
            idx = right;
        }

        while (A[right] > lambda) {
            right = right - 1;
        }

        if (left < right) {
            if (A[left] != A[right]) {
                std::swap(A[left], A[right]);
            }
            left = left + 1;
            right = right - 1;
        }
    }

    return idx;
}

// Partial quick sorting
void qSort(const int k, unsigned int* A, const int length) {
    int l = 0, r = length - 1;
    for(;;) {
        int pos = partition(A, l, r);

        if (pos < k)
            l = pos == l ? pos + 1 : pos;
        else if (pos > k)
            r = pos == r ? pos - 1 : pos;
        else return;
    }
}

unsigned long int calculateFood(const int quantity, unsigned int* food, const int length) {
    unsigned long int sum = 0;

    // partial quick sorting to divide the array into two parts larger and smaller
    qSort(quantity - 1, food, length);

    for (int i = 0; i < quantity; i++) {
        sum += food[i];
    }

    return sum;
}

int main(int argc, char *argv[]) {
    char const *input_file, *output_file;
    FILE *fp = NULL;
    unsigned int food_limit;
    int hamsters_quantity, left, right, middle, max_hamsters = 0;
    unsigned int *hamster_norm = NULL;
    unsigned int *hamster_greed = NULL;
    unsigned int *hamster_food = NULL;
    int i = 0;

    if (argc >= 2) {
        input_file = argv[1];
    } else {
        //input_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/hamstr/inputData/12.in";
        //input_file = "D:\\Projects\\GitHub\\algorithms-lits\\hamstr\\inputData\\12.in";
        input_file = "hamstr.in";
    }

    if (argc >= 3) {
        output_file = argv[2];
    } else {
        //output_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/hamstr/hamstr.out";
        //output_file = "D:\\Projects\\GitHub\\algorithms-lits\\hamstr\\hamstr.out";
        output_file = "hamstr.out";
    }

    // read data from file
    fp = fopen(input_file, "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    fscanf(fp, "%d", &food_limit);
    fscanf(fp, "%d", &hamsters_quantity);

    hamster_norm = new unsigned int[hamsters_quantity];
    hamster_greed = new unsigned int[hamsters_quantity];
    hamster_food = new unsigned int[hamsters_quantity];

    while(fscanf(fp, "%u %u", &hamster_norm[i], &hamster_greed[i]) == 2) {
        i++;
    }
    fclose(fp);

    left = 1;
    right = hamsters_quantity;

    do {
        middle = (right + left) / 2;

        // calculate the food for each hamster
        for (i = 0; i < hamsters_quantity; i++) {
            hamster_food[i] = hamster_norm[i] + (middle - 1) * hamster_greed[i];
        }

        if (calculateFood(middle, hamster_food, hamsters_quantity) <= food_limit) {
            max_hamsters = middle;
            left = middle;
        } else {
            right = middle;
        }

        if (right - left == 1) {
            if (left == middle || left == max_hamsters) {
                left = right;
            } else {
                middle = left - 1;
                right = left;
            }
        }

    } while (left < middle || middle < right);



    /*printf("Food limit: %d\n", food_limit);
    printf("Hamsters quantity: %d\n", hamsters_quantity);
    for (i = 0; i < hamsters_quantity; i++) {
        printf("%u %u\n", hamster_norm[i], hamster_greed[i]);
    }
    printf("Hamsters: %d\n", max_hamsters);*/





    if (hamster_norm != NULL) {
        delete [] hamster_norm;
    }
    if (hamster_greed != NULL) {
        delete [] hamster_greed;
    }
    if (hamster_food != NULL) {
        delete [] hamster_food;
    }

    fp = fopen(output_file, "w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    fprintf(fp, "%d", max_hamsters);
    fclose(fp);

    return 0;
}