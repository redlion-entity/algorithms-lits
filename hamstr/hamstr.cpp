#include <iostream>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"
//#include <vector>
#include "_generate.h"

//using namespace std;

/*
 * Compare two nodes
 */
/*int compare_int(void* leftp, void* rightp)
{
    int left = (long)leftp;
    int right = (long)rightp;
    if (left < right)
        return -1;
    else if (left > right)
        return 1;
    else
    {
        assert (left == right);
        return 0;
    }
}*/
/*
 * Print RBTRee
 */
/*void print_tree_helper(node n, int indent)
{
    int i;
    if (n == NULL)
    {
        fputs("<empty tree>", stdout);
        return;
    }
    if (n->right != NULL)
    {
        print_tree_helper(n->right, indent + INDENT_STEP);
    }
    for(i = 0; i < indent; i++)
        fputs(" ", stdout);
    if (n->color == BLACK)
        cout<<(long)n->key<<endl;
    else
        cout<<"<"<<(long)n->key<<">"<<endl;
    if (n->left != NULL)
    {
        print_tree_helper(n->left, indent + INDENT_STEP);
    }
}*/

/*void print_tree(rbtree t)
{
    print_tree_helper(t->root, 0);
    puts("");
}*/

/*
 * Main Contains Menu
 */
/*
int main()
{
    int i;
    RBTree rbt;
    rbtree t = rbt.rbtree_create();
    for (i = 0; i < 12; i++)
    {
        int x = rand() % 10;
        int y = rand() % 10;
        print_tree(t);
        cout<<"Inserting "<<x<<" -> "<<y<<endl<<endl;
        rbt.rbtree_insert(t, (void*)x, (void*)y, compare_int);
        assert(rbt.rbtree_lookup(t, (void*)x, compare_int) == (void*)y);
    }
    for (i = 0; i < 15; i++)
    {
        int x = rand() % 10;
        print_tree(t);
        cout<<"Deleting key "<<x<<endl<<endl;
        rbt.rbtree_delete(t, (void*)x, compare_int);
    }
    return 0;
}*/

/*bool hasHamstersCombination(const int k, const int n, unsigned int* food, const unsigned int food_limit) {
    int *vector = NULL;
    int gen_result;
    bool result = false;

    vector = new int[k];

    // initialize
    gen_result = gen_comb_norep_lex_init(vector, k, n);

    //generate all successors
    while (gen_result == GEN_NEXT) {
        unsigned int sum = 0;

        for (int i = 0; i < k; i++) {
            sum += food[vector[i]];
        }

        if (sum <= food_limit) {
            result = true;
            break;
        }

        gen_result = gen_comb_norep_lex_next(vector, k, n);
    }

    if (vector != NULL) {
        delete [] vector;
    }

    return result;
}*/

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
    unsigned int lambda = median(A[(left + right)/2], A[left], A[right]);

    while (left < right) {
        while (A[left] < lambda) {
            left = left + 1;
        }

        while (A[right] > lambda) {
            right = right - 1;
        }

        if (left < right) {
            if (A[left] != A[right]) {
                std::swap(A[left], A[right]);
            }
            if (right - left == 1) {
                right = left;
            } else {
                left = left + 1;
                right = right - 1;
            }
        }
    }

    return left;





    /*if (l!=r)
        std::swap(A[l + rand() % (r - l)], A[r]);
    unsigned int x = A[r];
    int i = l-1;
    for (int j = l; j <= r; j++) {
        if (A[j] <= x)
            std::swap(A[++i],A[j]);
    }
    return i;*/
}

// Kth order statistic
unsigned int nth(const int k, unsigned int* A, const int length) {
    int l = 0, r = length - 1;
    for(;;) {
        int pos = partition(A, l, r);
        if (pos < k)
            l = pos + 1;
        else if (pos > k)
            r = pos - 1;
        else return A[k];
    }
}

unsigned int calculateFood(const int quantity, unsigned int* food, const int length) {
    unsigned int sum = 0;

    // find Kth oder statistic to divide the array into two parts larger and smaller
    nth(quantity - 1, food, length);

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
        //input_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/hamstr/inputData/11.in";
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

        // calculate thу food for each hamster
        for (i = 0; i < hamsters_quantity; i++) {
            hamster_food[i] = hamster_norm[i] + (middle - 1) * hamster_greed[i];
        }

        //if (hasHamstersCombination(middle, hamsters_quantity, hamster_food, food_limit)) {
        if (calculateFood(middle, hamster_food, hamsters_quantity) <= food_limit) {
            max_hamsters = middle;
            left = middle;
        } else {
            right = middle;
        }

        if (right - left == 1) {
            left = right;
        }

    } while (left < middle || middle < right);



    /*printf("Food limit: %d\n", food_limit);
    printf("Hamsters quantity: %d\n", hamsters_quantity);
//    for (i = 0; i < hamsters_quantity; i++) {
//        printf("%u %u\n", hamster_norm[i], hamster_greed[i]);
//    }
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