/******************************************************************************
 * stack.cc                                                                   *
 * Skeleton by Alistair Campbell                                              *
 * Completed by:  Oliver Keh                                                  *
 *                                                                            *
 * February 5, 2016                                                           *
 *                                                                            *
 * This file handles all of the functions to do with the stack. Its           *
 * importance derives from its required use in backtracking, an essential     *
 * element in the game of sudoku. This creates a stack that works on a LIFO   *
 * stack data structure with functions such as pop, push, top, and empty,     *
 * to handle the data collection for sudoku.
 *****************************************************************************/

#include "stack.h"
#include <iostream>
#include <assert.h>
 using namespace std;

stack::stack()
{
    _init();
}

stack::~stack()
{
    _destroy(); // remove all nodes
}

stack::stack(const stack & other)
{
    _init();      // initialize.
    _copy(other); // copy other stack
}

stack & stack::operator=(const stack & rhs)
{
    if (this != &rhs) { // avoid assign to yourself
        _destroy();     // get rid of any data we already have.
        _copy(rhs);     // copy right hand side.
    }
    return *this;       // allows chained assignments
}

// Private methods
void stack::_copy(const stack & other)
{
    stack temp; // temporary storage
    // copy all data from other to temp.
    for (node *p = other._top; p != NULL; p = p->next)
        temp.push(p->data);
    // now temp is the reverse of other;
    // copy all data to this stack.
    for (node *p = temp._top; p != NULL; p = p->next)
        push(p->data);
}

void stack::_init()
{
    // Initializes variables.
    _top = NULL;
    _size = 0;
}

void stack::_destroy()
{
    // Loops through linked list and deletes every node until list is empty.
    node *current;
    while (current != NULL) {
        current = _top;
        pop();
    }
}

// Public methods

void stack::push(const element & item)
{
    // Creates a new node and sets the data equal to an inputed item.
    node *p = new node;
    if (_top == NULL) {
        p -> data = item;
        p -> next = NULL;
        _top = p;
        _size++;
    }
    else {
        p -> data = item;
        p -> next = _top;
        _top = p;
        _size++;
    }
}


void stack::pop()
{
    // Removes a node from the list and deletes it once it is detached.
    if (_top != NULL) {
        node *p = _top;
        _top = _top -> next;
        delete p;
        _size--;
    }
}

stack::element stack::top() const
{
    return _top -> data; // bogus to compile
}

bool stack::empty() const
{
    return _size == 0; // bogus to compile
}

size_t stack::size() const
{
    return _size; // bogus to compile
}
