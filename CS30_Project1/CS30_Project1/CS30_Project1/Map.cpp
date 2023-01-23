#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include "Map.h"
#include <cassert>

using namespace std;

Map::Map() {

    first = nullptr;
    last = nullptr;
    counter = 0;

}

Map::Map(Map* &m){


    first = nullptr;
    last = nullptr;
    counter = 0;

    if (m->first == NULL) {

        first = nullptr;

    }
    else {

        node* current = first;
        node* mFirst = m->first;
        node* mCurrent = mFirst;

        while (mCurrent->getNext() != nullptr) {

            insert(mCurrent->getKey(), mCurrent->getData());
            mCurrent = mCurrent->getNext();

        }

    }   
  

}

Map::~Map() {

    node* ptr = this->first;

    while (ptr != nullptr) {
        node* nextNode = ptr->getNext();
        delete ptr;
        ptr = nextNode;
    }

}

Map& Map::operator=(Map* &rhs) {

    std::swap(this->first, rhs->first);
    std::swap(this->last, rhs->last);

    return *this;

}

    bool Map::empty() const {

        if (this->first == NULL) {
            return true;
        }

        return false;

    }

    int Map::size() const {

        return Map::counter;

    }

    bool Map::insert(const KeyType& key, const ValueType& value) {

        node* n1 = new node(key, value);
        node* itr = this->first;

        while (itr != NULL) {

            if (itr->getKey() == key)
                return false;

            itr = itr->getNext();

        }

        if (counter == 0) {
            first = n1;
            last = n1;
            counter = 1;

            return true;
        }
        else {

            n1->setPrevious(last);
            n1->setNext(last->getNext());
            last->setNext(n1);
            last = n1;
            counter++;

            return true;
        }


        

    }

    bool Map::update(const KeyType& key, const ValueType& value) {

        node* itr = this->first;

        while (itr != NULL) {

            if (itr->getKey() == key) {

                itr->setData(value);
                return true;

            }

            itr = itr->getNext();

        }

        cerr << "Target key not found\n" << endl;
        return false;

    }

    bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
        
        node* itr = this->first;

        while (itr != NULL) {

            if (itr->getKey() == key) {

                itr->setData(value);

                cerr << "Target pair was found and updated\n" << endl;
                return true;


            }
                
            itr = itr->getNext();

        }

        cerr << "Target key was not found, creating node" << endl;

        node* n1 = new node(key, value);

        if (counter == 0) {
            first = n1;
            last = n1;
            counter = 1;

            return true;
        }
        else {

            n1->setPrevious(last);
            n1->setNext(last->getNext());
            last->setNext(n1);
            last = n1;
            counter++;

            return true;
        }


    }

    bool Map::erase(const KeyType& k) {

        node* itr = this->first;
        node* left = itr->getPrevious();
        node* right = itr->getNext();

        if (counter == 1) {

            this->first = NULL;
            this->last = NULL;
            counter = 0;
            //cerr << "First deleted" << endl;  
            return true;

        }


        while (right != NULL) {
            
            if (itr == this->first && itr->getKey() == k) {

                cerr << "Target key found at first!" << endl;

                first = first->getNext();
                first->setPrevious(NULL);

                cerr << "Deleting " << itr->getKey() << endl;

                delete itr;

                cerr << "Deleted " << endl;

                counter--;

                return true;

            }

            else if (itr->getKey() == k ) {

                cerr << "Target key found before last!" << endl;

                left->setNext(right);
                right->setPrevious(left);

                cerr << "Deleting " << itr->getKey() << endl;

                delete itr;

                cerr << "Deleted " << endl;

                counter--;
          
                return true;

            }

            itr = itr->getNext();
            left = itr->getPrevious();
            right = itr->getNext();

            
        }

        if (itr->getKey() == k) {

            cerr << "Target key found at last!" << endl;
            last = left;

            cerr << "Deleting " << itr->getKey() << endl;

            delete itr;

            cerr << "Deleted " << endl;
            counter--;

            return true;

        }

        cerr << "Target key not found\n" << endl;
        return false;

    }

    bool Map::contains(const KeyType& key) const {

        node* itr = this->first;

        while (itr != NULL) {

            if (itr->getKey() == key) {

                cerr << "This DLL contains the target " << key << "\n" << endl;
                return true;

            }

            itr = itr->getNext();

        }

        cerr << "Target " << key << " not found\n" << endl;
        return false;

    }

    bool Map::get(const KeyType& key, ValueType& value) const {

        node* itr = this->first;

        while (itr != nullptr) {
            
            if (itr->getKey() == key) {

                value = itr->getData();
                return true;

            }

            itr = itr->getNext();

        }

        return false;

    }

    bool Map::get(int i, KeyType& key, ValueType& value) const {

        int counts = 0;

        if (i <= this->size()) {

            node* itr = this->first;

            while (itr != nullptr) {

                if (counts == i) {

                    key = itr->getKey();
                    value = itr->getData();

                    return true;

                }

                counts++;
                itr = itr->getNext();

            }

        }

        return false;

    }

    void Map::swap(Map& other) {

        Map* temp = new Map(other);
        other = *this;
        *this = temp;

    }

    bool combine(const Map& m1, const Map& m2, Map& result) {

        KeyType k1;
        ValueType v1,v2;

        bool status = false;

        result = m1;

        cerr << "mR: ";
        result.showList();

        for (int i = 0; i < m2.size(); i++) {

            k1 = "";
            v1 = 0;
            v2 = 0;

            m2.get(i, k1, v1);
            result.get(k1, v2);

            if (result.contains(k1) && v2 == v1) {      //check if key/value pair is in both maps

                status = true;                          

            }
            else if (result.contains(k1) && v2 != v1) { //check if key appears in both maps, then check if values are the same
                                                        //if values aren't the same, set status to false
                result.erase(k1);
                status = false;

            }
            else if(!result.contains(k1)) {             //check if the current pair is unique, if so, then add it to 

                result.insert(k1, v1);

            }

        }

        return status;

    }

    void subtract(const Map& m1, const Map& m2, Map& result) {
          
        KeyType k = "";
        ValueType v = 0;

        result = m1;
        cerr << "mR: ";
        result.showList();

        for (int i = 0; i < m2.size(); i++) {

            m2.get(i, k, v);

            cerr << k << endl;

            result.erase(k);

            k = "";

        }

        

    }

    int main() {

        KeyType k = "";
        ValueType v = NULL;

        Map m4;

        Map* m = new Map();
        Map* m2 = new Map();
        Map* m3 = new Map();
        Map* mR = new Map();

        assert(m4.insert("Timothy", 1.0));
        assert(!m4.empty());
        assert(m4.size() == 1);

        m->insert("Jennie", 23.98);
        m->insert("Rose", 40.23);
        m->insert("Jisoo", 32.16);
        m->insert("Lisa", 0.00);

        m2->insert("Richtofen", 100.18);
        m2->insert("Takeo", 23.34);
        m2->insert("Dempsey", 09.21);
        m2->insert("Nikolai", 93.28);
        m2->insert("Lisa", 0.00);

        mR->insert("Arthur Morgan", 97.88);
        
        //m4.insert("Timothy", 1.0);
        m4.showList();
       
        cerr << "m: ";
        m->showList();

        cerr << "m2: ";
        m2->showList();

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

        subtract(*m, *m2, *mR);                           //Testing subtract func
        mR->showList();


        //combine(*m, *m2, *mR);                          //Testing combine func
        //cerr << "Combined mR: ";
        //mR->showList();

    }

