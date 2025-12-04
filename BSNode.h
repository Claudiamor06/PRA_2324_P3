#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T>
class BSNode {
    public:
        // Atributos públicos
        T elem;                 // Elemento almacenado en el nodo
        BSNode<T>* left;        // Puntero al sucesor izquierdo
        BSNode<T>* right;       // Puntero al sucesor derecho

        // Constructor
        BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
            : elem(elem), left(left), right(right) {}

        // Sobrecarga del operador << como función amiga
        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn) {
            out << bsn.elem;
            return out;
        }
};

#endif

