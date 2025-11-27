#include <iostream>
#include "HashTable.h"

int main() {
    HashTable<int> ht(5);

    ht.insert("uno", 1);
    ht.insert("dos", 2);
    ht.insert("tres", 3);

    std::cout << "Valor de 'dos': " << ht.search("dos") << std::endl;

    ht.remove("uno");

    std::cout << "Entradas actuales: " << ht.entries() << std::endl;

    std::cout << ht << std::endl;

    return 0;
}

