#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include "Map.h"
#include <cassert>

using namespace std;

Map::Map() {                                            //Default constructor, creates empty class

    first = nullptr;                                    //set 
    last = nullptr;
    counter = 0;

}

Map::Map(Map* &m){                                      //Copy constructor


    first = nullptr;
    last = nullptr;
    counter = 0;

    if (m->first == NULL) {                             //if the map being copied is empty, make the new class empty as well

        first = nullptr;
        last = nullptr;

    }
    else {

        node* current = first;                          //create a node pointing the the first node of the new map                     
        node* mCurrent = m->first;                      //create a node pointing to the first node of the map to copy

        while (mCurrent->getNext() != nullptr) {        //repeatedly: 

            insert(mCurrent->getKey(), mCurrent->getData());    //add nodes from the map to copy to the new map with the corresponding key/value pairs
            mCurrent = mCurrent->getNext();             //move to the next node in the map to copy

        }                                               //once the map to copy is empty, exit and complete creation of new map

    }   
  

}

Map::~Map() {

    node* ptr = this->first;                            //create a node at the start of the target map

    while (ptr != nullptr) {                            //repeatedly:
        node* nextNode = ptr->getNext();                //create another node and set it to ptr's next node
        delete ptr;                                     //then delete ptr
        ptr = nextNode;                                 //then set ptr to the nextNode 
    }                                                   //Once the whole map has been deleted, exit

}

