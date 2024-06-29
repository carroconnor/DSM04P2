#ifndef UNORDERED_H
#define UNORDERED_H
#include "linkedList.h"

template <class type>
class unorderedLinkedList : public linkedListType<type>
{
public:
    void insert(const type &newdata);
    void deleteNode(const type &deleteItem);
    bool search(const type &searchItem) const;
    void mergesort(int (*func)(type &firstObj, type &secondObj));
private:
    void mergeSortHelper(node<type>*& headRef, int (*func)(type &firstObj, type &secondObj));
    void splitList(node<type>* source, node<type>** frontRef, node<type>** backRef);
    node<type>* merge(node<type>* first, node<type>* second, int (*func)(type &firstObj, type &secondObj));
};

template<class type>
void unorderedLinkedList<type>::mergesort(int (*func)(type &firstObj, type &secondObj)) {
    mergeSortHelper(this->head, func);
}

template<class type>
void unorderedLinkedList<type>::mergeSortHelper(node<type>*& headRef, int (*func)(type &firstObj, type &secondObj)) {
    node<type>* head = headRef;
    node<type>* first;
    node<type>* second;

    // Base case: list is empty or has only one element
    if ((head == nullptr) || (head->link == nullptr)) {
        return;
    }

    // Split head into 'first' and 'second' sublists
    splitList(head, &first, &second);

    // Recursively sort the sublists
    mergeSortHelper(first, func);
    mergeSortHelper(second, func);

    // Merge the sorted lists together
    headRef = merge(first, second, func);
}

// Splits the list into two halves
template<class type>
void unorderedLinkedList<type>::splitList(node<type>* source, node<type>** frontRef, node<type>** backRef) {
    node<type>* fast;
    node<type>* slow;

    if (source == nullptr || source->link == nullptr) {
        *frontRef = source;
        *backRef = nullptr;
    } else {
        slow = source;
        fast = source->link;
        //find last element
        while (fast != nullptr) {
            fast = fast->link;
            if (fast != nullptr) {
                slow = slow->link;
                fast = fast->link;
            }
        }

        *frontRef = source;
        *backRef = slow->link;
        slow->link = nullptr;
    }
}

// Merges two sorted lists
template<class type>
node<type>* unorderedLinkedList<type>::merge(node<type>* first, node<type>* second, int (*func)(type &firstObj, type &secondObj)) {
    node<type>* result = nullptr;

    // Base cases
    if (first == nullptr)
        return second;
    else if (second == nullptr)
        return first;

    // Pick either first or second and recur
    if (func(*(first->data), *(second->data)) <= 0) {
        result = first;
        result->link = merge(first->link, second, func);
    } else {
        result = second;
        result->link = merge(first, second->link, func);
    }
    return result;
}

template <class type>
inline void unorderedLinkedList<type>::insert(const type &newdata)
{
    node<type> *newNode;
    newNode = new node<type>;
    newNode->data = new type(newdata);
    newNode->link = nullptr;

    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
        this->count++;
    }
    else
    {
        this->tail->link = newNode;
        this->tail = newNode;
        this->count++;
    }
}

template <class type>
inline void unorderedLinkedList<type>::deleteNode(const type &deleteItem)
{
    node<type> *current;
    node<type> *trailCurrent;
    bool found;
    if (this->isEmptyList())
        throw std::out_of_range("Cannot delete from empty list.");
    else
    {
        if (*(this->head->data) == deleteItem)
        {
            current = this->head;
            this->head = this->head->link;
            this->count--;
            if (this->head == nullptr)
                this->tail = nullptr;
            delete current;
        }
        else
        {
            found = false;
            trailCurrent = this->head;
            current = this->head->link;
            while (current != nullptr && !found)
            {
                if (*(current->data) != deleteItem)
                {
                    trailCurrent = current;
                    current = current->link;
                }
                else
                    found = true;
            }
            if (found)
            {
                trailCurrent->link = current->link;
                this->count--;
                if (this->tail == current)
                    this->tail = trailCurrent;
                delete current;
            }
            else
                throw std::out_of_range("Item not found in list. Cannot delete.");
        }
    }
}

template <class type>
inline bool unorderedLinkedList<type>::search(const type &searchItem) const
{
    node<type> *current;
    bool found = false;
    current = this->head;
    while (current != nullptr && !found)
    {
        if (*(current->data) == searchItem)
        {
            found = true;
        }
        else
        {
            current = current->link;
        }
    }
    return found;
}

#endif