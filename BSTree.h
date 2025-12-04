#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
    private:
        int nelem;          // número de elementos
        BSNode<T>* root;    // nodo raíz

        // Métodos privados recursivos
        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) throw std::runtime_error("Elemento no encontrado");
            if (e == n->elem) return n;
            if (e < n->elem) return search(n->left, e);
            else return search(n->right, e);
        }

        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (n == nullptr) {
                nelem++;
                return new BSNode<T>(e);
            }
            if (e == n->elem) throw std::runtime_error("Elemento duplicado");
            if (e < n->elem) n->left = insert(n->left, e);
            else n->right = insert(n->right, e);
            return n;
        }

        void print_inorder(std::ostream &out, BSNode<T>* n) const {
            if (n != nullptr) {
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out, n->right);
            }
        }

        BSNode<T>* remove(BSNode<T>* n, T e) {
            if (n == nullptr) throw std::runtime_error("Elemento no encontrado");
            if (e < n->elem) n->left = remove(n->left, e);
            else if (e > n->elem) n->right = remove(n->right, e);
            else {
                // Caso encontrado
                if (n->left == nullptr) {
                    BSNode<T>* tmp = n->right;
                    delete n;
                    nelem--;
                    return tmp;
                } else if (n->right == nullptr) {
                    BSNode<T>* tmp = n->left;
                    delete n;
                    nelem--;
                    return tmp;
                } else {
                    // Dos hijos: reemplazar por máximo del subárbol izquierdo
                    T m = max(n->left);
                    n->elem = m;
                    n->left = remove_max(n->left);
                }
            }
            return n;
        }

        T max(BSNode<T>* n) const {
            if (n->right == nullptr) return n->elem;
            return max(n->right);
        }

        BSNode<T>* remove_max(BSNode<T>* n) {
            if (n->right == nullptr) {
                BSNode<T>* tmp = n->left;
                delete n;
                nelem--;
                return tmp;
            }
            n->right = remove_max(n->right);
            return n;
        }

        void delete_cascade(BSNode<T>* n) {
            if (n != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }

    public:
        // Constructor
        BSTree() : nelem(0), root(nullptr) {}

        // Destructor
        ~BSTree() {
            delete_cascade(root);
        }

        // Tamaño
        int size() const { return nelem; }

        // Búsqueda
        T search(T e) const {
            BSNode<T>* n = search(root, e);
            return n->elem;
        }

        T operator[](T e) const {
            return search(e);
        }

        // Inserción
        void insert(T e) {
            root = insert(root, e);
        }

        // Eliminación
        void remove(T e) {
            root = remove(root, e);
        }

        // Impresión inorden
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }
};

#endif

