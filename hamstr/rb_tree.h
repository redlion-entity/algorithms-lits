//
// Created by Red Lion on 21.05.17.
//

#ifndef HAMSTR_RB_TREE_H
#define HAMSTR_RB_TREE_H

struct node
{
    int key;
    node *parent;
    char color;
    node *left;
    node *right;
};

class RBtree {
    node *root;
    node *q;

public :
    RBtree()
    {
        q=NULL;
        root=NULL;
    }
    void insert();
    void insertfix(node *);
    void leftrotate(node *);
    void rightrotate(node *);
    void del();
    node* successor(node *);
    void delfix(node *);
    void disp();
    void display( node *);
    void search();
};


#endif //HAMSTR_RB_TREE_H
