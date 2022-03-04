#include <iostream>
#include <string>
#include <cassert>
#include "RadixTree.h"
#include "AttributeTranslator.h"
using namespace std;

void listCompatiblePairs(const AttributeTranslator& translator) {
    AttValPair att("favorite_food", "del taco");
    std::vector<AttValPair> result = translator.FindCompatibleAttValPairs(att);
    if (!result.empty()) {
        std::cout << "Compatible attributes and values:" << std::endl;
        for (const auto& p: result)
            std::cout << p.attribute << " -> " << p.value << std::endl;
    }
}

void testTranslator() {
    AttributeTranslator at;
    at.Load("/Users/allenwang/Desktop/project4/translator.txt");
    listCompatiblePairs(at);
}

void testRadixTree() {
    RadixTree<int> t;
    t.insert("alpha", 2);
    t.insert("chisun", 4);
    t.insert("chi", 3);
    t.insert("allen", 1);
    t.insert("rubens", 9);
    t.insert("romane", 6);
    t.insert("romanus", 7);
    t.insert("romulus", 8);
    t.insert("romanb", 5);
    t.insert("ruber", 10);
    t.insert("rubicon", 11);
    t.insert("rubicundus", 12);
    t.insert("xxxx",99);
    t.insert("xxxxy",99);
    t.insert("alpha", 22);
    t.insert("apple",100);
    t.insert("applewatch",100);
    t.insert("app",100);
    t.insert("ap",100);
    t.insert("and",100);

    assert(*(t.search("allen"))==1);
    assert(*(t.search("chi"))==3);
    assert(*(t.search("rubicundus"))==12);
    assert(*(t.search("romanus"))==7);
    assert(*(t.search("ruber"))==10);
    assert(t.search("big")==nullptr);
    

    t.dump(t.m_root, 0);
    assert(!t.m_root->m_end);


    cout<<"passed RadixTree test"<<endl;
}

int main() {
    //testRadixTree();
    testTranslator();
}

