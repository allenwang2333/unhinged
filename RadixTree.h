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
       
        
    //private:
        struct Node {
            Node(std::string key)
            : m_key(key), m_end(false)
            {
                for (int i = 0; i < 128; i++) {
                    m_child[i] = nullptr;
                }
                m_end = false;
            }
            std::string m_key;
            Node* m_child[128];
            ValueType m_value;
            bool m_end;
        };
        int getMaxSub(std::string subKey, std::string key) const;
        Node* m_root;
        void dump(Node* p, int depth);
        void cleanUp(Node* p);
};

template<typename ValueType>
RadixTree<ValueType>::RadixTree() {
    m_root = new Node("");
    m_root->m_end = false;
}

template<typename ValueType>
RadixTree<ValueType>::~RadixTree() {
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
            ptr->m_child[c] = new Node(key);
            ptr->m_child[c]->m_end = true;
            ptr->m_child[c]->m_value = value;
            return;
        }
        else {
            if (key == ptr->m_child[c]->m_key) {
                ptr->m_child[c]->m_value = value;
                return;
            }
            int pos = getMaxSub(ptr->m_child[c]->m_key, key);
            // has common substr, inserted length is larger than existing length
            if (pos == ptr->m_child[c]->m_key.size()) {
                key = key.substr(pos);
                ptr = ptr->m_child[c];
                continue;
            }
            else {
                Node* oldNode = ptr->m_child[c];
                Node* newNode = new Node(oldNode->m_key.substr(0,pos));
                ptr->m_child[c] = newNode;
                oldNode->m_key = oldNode->m_key.substr(pos);
                newNode->m_child[oldNode->m_key[0]] = oldNode;
                if (pos == key.size()) {
                    newNode->m_end = true;
                    newNode->m_value = value;
                }
                else{
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
                return nullptr;
            }
            else {
                int pos = getMaxSub(ptr->m_child[c]->m_key, key);
                if (key.substr(0, pos) == ptr->m_child[c]->m_key.substr(0, pos)) {
                    if (key == ptr->m_child[c]->m_key && ptr->m_child[c]->m_end) {
                        return &(ptr->m_child[c]->m_value);
                    }
                    else {
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

template<typename ValueType>
void RadixTree<ValueType>::dump(Node* p, int depth) {
        std::string space(4*depth, ' ');
        if (p->m_end) {
            std::cout << space << p->m_key << "$" << p->m_value << std::endl;
        }
        else {
            std::cout << space << p->m_key << std::endl;
        }
        for (int k = 0; k < 128; k++) {
            if (p->m_child[k] != nullptr)
                dump(p->m_child[k], depth+1);
        }
}
#endif
