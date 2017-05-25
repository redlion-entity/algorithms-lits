#include <iostream>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

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


int main(int argc, char *argv[]) {
    char *input_file, *output_file;
    FILE *fp = NULL;
    unsigned int food_limit, norm, greed;
    int hamsters_quantity;
    unsigned int **hamster_norm = NULL;
    unsigned int **hamster_greed = NULL;
    int i = 0;

    if (argc >= 2) {
        input_file = argv[1];
    } else {
        input_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/hamstr/inputData/01.in";
        //input_file = "lngpok.in";
    }

    if (argc >= 3) {
        output_file = argv[2];
    } else {
        output_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/hamstr/hamstr.out";
        //output_file = "lngpok.out";
    }

    // read data from file
    fp = fopen(input_file, "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    fscanf(fp, "%d", &food_limit);
    fscanf(fp, "%d", &hamsters_quantity);

    hamster_norm = new unsigned int*[hamsters_quantity];
    hamster_greed = new unsigned int*[hamsters_quantity];

    while(fscanf(fp, "%u %u", &hamster_norm[i], &hamster_greed[i]) == 2) {
        i++;
    }
    fclose(fp);





    printf("Food limit: %d", food_limit);
    printf("Hamsters quantity: %d", hamsters_quantity);
    for (i = 0; i < hamsters_quantity; i++) {
        printf("%d %d", *hamster_norm[i], *hamster_greed[i]);
    }




    if (hamster_norm != NULL) {
        delete [] hamster_norm;
    }
    if (hamster_greed != NULL) {
        delete [] hamster_greed;
    }

    /*fp = fopen(output_file, "w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    fprintf(fp, "%d", max_sequence_length);
    fclose(fp);*/

    return 0;
}