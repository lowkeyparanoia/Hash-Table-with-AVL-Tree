
#include <iostream>
#include <string>
#include <algorithm>
#include <AVLTree.h>

using namespace std;


// Hash Table class
class HashTable {
    AVLTree *table;
    int size;

public:
    HashTable(int s) {
        size = s;
        table = new AVLTree[size];
    }

    // hash function
    int hashFunc(string key) {
        int hash = 0;
        for (int i = 0; i < key.length(); i++) {
            hash += (int)key[i];
        }
        return hash % size;
    }

    // insert
    void insert(string key, int value) {
        int index = hashFunc(key);
        table[index].insert(key, value);
    }

    // search
    bool search(string key) {
        int index = hashFunc(key);
        return table[index].search(key);
    }

    // get
    int get(string key) {
        int index = hashFunc(key);
        return table[index].get(key);
    }

    // delete
    void remove(string key) {
        int index = hashFunc(key);
        table[index].remove(key);
    }
};

int main() {
    HashTable ht(10);
    ht.insert("apple", 5);
    ht.insert("banana", 3);
    ht.insert("carrot", 4);
    ht.insert("date", 7);
    ht.insert("eggplant", 2);
    ht.insert("fig", 1);

    cout << ht.get("apple") << endl;
    cout << ht.get("banana") << endl;
    cout << ht.get("carrot") << endl;
    cout << ht.get("date") << endl;
    cout << ht.get("eggplant") << endl;
    cout << ht.get("fig") << endl;

    return 0;
}
