#include <iostream>

#include "bst.h"

void printEl(int& el)
{
    std::cout << el << " ";
}

int main()
{
    BST<int> tree({ 24, 12, 89, 10, 112, 8, 5 });
    // tree.push(24);
    // tree.push(12);
    // tree.push(89);
    // tree.push(10);
    // tree.push(112);
    // tree.push(8);
    // tree.push(5);

    tree.erase(12);
    tree.erase(24);

    //tree.erase(112);

    tree.forEach(printEl);

    std::cout << std::endl;

    std::cout << tree.min() << std::endl;
    std::cout << tree.max() << std::endl;

    return 0;
}