#pragma once
/*
  dlist.h
  Doubly-linked lists of ints
 */
class dlist {
  public:
    dlist() { }

    struct node {
        int value;
        node* next;
        node* prev;
    };

    node* head() const { return _head; }
    node* tail() const { return _tail; }

    // **** Implement ALL the following methods ****

    // Returns the node at a particular index (0 is the head). If n >= size()
    // return nullptr; if n < 0, return the head of the list.
    // Must run in O(n) time.
    node* at(int v) const {
        int a = 0;
        node* n = _head;
        while(v != 0 && n != nullptr) {
            v--;
            n = n -> next;
        }
        return n;
    }

    // Insert a new value, after an existing one. If previous == nullptr, then
    // the list is assumed to be empty.
    // Must run in O(1) time.
    void insert(node *previous, int value) {
        if(previous == nullptr) {
            _head = new node{value, _head, nullptr};
            if(_tail == nullptr) {
                _tail = _head;
            }
            if(_head -> next != nullptr) {
                _head -> next -> prev = _head;
            }
        }
        else {
            node* n = new node{value, previous -> next, previous};
            previous -> next = n;
            if(n -> next != nullptr) {
                n -> next -> prev = n;
            }
            if(previous == _tail) {
                _tail = n;
            }
        }
    }

    // Delete the given node. Should do nothing if which == nullptr.
    // Must run in O(1) time.
    void remove(node* which) {
        if(empty() || which -> next == nullptr) {
            return;
        }
        else {
            if(_tail == which)
                _tail = which -> prev;
            if(_head == which)
                _head = which -> next;
            if(which -> prev != nullptr)
                which -> prev -> next = which -> next;
            if(which -> next != nullptr)
                which -> next -> prev = which -> prev;
            delete which;
        }
    }

    // Add a new element to the *end* of the list
    // Must run in O(1) time.
    void push_back(int value) {
        insert(_tail, value);
    }

    // Add a new element to the *beginning* of the list
    // Must run in O(1) time.
    void push_front(int value) {
        if(empty()) {
            node* n = new node;
            n -> value = value;
            n -> next = nullptr;
            n -> prev = nullptr;
            _head = n;
            _tail = n;
        }
        else {
            node* n = new node;
            n -> value = value;
            n -> prev = nullptr;
            n -> next = _head;
            _head -> prev = n;
            _head = n;
        }
    }

    // Remove the first element. 
    // If the list is empty, do nothing.
    // Must run in O(1) time
    void pop_front() {
        if(empty()) {
            
        }
        else if(_head == _tail && _head != nullptr) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else {
            node* n = _head;
            _head -> next -> prev = nullptr;
            _head = _head -> next;
            delete n;
        }
    }

    // Remove the last element. 
    // If the list is empty, do nothing.
    // Must run in O(1) time
    void pop_back() {
        if(empty()) {
            
        }
        else if(_head == _tail && _head != nullptr) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else {
            node* n = _tail;
            _tail -> prev -> next = nullptr;
            _tail = _tail -> prev;
            delete n;
        }
    }

    // Get the size of the list
    // Should run in O(n) time at the worst
    int size() const {
        int a = 0;
        node* n = _head;
        while(n != nullptr) {
            n = n -> next;
            a++;
        }
        return a;
    }

    // Returns true if the list is empty
    // Must run in O(1) time
    bool empty() const {
        return _head == nullptr;
    }

  private:
    node* _head = nullptr;
    node* _tail = nullptr;

    // Add any other private members you need
};

// **** Implement ALL the following functions ****

/* a == b
   Compares two lists for equality, returning true if they have the same
   elements in the same positions. (Hint: it is *not* enough to just compare
   pointers! You have to compare the values stored in the nodes.)

   Must run in O(m) time, where m is the length of the shorter of the two lists.
*/ 
inline bool operator== (const dlist& a, const dlist& b) {
    if(a.size() != b.size()) {
        return false;
    }
    dlist::node* c1 = a.head();
    dlist::node* c2 = b.head();
    while(c1 != nullptr){
        if(c1 -> value != c2 -> value){
            return false;
        }
        c1 = c1 -> next;
        c2 = c2 -> next;
    }
    return true;
}
    
/* a + b
   Returns a new list consisting of all the elements of a, followed by all the
   elements of b (i.e., the list concatenation).

   Must run in O(n) time in the length of the result (i.e., the length of a
   plus the length of b).
*/
inline dlist operator+ (const dlist& a, const dlist& b) {
    dlist c;
    if(a.empty() == true && b.empty() == true) {
        return c;
    }
    else if(a.empty() == true && b.empty() == false) {
        dlist::node* b2 = b.head();
        while(b2 != nullptr) {
            c.push_back(b2 -> value);
            b2 = b2 -> next;
        }
        return c;
    }
    else if(a.empty() == false && b.empty() == true) {
        dlist::node* a2 = a.head();
        while(a2 != nullptr) {
            c.push_back(a2 -> value);
            a2 = a2 -> next;
        }
        return c;
    }
    else {
        dlist::node* a2 = a.head();
        while(a2 != nullptr) {
            c.push_back(a2 -> value);
            a2 = a2 -> next;
        }
        dlist::node* b2 = b.head();
        while(b2 != nullptr) {
            c.push_back(b2 -> value);
            b2 = b2 -> next;
        }
        return c;
    }
}

/* reverse(l)
   Returns a new list that is the *reversal* of l; that is, a new list 
   containing the same elements as l but in the reverse order.

   Must run in O(n) time. 
*/
inline dlist reverse(const dlist& l) {
    dlist n;
    dlist:: node* a = l.tail();
    if(l.empty()) {
        return n;
    }
    else if(l.head() == l.tail() && l.head() != nullptr) {
        n.push_back(a -> value);
        return n;
    }
    else {
        while(a != nullptr) {
            n.push_back(a -> value);
            a = a -> prev;
        }
        return n;
    }
}