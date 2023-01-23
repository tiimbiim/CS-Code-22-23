#pragma once
#include <string>
#include <cassert>
using namespace std;

using KeyType = std::string;
using ValueType = double;

class Map
{
private:

    struct node {

        node* next;
        node* previous;
        ValueType v;
        KeyType k;

        node(KeyType id, ValueType newData) {

            v = newData;
            k = id;
            next = nullptr;
            previous = nullptr;

        };

        ~node() {

            v = 0;
            k = "";
            next = nullptr;
            previous = nullptr;

        }

        ValueType getData() { return v; }
        void setData(ValueType newData) { v = newData; }
        KeyType getKey() { return k; }
        void setKey(KeyType id) { k = id; }

        node* getNext() { return next; }
        node* getPrevious() { return previous; }
        void setNext(node* newNext) { next = newNext; }
        void setPrevious(node* newPrevious) { previous = newPrevious; }

        string showNode() {

            stringstream ss;
            ss << " "
                << this
                << " Node[Next: " << next
                << " Previous: " << previous
                << " v: " << v
                << " k: " << k
                << "]";

            return ss.str();

        }

    };

    node* first = NULL;
    node* last = NULL;
    int counter = 0;

public:
    Map();              // Create an empty map (i.e., one with no key/value pairs)
    Map(Map* &m);       // Copy constructor
    ~Map();             // Destructor

    bool empty() const; // Return true if the map is empty, otherwise false.

    int size() const;   // Return the number of key/value pairs in the map.

    bool insert(const KeyType& key, const ValueType& value);
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map).

    bool update(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // If key is not equal to any key currently in the map then add it and 
    // return true. In fact this function always returns true.

    bool erase(const KeyType& key);
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.

    bool contains(const KeyType& key) const;
    // Return true if key is equal to a key currently in the map, otherwise
    // false.

    bool get(const KeyType& key, ValueType& value) const;
    // If key is equal to a key currently in the map, set value to the
    // value in the map that that key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.

    bool get(int i, KeyType& key, ValueType& value) const;
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of one of the key/value pairs in the map and return
    // true.  Otherwise, leave the key and value parameters unchanged and
    // return false.  (See below for details about this function.)

    void swap(Map& other);
    // Exchange the contents of this map with the other one.

    void showList() { //FOR TESTING ONLY

        int n = 1;
        cout << endl
            << " First:" << first
            << " Last:" << last
            << " Counter:" << counter << endl;

        node* p = this->first;

        while (p != nullptr) {

            cout << n++ << "  "
                << p->showNode() << endl;

            p = p->getNext();

        }

        cout << "\n" << endl;

    }

    Map& operator= (Map* &rhs);

};