#include <iostream>
#include "TableEntry.h"

int main() {
    TableEntry<int> e1("uno", 1);
    TableEntry<int> e2("dos", 2);
    TableEntry<int> e3("uno", 99);

    std::cout << e1 << std::endl;
    std::cout << e2 << std::endl;

    if (e1 == e3)
        std::cout << "e1 y e3 tienen la misma clave" << std::endl;

    if (e1 != e2)
        std::cout << "e1 y e2 tienen claves distintas" << std::endl;

    return 0;
}

