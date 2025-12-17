#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"

// Permite almacenar valores de cualquier tipo V
template <typename V>
// Hereda de Dict V
class HashTable : public Dict<V> {
private:
// Numero de elementos almacenados en la tabla
    int n;   
// Numero de cubetas (tamaño del array)
    int max;
// Array dinamico de listas enlazadas
    ListLinked<TableEntry<V>>* table;

// Funcion Hash: convierte una clave string en un indice entre 0 y max-1, suma los codigos ASCII de los caracteres y hace modulo max
    int h(std::string key) {
        int suma = 0;
        for (size_t i = 0; i < key.size(); i++) {
            suma += int(key.at(i));
        }
        return suma % max;
    }

public:

// Constructor: crea la tabla hash con un numero de cubetas dado, inicializa n a cero y reserva memoria para las listas
    HashTable(int size) {
        max = size;
        n = 0;
        table = new ListLinked<TableEntry<V>>[max];
    }

// Destructor: libera la memoria del array dinamico de listas
    ~HashTable() {
        delete[] table;
    }

// Inserta elemento: calcula la cubeta con el hash, comprueba si la clave ya existe y la inserta al final de la lista correspondiente
    void insert(std::string key, V value) override {
        int idx = h(key);
        TableEntry<V> entrada(key, value);
        if (table[idx].search(entrada) != -1) {
            throw std::runtime_error("Clave ya existente");
        }
        table[idx].insert(table[idx].size(), entrada);
        n++;
    }

// Busca el elemento: calcula la cubeta, busca la clave en la lista y si existe devuelve el valor
    V search(std::string key) override {
        int idx = h(key);
        TableEntry<V> entrada(key);
        int pos = table[idx].search(entrada);
        if (pos == -1) {
            throw std::runtime_error("Clave no encontrada");
        }
        return table[idx].get(pos).value;
    }

// Elimina el elemento: calcula la cubeta, busca la clave, la elimina y devuelve su valor
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

// Devuelve cuantos elementos hay en la tabla
    int entries() override {
        return n;
    }

// Devuelve cuantas cubetas tiene la tabla
    int capacity() {
        return max;
    }

// Es el que permite imprimir la tabla hash completa recorriendo todas las cubetas y sus listas
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

