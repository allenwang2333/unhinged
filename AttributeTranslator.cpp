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
    ifstream attributeFile(filename);
    string line;
    if (attributeFile) {
        while (!attributeFile.eof()) {
            getline(attributeFile, line);
            if (line.size() == 0) {
                continue;
            }
            int pos = line.find(',');
            string sourceaAttr = line.substr(0, pos); // source attribute
            line = line.substr(pos+1);
            
            pos = line.find(',');
            string sourceValue = line.substr(0, pos); //source value;
            string compatible = line.substr(pos+1); // compatible attribute + ',' + compatible value
            string source = sourceaAttr + ',' + sourceValue;
            vector<string>* ptr = m_pair.search(source); // search whether exist
            if (ptr == nullptr) {
                // if not exist create a new vector and insert
                vector<string> attVal;
                attVal.push_back(compatible);
                m_pair.insert(source, attVal);
            }
            else {
                // compatible attributes for a given attribute is less than 10, so O(10) = O(1)
                bool flag = false; // repeated case
                for (int i = 0; i < ptr->size(); i++) {
                    if ((*ptr)[i] == compatible) {
                        flag = true; // has repeat
                        break;
                    }
                }
                if (!flag) {
                    ptr->push_back(compatible); // no repeat push back
                }
            }
        }
        return true;
    }
    else {
        return false;
    }
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
    vector<AttValPair> result;
    string s = source.attribute + ',' + source.value;
    
    vector<string>* ptr = m_pair.search(s);
    if (ptr == nullptr) {
        return result;
    }
    else {
        for (int i = 0; i < ptr->size(); i++) {
            int pos = (*ptr)[i].find(',');
            // push back to the vector
            result.push_back(AttValPair((*ptr)[i].substr(0, pos), (*ptr)[i].substr(pos + 1)));
        }
    }
    return result;
}
