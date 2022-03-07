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
    // TODO: need optimization
    m_num++;
    vector<AttValPair> v;
    bool flag = false;
    if (m_cntVec.empty()) {
        m_cntVec.push_back(Counter(attval.attribute));
        v.push_back(attval);
        m_pair.insert(attval.attribute, v);
    }
    else {
        for (int i = 0; i < m_cntVec.size(); i++) {
            if (attval.attribute == m_cntVec[i].m_attr) {
                m_cntVec[i].m_number += 1;
                flag = true;
            }
        }
        if (!flag) {
            m_cntVec.push_back(Counter(attval.attribute));
        }
        if (m_pair.search(attval.attribute) == nullptr) {
            v.push_back(attval);
            m_pair.insert(attval.attribute, v);
        }
        else {
            int size = m_pair.search(attval.attribute)->size();
            for (int j = 0; j < size; j++) {
                if (m_pair.search(attval.attribute)->at(j) == attval) {
                    m_num--;
                    return;
                }
            }
            m_pair.search(attval.attribute)->push_back(attval);
        }
    }
}

int PersonProfile::GetNumAttValPairs() const {
    return m_num;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attaval) const {
    vector<AttValPair> v;
    if (attribute_num < 0 || attribute_num >= GetNumAttValPairs()) {
        return false;
    }
    else {
        int i;
        for (i = 0; i < m_cntVec.size(); i++) {
            if (attribute_num > m_cntVec[i].m_number) {
                attribute_num -= m_cntVec[i].m_number;
                attribute_num --;
            }
            else {
                break;
            }
        }
        v = *m_pair.search(m_cntVec[i].m_attr);
        attaval.attribute = v[attribute_num].attribute;
        attaval.value = v[attribute_num].value;
        return true;
    }
}
