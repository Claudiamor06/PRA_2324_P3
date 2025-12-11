#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry {
public:
    std::string key;
    V value;

    // Constructores
    TableEntry(std::string k, V v) : key(k), value(v) {}
    TableEntry(std::string k) : key(k), value() {}
    TableEntry() : key(""), value() {}

    // Operadores de comparación (solo por clave)
    friend bool operator==(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        return te1.key == te2.key;
    }

    friend bool operator!=(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        return te1.key != te2.key;
    }

    // Operador de impresión
    friend std::ostream& operator<<(std::ostream& out, const TableEntry<V>& te) {
        out << te.key << " -> " << te.value;
	return out;
    }

};

#endif

