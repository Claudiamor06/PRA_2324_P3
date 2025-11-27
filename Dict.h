#ifndef DICT_H
#define DICT_H

#include <string>
#include <stdexcept>

template <typename V>
class Dict {
public:
    virtual ~Dict() {}

    // Inserta un par clave→valor. Lanza excepción si la clave ya existe.
    virtual void insert(std::string key, V value) = 0;

    // Busca el valor asociado a la clave. Lanza excepción si no existe.
    virtual V search(std::string key) = 0;

    // Elimina el par clave→valor. Lanza excepción si no existe.
    virtual V remove(std::string key) = 0;

    // Devuelve el número de elementos en el diccionario.
    virtual int entries() = 0;
};

#endif

