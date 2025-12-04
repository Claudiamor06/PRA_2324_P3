#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {
    private:
        BSTree<TableEntry<V>>* tree;   // ABB con entradas clave->valor

    public:
        // Constructor: crea un ABB vacío
        BSTreeDict() {
            tree = new BSTree<TableEntry<V>>();
        }

        // Destructor: libera memoria
        ~BSTreeDict() {
            delete tree;
        }

        // Insertar una entrada clave->valor
        void insert(std::string key, V value) override {
            TableEntry<V> entry(key, value);
            tree->insert(entry);
        }

        // Buscar un valor por clave
        V search(std::string key) override {
            TableEntry<V> entry(key, V()); // valor dummy
            TableEntry<V> result = tree->search(entry);
            return result.value;
        }

        // Eliminar una entrada por clave y devolver su valor
        V remove(std::string key) override {
            TableEntry<V> entry(key, V());
            TableEntry<V> result = tree->search(entry); // obtenemos el valor
            tree->remove(entry);                        // eliminamos del ABB
            return result.value;                        // devolvemos el valor eliminado
        }

        // Devolver número de entradas
        int entries() override {
            return tree->size();
        }

        // Sobrecarga del operador []
        V operator[](std::string key) {
            return search(key);
        }

        // Sobrecarga del operador <<
        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
            out << *(bs.tree);
            return out;
        }
};

#endif


