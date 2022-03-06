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
            string source = findSource(line);
            string compatible = findCompatible(line);
            vector<string> attVal;
            if (m_pair.search(source) == nullptr) {
                attVal.push_back(compatible);
                m_pair.insert(source, attVal);
            }
            else {
                // TODO:: do i need to deal with the repeated case?
                vector<string> existedPairs = *m_pair.search(source);
                existedPairs.push_back(compatible);
                m_pair.insert(source, existedPairs);
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
    vector<string> result;
    vector<AttValPair> empty;
    vector<AttValPair> returnVec;
    string s = source.attribute + ',' + source.value;
    if (m_pair.search(s) == nullptr) {
        return empty;
    }
    else {
        result = *(m_pair.search(s));
    }
    for (int i = 0; i < result.size(); i++) {
        string attr = result[i].substr(0, result[i].find(','));
        string value = result[i].substr(result[i].find(',') + 1);
        returnVec.push_back(AttValPair(attr, value));
    }
    return returnVec;
}

string AttributeTranslator::findCompatible(string line) {
    int counter = 0;
    string s;
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
    return compatibleAttr + ',' + compatibleValue;
}

string AttributeTranslator::findSource(string line) {
    int counter = 0;
    string s;
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
    return sourceAttr + ',' + sourceValue;
}
