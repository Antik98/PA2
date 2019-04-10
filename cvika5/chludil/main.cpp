#include "bst.h"

int main()
{
    BST tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(2);
    tree.insert(7);
    tree.insert(0);
    tree.insert(2);
    cout << tree << endl << endl;
    tree.remove(0);
    cout << tree << endl << endl;
    tree.remove(5);
    cout << tree << endl << endl;
    tree.insert(9);
    tree.insert(10);
    tree.insert(4);
    cout << tree << endl << endl;
    tree.remove(9);
    cout << tree << endl << endl;

    BST tree2 = tree;   // zde se vola copy contructor
    cout << tree2 << endl << endl;

    BST tree3;
    tree3 = tree2;      // zde se vola operator =

    cout << tree3 << endl << endl;

    return 0;
}