#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

// Ajusta la ruta según dónde tengas ListLinked.h
#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;   // número de elementos
    int max; // número de cubetas
    ListLinked<TableEntry<V>>* table; // array de listas

    int h(std::string key) {
        int suma = 0;
        for (size_t i = 0; i < key.size(); i++) {
            suma += int(key.at(i));
        }
        return suma % max;
    }

public:
    HashTable(int size) {
        max = size;
        n = 0;
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(std::string key, V value) override {
        int idx = h(key);
        TableEntry<V> entrada(key, value);
        if (table[idx].search(entrada) != -1) {
            throw std::runtime_error("Clave ya existente");
        }
        table[idx].insert(table[idx].size(), entrada);
        n++;
    }

    V search(std::string key) override {
        int idx = h(key);
        TableEntry<V> entrada(key);
        int pos = table[idx].search(entrada);
        if (pos == -1) {
            throw std::runtime_error("Clave no encontrada");
        }
        return table[idx].get(pos).value;
    }

    V remove(std::string key) override {
        int idx = h(key);
        TableEntry<V> entrada(key);
        int pos = table[idx].search(entrada);
        if (pos == -1) {
            throw std::runtime_error("Clave no encontrada");
        }
        V val = table[idx].get(pos).value;
        table[idx].remove(pos);
        n--;
        return val;
    }

    int entries() override {
        return n;
    }

    int capacity() {
        return max;
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
        for (int i = 0; i < th.max; i++) {
            out << "Cubeta " << i << ": ";
            for (int j = 0; j < th.table[i].size(); j++) {
                out << th.table[i].get(j) << " ";
            }
            out << std::endl;
        }
        return out;
    }
};

#endif

