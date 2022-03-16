#ifndef ATTRIBUTE_TRANSLATOR_H
#define ATTRIBUTE_TRANSLATOR_H

#include <string>
#include <vector>
#include "RadixTree.h"
#include "provided.h"

class AttributeTranslator {
    public:
        AttributeTranslator();
        ~AttributeTranslator();
        bool Load(std::string filename);
        std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
    private:
        RadixTree<std::vector<std::string>> m_pair;
};

#endif
