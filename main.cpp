#include <iostream>
#include <fstream>
#include "unorderedLinkedList.h"
#include "product.h"

int compareDescription(product &item1, product &item2);
int comparePrice(product &item1, product &item2);
int compareRating(product &item1, product &item2);

int main()
{
    
    unorderedLinkedList<product> listByPrice;
    unorderedLinkedList<product> listByDescription;
    unorderedLinkedList<product> listByRating; 

    read the product information from the file

    std::cout << std::endl;
    std::cout << "original list for ordering by description: " << std::endl;
    listByDescription.print(std::cout, "\n"); // prints all of the items in the list and uses \n as the separator character.
    std::cout << std::endl
              << std::endl;
    std::cout << "original list for ordering by Price: " << std::endl;
    listByPrice.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;
    std::cout << "original list for ordering by rating" << std::endl;
    listByRating.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    merge sort the 3 lists
    Don't forget to modify unorderedLinkedList.h to add the merge sort functionality.

    std::cout << "mergeSorted by description product list: " << std::endl;
    listByDescription.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;
    std::cout << "mergeSorted by price product list: " << std::endl;
    listByPrice.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    std::cout << "mergeSorted by rating product list: " << std::endl;
    listByRating.print(std::cout, "\n");
    std::cout << std::endl
              << std::endl;

    return 0;
}
