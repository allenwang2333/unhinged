#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "AttributeTranslator.h"
#include "provided.h"
using namespace std;

AttributeTranslator::AttributeTranslator() {
    
}

AttributeTranslator::~AttributeTranslator() {

}

bool AttributeTranslator::Load(string filename) {
    ifstream attributeFile;
    string line;
    attributeFile.open(filename);
    if (attributeFile.is_open()) {
        while (getline(attributeFile, line)) {
            string sourceAttr = findSourceTrait(line);
            vector<AttValPair> att = parser(line);
            if (m_pair.search(sourceAttr) == nullptr) {
                m_pair.insert(sourceAttr, parser(line));
            }
            else {
                // TODO:: do i need to deal with the repeated case?
                vector<AttValPair> existedPairs = *m_pair.search(sourceAttr);
                for (int i = 0; i < parser(line).size(); i++) {
                    existedPairs.push_back(parser(line)[i]);
                }
                m_pair.insert(sourceAttr, existedPairs);
            }
        }
        attributeFile.close();
        return true;
    }
    else {
        cerr << "The file cannot be opened. There must be some error!" << endl;
        return false;
    }
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
    vector<AttValPair> result;
    vector<AttValPair> empty;
    vector<AttValPair> returnVec;
    if (m_pair.search(source.attribute) == nullptr) {
        return empty;
    }
    else {
        result = *(m_pair.search(source.attribute));
    }
    for (int i = 0; i < result.size()-1; i++) {
        if (result[i] == source){
            returnVec.push_back(result[i+1]);
            i++;
        }
    }
    return returnVec;
}

vector<AttValPair> AttributeTranslator::parser(string line) {
    int counter = 0;
    vector<AttValPair> v;
    string sourceAttr = "";
    string sourceValue = "";
    string compatibleAttr = "";
    string compatibleValue = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ',') {
            counter += 1;
            continue;
        }
        if (counter == 0) {
            sourceAttr += line[i];
        }
        else if (counter == 1) {
            sourceValue += line[i];
        }
        else if (counter == 2) {
            compatibleAttr += line[i];
        }
        else {
            compatibleValue += line[i];
        }
    }
    v.push_back(AttValPair(sourceAttr, sourceValue));
    v.push_back(AttValPair(compatibleAttr, compatibleValue));
    return v;
}

string AttributeTranslator::findSourceTrait(string line) {
    string attr = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ',') {
            return attr;
        }
        else {
            attr += line[i];
        }
    }
    return attr;
}
