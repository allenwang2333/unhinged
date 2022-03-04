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
    //if (m_attrName.empty()) {
        //m_attrName.push_back()
    //}
}

int PersonProfile::GetNumAttValPairs() const {
    return m_num;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attaval) const {
    /*
    if (attribute_num < 0 || attribute_num >= GetNumAttValPairs()) {
        return false;
    }
    else {
        attaval = m_pair[attribute_num];
        return true;
    }
     */
    return true;
}
