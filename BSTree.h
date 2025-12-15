#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>

class BSTree {

    private:

        int nelem;          // número de elementos del árbol
        BSNode<T>* root;    // puntero al nodo raíz del árbol

        // Métodos privados recursivos
	
	// Busca en el árbol
        BSNode<T>* search(BSNode<T>* n, T e) const {

	    // Si no hay nodo, devuelve error
            if (n == nullptr) throw std::runtime_error("Elemento no encontrado"); 

	    // Si el dato coincide, lo devuelve
            if (e == n->elem) return n; 

	    // Si es menor, sigue buscando para la izquierda
            if (e < n->elem) return search(n->left, e);

	    // Si es mayor, sigue buscando para la derecha
            else return search(n->right, e);
        }

	// Inserta los datos en el árbol
        BSNode<T>* insert(BSNode<T>* n, T e) {

	    // Si no hay nodo, se crea uno nuevo
            if (n == nullptr) {
                nelem++;
                return new BSNode<T>(e);
            }

	    // Esto no permite duplicados
            if (e == n->elem) throw std::runtime_error("Elemento duplicado"); 

	    // Si el dato es menor que el siguiente, sigue buscando para la izquierda (más adelante se insertará)
            if (e < n->elem) n->left = insert(n->left, e); 

	    // Sino, es mayor y sigue buscando para la derecha (más adelante se insertará)
            else n->right = insert(n->right, e);

	    // Devuelve el nodo actual
            return n;
        }
	
	// Recorre e imprime el árbol de izquierda-nodo-derecha
        void print_inorder(std::ostream &out, BSNode<T>* n) const {
                // Si NO está vacío imprime todo lo que haya a la izquierda luego el nodo actual y luego lo de la derecha
		if (n != nullptr) {
                print_inorder(out, n->left); 
                out << n->elem << " "; 
                print_inorder(out, n->right);
            }
        }

	// Elimina un elemento del árbol
        BSNode<T>* remove(BSNode<T>* n, T e) {

	    // Si no existe, error
            if (n == nullptr) throw std::runtime_error("Elemento no encontrado");

	    // Si el dato es menor que el siguiente, sigue buscando para la izquierda (más adelante se borrará)
            if (e < n->elem) n->left = remove(n->left, e); 

	    // Sino, es mayor y sigue buscando para la derecha (más adelante se borrará)
            else if (e > n->elem) n->right = remove(n->right, e);
            else {
                // Caso encontrado
		
		// Si no tiene hijo izquierdo, guarda el derecho, borra el nodo actual, le resta uno al contador y devuelve el hijo derecho
                if (n->left == nullptr) { 
                    BSNode<T>* tmp = n->right; 
                    delete n;
                    nelem--; 
                    return tmp; 
                } 

		// Si no tiene hijo derecho, guarda el izquierdo, borra el nodo actual, le resta uno al contador y devuelve el hijo izquierdo
		else if (n->right == nullptr) {
                    BSNode<T>* tmp = n->left; 
                    delete n; 
                    nelem--; 
                    return tmp; 
                } else {
                    // Si tiene dos hijos, busca el máximo de la izquierda, reemplaza el valor actual y borra ese máximo de la izquierda
                    T m = max(n->left); 
                    n->elem = m; 
                    n->left = remove_max(n->left); 
                }
            }

	    // devuelve el nodo actuaizado
            return n; 
        }

	// Devuelve el valor máximo dentro de un subárbol
        T max(BSNode<T>* n) const {

	    // si no hay más derecha ese es el máximo y se devuelve
            if (n->right == nullptr) return n->elem;

	    // y sino, sigue buscando a la derecha
            return max(n->right);
        }

	// Elimina el nodo máximo de un subárbol
        BSNode<T>* remove_max(BSNode<T>* n) {

	    // Si ese es el máximo, guarda el hijo izquierdo, borra el nodo, resta uno al contador y devuelve al hijo izquierdo
            if (n->right == nullptr) { 
                BSNode<T>* tmp = n->left;
                delete n;
                nelem--;
                return tmp;
            }

	    // Y sino, sigue bajando por la derecha
            n->right = remove_max(n->right);
            return n;
        }

	// Borra todos los nodos de un subárbol en cascada
        void delete_cascade(BSNode<T>* n) {

	// si no está vacío, borra primero los de la izquierda, luego el de la derecha y luego el actual
            if (n != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }

    public:
        // Constructor (empieza con cero elementos y la raíz vacía)
        BSTree() : nelem(0), root(nullptr) {}

        // Destructor (borra todos los nodos en cascada)
        ~BSTree() {
            delete_cascade(root);
        }

        // Devuelve el Tamaño del árbol (cuántos elementos tiene)
        int size() const { return nelem; }

        // Búsqueda (devuelve el elemento si existe)
        T search(T e) const {
            BSNode<T>* n = search(root, e);
            return n->elem;
        }

	// Sobrecarga del operador [] para buscar como si fuera un array
        T operator[](T e) const {
            return search(e);
        }

        // Inserción (añade un elemento al árbol)
        void insert(T e) {
            root = insert(root, e);
        }

        // Eliminación (borra un elemento del árbol)
        void remove(T e) {
            root = remove(root, e);
        }

        // Impresión inorden (izquierda, nodo, derecha)
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
            bst.print_inorder(out, bst.root); // llama al recorrido inorden
            return out;
        }
};

#endif

