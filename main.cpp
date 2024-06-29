#include <iostream>
#include <fstream>
#include "unorderedLinkedList.h"
#include "product.h"

/* Program name: mergeSortProducts.cpp
    * Author: Carr O'Connor
    * Date last updated: 6/28/2024
    * Purpose: Implement and invoke mergesort that takes a function pointer as a parameter
*/

int compareDescription(product &item1, product &item2);
int comparePrice(product &item1, product &item2);
int compareRating(product &item1, product &item2);

int main()
{
    unorderedLinkedList<product> listByPrice;
    unorderedLinkedList<product> listByDescription;
    unorderedLinkedList<product> listByRating; 

    std::ifstream inputFile("products.txt");
    if(!inputFile.is_open()){
        throw std::invalid_argument("Error opening file");
    }

    //build our lists by reading from the file given
    std::stringstream ss;
    ss << inputFile.rdbuf();
    int index = 1;
    double currentPrice;
    std::string currentDesc;
    std::string currentNum;
    double currentRating;
    while(ss.good()){
        std::string currentLine;
        std::getline(ss, currentLine, '\n');
        if(currentLine != ""){
            if(index == 1){
                currentPrice = std::stod(currentLine);
            } else if (index == 2){
                currentDesc = currentLine;
            } else if (index == 3) {
                currentNum = currentLine;
            }
            else{
                currentRating = std::stod(currentLine);
                product prod = product(currentPrice, currentDesc, currentNum, currentRating);
                listByPrice.insert(prod);
                listByDescription.insert(prod);
                listByRating.insert(prod);
            }
        }
        if(index >= 4)
            index = 0;
        index++;
    }


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

    listByDescription.mergesort(compareDescription);
    listByPrice.mergesort(comparePrice);
    listByRating.mergesort(compareRating);

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

//compare products by description
int compareDescription(product &firstProd, product &secondProd){
    if(firstProd.getDescription() < secondProd.getDescription()){
        return -1;
    }
    if(firstProd.getDescription() == secondProd.getDescription()){
        return 0;
    }
    return 1;
}

//compare products by price
int comparePrice(product &firstProd, product &secondProd){
    if(firstProd.getPrice() < secondProd.getPrice()){
        return -1;
    }
    if(firstProd.getPrice() == secondProd.getPrice()){
        return 0;
    }
    return 1;
}

//compare products by rating
int compareRating(product &firstProd, product &secondProd){
     if(firstProd.getRating() < secondProd.getRating()){
        return -1;
    }
    if(firstProd.getRating() == secondProd.getRating()){
        return 0;
    }
    return 1;
}
