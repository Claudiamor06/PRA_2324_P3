#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T>
class BSNode {
    public:
        T elem;                 // Elemento almacenado en el nodo
        BSNode<T>* left;        // Puntero al hijo izquierdo
        BSNode<T>* right;       // Puntero al hijo derecho

        // Constructor (crea un nodo con un dato e hijos izquierdo y derecho)
        BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
            : elem(elem), left(left), right(right) {}

        // Sobrecarga del operador << para imprimir el nodo
        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn) {
	    // Imprime solo el dato del nodo
            out << bsn.elem;
            // Devuelve el stream para seguir imprumiendo
	    return out;
        }
};

#endif

