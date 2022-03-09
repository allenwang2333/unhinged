#ifndef RADIX_TREE_H
#define RADIX_TREE_H

#include <string>
#include <map>
#include <iostream>

template <typename ValueType>
class RadixTree {
    public:
        RadixTree();
        ~RadixTree();
        void insert(std::string key, const ValueType& value);
        ValueType* search(std::string key) const;
       
    private:
        struct Node {
            Node(std::string key)
            : m_key(key), m_end(false)
            {
                for (int i = 0; i < 128; i++) {
                    m_child[i] = nullptr;
                }
            }
            std::string m_key;
            Node* m_child[128];
            ValueType m_value;
            bool m_end;
        };
        int getMaxSub(std::string subKey, std::string key) const;
        Node* m_root;
        void cleanUp(Node* p);
};

template<typename ValueType>
RadixTree<ValueType>::RadixTree() {
    // root is empty string
    m_root = new Node("");
}

template<typename ValueType>
RadixTree<ValueType>::~RadixTree() {
    // recursive 
    cleanUp(m_root);
}

template<typename ValueType>
int RadixTree<ValueType>::getMaxSub(std::string subKey, std::string key) const {
    // get largest common substr
    // if there is no common substr return 0;
    int i = 0;
    for (; i < subKey.size() && i < key.size();) {
        if (subKey.at(i) == key.at(i)) {
            i++;
        }
        else{
            break;
        }
    }
    return i;
}

template<typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value) {
    // if key is empty
    if (key.size() == 0) return;
    Node* ptr = m_root;
    while (key.size() > 0) {
        int c = key[0];
        if (ptr->m_child[c] == nullptr) {
            // if this child does not exist
            ptr->m_child[c] = new Node(key);
            ptr->m_child[c]->m_end = true;
            ptr->m_child[c]->m_value = value;
            return;
        }
        else {
            if (key == ptr->m_child[c]->m_key) {
                // if key is the same, then replace
                ptr->m_child[c]->m_value = value;
                return;
            }
            int pos = getMaxSub(ptr->m_child[c]->m_key, key);
            
            if (pos == ptr->m_child[c]->m_key.size()) {
                // go to child node
                key = key.substr(pos);
                ptr = ptr->m_child[c];
                continue;
            }
            else {
                // rebase
                Node* oldNode = ptr->m_child[c];
                Node* newNode = new Node(oldNode->m_key.substr(0,pos));
                ptr->m_child[c] = newNode;
                oldNode->m_key = oldNode->m_key.substr(pos);
                newNode->m_child[oldNode->m_key[0]] = oldNode;
                if (pos == key.size()) {
                    // has common substr, and is exactly the substr
                    newNode->m_end = true;
                    newNode->m_value = value;
                }
                else{
                    // not a exact substr
                    Node* secOldNode = new Node(key.substr(pos));
                    newNode->m_child[key[pos]] = secOldNode;
                    newNode->m_child[key[pos]]->m_end = true;
                    newNode->m_child[key[pos]]->m_value = value;
                }
                return;
            }
        }
    }
}

template<typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const {
    if (key.size() == 0) {
        return nullptr;
    }
    else {
        Node* ptr = m_root;
        while (key.size() > 0) {
            int  c = key[0];
            if (ptr->m_child[c] == nullptr) {
                // not exist at all
                return nullptr;
            }
            else {
                int pos = getMaxSub(ptr->m_child[c]->m_key, key);
                if (key.substr(0, pos) == ptr->m_child[c]->m_key.substr(0, pos)) {
                    if (key == ptr->m_child[c]->m_key && ptr->m_child[c]->m_end) {
                        
                        return &(ptr->m_child[c]->m_value);
                    }
                    else {
                        // go to next child node
                        key = key.substr(pos);
                        ptr = ptr->m_child[c];
                    }
                }
                else {
                    return nullptr;
                }
            }
        }
        return nullptr;
    }
}

template<typename ValueType>
void RadixTree<ValueType>::cleanUp(Node* p) {
    // clean up danamically allocated memory
    if (p != nullptr) {
        for (int i = 0; i < 128; i++) {
            if (p->m_child[i] != nullptr) {
                cleanUp(p->m_child[i]);
            }
        }
        delete p;
        return;
    }
}
#endif
