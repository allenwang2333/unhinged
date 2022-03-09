#include <iostream>
#include <fstream>
#include "MemberDatabase.h"
#include "RadixTree.h"
#include "PersonProfile.h"
#include "provided.h"
using namespace std;

MemberDatabase::MemberDatabase() {
    

}

MemberDatabase::~MemberDatabase() {
    for (int i = 0; i < m_personPtr.size(); i++) {
        delete m_personPtr[i];
    }
}

bool MemberDatabase::LoadDatabase(string filename) {
    ifstream memberFile(filename);
    string line;
    vector<string> personInfo;
    if (memberFile) {
        while (getline(memberFile, line)) {
            if (line.size() != 0) {
                personInfo.push_back(line);
            }
            else {
                PersonProfile* p = new PersonProfile(personInfo[0], personInfo[1]);
                int size = personInfo.size();
                for (int i = 3; i < size; i++) {
                    int pos = personInfo[i].find(',');
                    string attr = personInfo[i].substr(0, pos); // attribute
                    string value = personInfo[i].substr(pos+1); // value
                    p->AddAttValPair(AttValPair(attr, value));  // add attribute value pair
                }
                
                for (int j = 0; j < p->GetNumAttValPairs(); j++) {
                    // person profile does not have repeated attval paris.
                    // there fore I don't need to check for repetition in this case
                    // saves time complexity!!
                    AttValPair attval;
                    p->GetAttVal(j, attval);
                    string s = attval.attribute + ',' + attval.value;
                    vector<string>* ptr = m_treeByPair.search(s);
                    if (ptr == nullptr) {
                        vector<string> emails;
                        emails.push_back(p->GetEmail());
                        m_treeByPair.insert(s, emails);
                    }
                    else {
                        ptr->push_back(p->GetEmail());
                    }
                }
                m_treeByEmail.insert(personInfo[1], p); // inserting email tree
                m_personPtr.push_back(p);
                personInfo.clear();
            }
        }
        return true;
    }
    else {
        cerr << "The file cannot be opened. There must be some error!" << endl;
        return false;
    }
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    vector<string> v;
    string s = input.attribute + ',' + input.value;
    vector<string>* ptr = m_treeByPair.search(s);
    if (ptr == nullptr) {
        return v;
    }
    else {
        return *ptr; // the vector of emails
    }
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {
    PersonProfile** ptr = m_treeByEmail.search(email);
    if (ptr != nullptr) {
        return *ptr;
    }
    else {
        return nullptr;
    }
}

