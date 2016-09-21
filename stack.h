#include <cstdlib>

class stack {
public:

  typedef double element;  // 

    // The critical four, for objects that manage dynamic data:
    stack();  // no-arg constructor:  creates empty stack
    ~stack(); // destructor
    stack(const stack & other); // copy constructor
    stack & operator=(const stack & rhs);  // assignment operator

    // The canonical stack operations:
    void push(const element & item);
    void pop();
    element top() const;
    bool empty() const;

    // The extra method because we care:
    size_t size() const;

private:

    // Internal node structure
    struct node {
      element data;
      node *next;
    };

    // Data elements
    node *_top;   // pointer to top node of the stack; NULL if stack empty
    size_t _size; // number of elements

    // Helper methods:
    void _copy(const stack & other);  // add all elements of other to this stack.  
                                      // Called by copy constructor and 
                                      // assignment operator
    void _init();      // initialize an empty stack.  Called by constructors
    void _destroy();   // remove all nodes.  Called by destructor and 
                       // assignment operator

};
