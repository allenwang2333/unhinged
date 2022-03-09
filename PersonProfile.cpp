#include <string>
#include "PersonProfile.h"
#include "provided.h"
using namespace std;

PersonProfile::PersonProfile(string name, string email) :m_name(name), m_email(email), m_num(0) {

}

PersonProfile::~PersonProfile() {
    
}


string PersonProfile::GetName() const {
    return m_name;
}

string PersonProfile::GetEmail() const {
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    vector<string>* ptr = m_tree.search(attval.attribute);
    if (ptr == nullptr) {
        // if attribute not exist, create a new vector and insert to the tree
        vector<string> temp;
        temp.push_back(attval.value);
        m_tree.insert(attval.attribute, temp);
        m_pair.push_back(attval);
        m_num++;
    }
    else {
        // check for duplication 
        for (int i = 0; i < ptr->size(); i++) {
            if ((*ptr)[i] == attval.value) {
                return;
            }
        }
        ptr->push_back(attval.value);
        m_pair.push_back(attval);
        m_num++;
    }
}

int PersonProfile::GetNumAttValPairs() const {
    return m_num;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attaval) const {
    if (attribute_num < 0 || attribute_num >= m_num) {
        return false;
    }
    else {
        attaval = m_pair[attribute_num]; // a vector retrieval is O(1)
        return true;
    }
}