Map& Map::operator=(Map* &rhs) {                        //assignment operator

    std::swap(this->first, rhs->first);                 //swap lhs map first node with rhs map first node
    std::swap(this->last, rhs->last);                   //swap lhs map last node with rhs map last node

    return *this;                                       //return the lhs with it's new values

}

    bool Map::empty() const {                           //this function will check if the map is empty

        if (this->first == NULL && counter == 0) {      //check if first node is null and the counter is 0
            return true;                                //if this is the case, the map is empty (true)
        }

        return false;                                   //if not the case, the map has something in it (false)

    }

    int Map::size() const {                             //this function will return the size of the map

        return Map::counter;                            //a counter tracks the number of nodes in the map, and is returned

    }

    bool Map::insert(const KeyType& key, const ValueType& value) {  //this function adds nodes to the map

        node* n1 = new node(key, value);                //create two nodes, n1 which will be the node that is added to the map
        node* itr = this->first;                        //and itr, which will "iterate" through the map

        while (itr != NULL) {                           //repeatedly:

            if (itr->getKey() == key)                   //check if the inputted key to be added is already in the map
                return false;                           //if so, return false

            itr = itr->getNext();                       //check the next node
                                                        //until itr reaches null
        }                                              

        if (counter == 0) {                             //check if the map is empty
            first = n1;                                 //if so, simply set first and last nodes of the map to n1
            last = n1;
            counter = 1;                                //if the map is truly empty, the counter should only be 1 after adding a single node                   

            return true;
        }
        else {                                          //if it's not empty, add the last node onto the end of the map

            n1->setPrevious(last);                      //set n1's previous node to the last node
            n1->setNext(last->getNext());               //set n1's next node to whatever the last node's next node is (should be nullptr)
            last->setNext(n1);                          //then set last's next to n1
            last = n1;                                  //then make last = n1
            counter++;                                  //finally, increment the counter
                
            return true;
        }


        

    }

    bool Map::update(const KeyType& key, const ValueType& value) {  //this function will update an existing node in the map

        node* itr = this->first;                        //create a node to iterate through the map

        while (itr != NULL) {                           //while itr is not at the end of the map,

            if (itr->getKey() == key) {                 //check itr's key value
                                                        //if itr's key is equal to the inputted key,
                itr->setData(value);                    //set the data of the node that itr currently points to the the value inputted
                return true;

            }

            itr = itr->getNext();                       //move to the next node

        }

        return false;                                   //if, by the end of the map, the target key is not found, return false

    }

    bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {  //Similar the update(), this function will create a new node with the inputs if it cannot be found
        
        node* itr = this->first;                        //create a node to search through the map

        while (itr != NULL) {                           //while itr is not at the end of the map

            if (itr->getKey() == key) {                 //check the given key with itr's key, and if they match

                itr->setData(value);                    //set itr's current node value with the input value
                return true;    


            }
                
            itr = itr->getNext();                       //move on to the next node

        }
                                                        //if it couldn't be found in the map,
        node* n1 = new node(key, value);                //create a new node with the input key and value

        if (counter == 0) {                             //check if the map is empty before inserting
            first = n1;                                 //if so, set first node and last node to n1
            last = n1;
            counter = 1;                                //counter should only be 1 if this is the case

            return true;
        }
        else {

            n1->setPrevious(last);                      //if not, add to end of map, just like insert()
            n1->setNext(last->getNext());
            last->setNext(n1);
            last = n1;
            counter++;

            return true;
        }


    }

    bool Map::erase(const KeyType& k) {                 //this function will erase the input key, along with the value

        node* itr = this->first;                        //create a node to search through map
        node* left = itr->getPrevious();                //as well as two nodes to point to itr's previous
        node* right = itr->getNext();                   //and next value

        if (counter == 1) {                             //if the map only has one value

            this->first = NULL;                         //set first and last nodes to null
            this->last = NULL;
            counter = 0;                                //the map is empty, thus counter = 0
            return true;

        }


        while (right != NULL) {                         //if the map has more than one node, search until reaching the last node
            
            if (itr == this->first && itr->getKey() == k) { //if the target node is found at first

                first = first->getNext();               //set first to first's next node
                first->setPrevious(NULL);               //then set first's previous to null

                delete itr;                             //then delete itr
                counter--;                              //and decrement the counter

                return true;

            }

            else if (itr->getKey() == k ) {             //if target node is between the ends

                left->setNext(right);                   //set the itr's previous node to itr's next node
                right->setPrevious(left);               //then set itr's next node to itr's previous

                delete itr;                             //then delete itr
                counter--;                              //and decremement the node count
          
                return true;

            }

            itr = itr->getNext();                       //move all nodes to their next positions
            left = itr->getPrevious();
            right = itr->getNext();

            
        }
                                                        //by this point, itr is at last node, and key was not found
        if (itr->getKey() == k) {                       //check if last node contains the key

            last = left;                                //if found, set last to itr's previous node
            left->setNext(nullptr);                     //set itr's previous node's next node to nullptr
            right = nullptr;                            //set itr's next node to nullptr

            delete itr;                                 //delete itr
            counter--;                                  //and finally decrement

            return true;

        }

        return false;                                   //at this point, the node was not found, return false;

    }

    bool Map::contains(const KeyType& key) const {      //this function will check if the map contains the input key

        node* itr = this->first;                        //create node to search map

        while (itr->getNext() != nullptr) {             //while itr's next node is not null

            if (itr->getKey() == key) {                 //check to see if the input key and itr's key match

                return true;                            //return true if so

            }

            itr = itr->getNext();                       //set itr to the next node and repeat

        }

        if (itr->getKey() == key) {                     //check if last node contains the target key

            return true;                                //if so, return true

        }

        return false;                                   //if not, then exit

    }

    bool Map::get(const KeyType& key, ValueType& value) const { //this function will, given a key, set a precreated variable to the value of that key

        node* itr = this->first;                        //iterator node

        while (itr != nullptr) {                        //while the iterator node is not at the end of the map
            
            if (itr->getKey() == key) {                 //check if itr's key matches the given key

                value = itr->getData();                 //if true, set value to itr's node value
                return true;

            }

            itr = itr->getNext();                       //move itr to the next node

        }

        return false;                                   //if the key isn't found, return false
                    
    }

    bool Map::get(int i, KeyType& key, ValueType& value) const {    //similar to the two argument get function, this function will find the node at the given position,
                                                                    //i.e. i = 1, so set key and value to the map's first node key and value

        int counts = 0;                                 //create variable counts which will track the current position of the iterator node

        if (i <= this->size()) {                        //check if the given i is within the bounds of the map

            node* itr = this->first;                    //set itr to the first position

            while (itr != nullptr) {                    //iterate through the map

                if (counts == i) {                      //check if counts has moved to the desired position in the map
                                                        //once it has,
                    key = itr->getKey();                //set key to the key of the current position's node
                    value = itr->getData();             //and set the value to the value of the current position's node

                    return true;

                }

                counts++;                               //increment the counts
                itr = itr->getNext();                   //move to the next position

            }

        }
                                                        //if the input i could not be reached, return false
        return false;

    }

    void Map::swap(Map& other) {                        //this function will swap the pairs in two maps

        Map* temp = new Map(other);                     //create a temp map that contains the data from the second map
        other = *this;                                  //set the second map equal the first map
        *this = temp;                                   //then set the calling map to temp, which holds values from the second map

    }

    bool combine(const Map& m1, const Map& m2, Map& result) {   //this non-member function takes two maps, combines them, and then inserts those nodes into a new map
                                                                //if a pair appears in both of the maps, it is only inserted once into the new map
                                                                //if a key appears in both maps, but the values are different, this func returns false;

        KeyType k1;                                     //create a variable to hold the keys from the first map
        ValueType v1,v2;                                //create two variables to hold the values from both maps, respectively

        bool status = false;                            //by default, set the status of the func to false

        result = m1;                                    //set the resulting map equal to m1, this way we only have to compare the resulting map to m2,
                                                        //instead of comparing m1 to m2, then inserting and erasing nodes into resulting map

        for (int i = 0; i < m2.size(); i++) {           //while the three-argument get function checks the second map

            k1 = "";
            v1 = 0;                                     //reset the values of k1, v1, and v2
            v2 = 0;
            
            m2.get(i, k1, v1);                          //get the key and value from m2
            result.get(k1, v2);                         //using the key value from m2, get the corresponding value from result (if it exists in result)

            if (result.contains(k1) && v2 == v1) {      //if the key/value pair matches perfectly

                status = true;                          //set the status to true
                                                        //because result is set equal to m1, this pair should already be in result, so we don't need to insert it
                        
            }
            else if (result.contains(k1) && v2 != v1) { //check if key appears in both maps, then check if values are the same
                                                        //if values aren't the same, set status to false
                result.erase(k1);                       //and erase the node, because the values are different
                status = false;

            }
            else if(!result.contains(k1)) {             //check if the current pair is in m2 but not result

                result.insert(k1, v1);                  //if so, add it to result
                                                        //because there are no values to compare, status does not change
            }

        }

        return status;                                  //return the status

    }

    void subtract(const Map& m1, const Map& m2, Map& result) {  //this map will compare two maps, erase the nodes that appear in both maps, and then insert the remaining nodes into a new map
          
        KeyType k = "";
        ValueType v = 0;                                //create variables to hold keys and values 

        result = m1;                                    //set resulting map to m1
                                                        //like combine function, doing this means we can simply compare result to m2 instead of m1 to m2, then adding/erasing to result

        for (int i = 0; i < m2.size(); i++) {           //iterate through m2

            m2.get(i, k, v);                            //take the key and value of the current node in m2

            result.erase(k);                            //erase the key from result map (if it doesn't appear in result nothing will be erased)

            k = "";                                     //reset the value of k

        }

        

    }

    void fate() {

        Map m;
        assert(m.insert("Fred", 123));
        assert(m.insert("Ethel", 456));
        assert(m.size() == 2);

        double d = 42;

        assert(m.get("Fred", d) && d == 123);
        d = 42;
        string s1;
        assert(m.get(0, s1, d) &&
            ((s1 == "Fred" && d == 123) || (s1 == "Ethel" && d == 456)));
        string s2;
        assert(m.get(1, s2, d) && s1 != s2 &&
            ((s2 == "Fred" && d == 123) || (s2 == "Ethel" && d == 456)));

    }

    int main() {

        fate();
        cout << "Passed all test" << endl;

        //KeyType k = "";
        //ValueType v = NULL;

        //Map* m = new Map();
        //Map* m2 = new Map();
        //Map* m3 = new Map();
        //Map* mR = new Map();

        //m->insert("Jennie", 23.98);
        //m->insert("Rose", 40.23);
        //m->insert("Jisoo", 32.16);
        //m->insert("Lisa", 0.01);

        //m2->insert("Richtofen", 100.18);
        //m2->insert("Lisa", 32.16);
        //m2->insert("Takeo", 23.34);
        //m2->insert("Dempsey", 09.21);
        //m2->insert("Rose", 0.01);
        //m2->insert("Nikolai", 93.28);

        //mR->insert("Arthur Morgan", 97.88);

        //Map* m4 = new Map(*m);
        //m4->showList();

        //cerr << "m: ";
        //m->showList();

        //cerr << "m2: ";
        //m2->showList();

        //cerr << "mR: ";
        //mR->showList();

        //cerr << "Map 01: ";
        //m->showList();

        //cerr << "Updating TIMOTHY" << endl;
        //m->update("Timothy", 13.6);                     //Testing true update
        //cerr << "Update complete\n" << endl;

        //cerr << "Updating TIM" << endl;
        //m->update("Tim", 33.55);                        //Testing false update
        //cerr << "Update complete\n" << endl;

        //m->showList();

        //cerr << "Erasing REYNA" << endl;
        //m->erase("Reyna");                              //Testing true erase
        //cerr << "Erase complete\n" << endl;

        //m->showList();

        //cerr << "Erasing TIM" << endl;
        //m->erase("Tim");                                //Testing false erase
        //cerr << "Erase complete\n" << endl;

        //cerr << "Erasing LISA" << endl;
        //m->erase("Lisa");                              //Testing erase on last node
        //cerr << "Erase complete\n" << endl;

        //m->showList();

        //cerr << "Erasing TIMOTHY" << endl;
        //m->erase("Timothy");                            //Testing erase on first node
        //cerr << "Erase complete" << endl;

        //m->showList();
        //
        //cerr << "InsertOrUpdating TIMOTHY" << endl;
        //m->insertOrUpdate("Timothy", 39.03);            //Testing insertOrUpdate on nonexistent key
        //cerr << "InsertOrUpdate complete\n" << endl;

        //m->showList();

        //cerr << "InsertOrUpdating GRIFFIN" << endl;
        //m->insertOrUpdate("Griffin", 98.62);            //Testing insertOrUpdate on existing key
        //cerr << "Update complete\n" << endl;

        //m->showList();

        //cerr << "Checking if DLL contains ROSE" << endl;
        //m->contains("Rose");                            //Testing contains on nonexistent key
        //cerr << "Check complete\n" << endl;


        //cerr << "Checking if DLL contains JOSHUA" << endl;
        //m->contains("Joshua");                          //Testing contains on existing key
        //cerr << "Check complete\n" << endl;

        //m->get("Jisoo", v);

        //cerr << v << endl;

        //Map* m2C = new Map(*m2);                          //Testing assignment operator and copy constructor
        //cerr << "m2C: ";
        //m2C->showList();

        //m2->swap(*m);                                   //Testing swap func

        //subtract(*m, *m2, *mR);                           //Testing subtract func
        //mR->showList();


        //combine(*m, *m2, *mR);                          //Testing combine func
        //cerr << "Combined mR: ";
        //mR->showList();

    }

