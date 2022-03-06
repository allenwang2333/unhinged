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
    ifstream memberFile;
    string line;
    int count = 0;
    string name = "";
    string email = "";
    vector<AttValPair> v;
    
    memberFile.open(filename);
    if (memberFile.is_open()) {
        while (getline(memberFile, line)) {
            if (count == 0) {
                name = line;
                count++;
            }
            else if (count == 1) {
                email = line;
                count++;
            }
            else if (count == 2) {
                count++;
                continue;
            }
            else {
                if (line.size()!= 0) {
                    v.push_back(parser(line));
                    count++;
                }
            }
            
            if (line.size() == 0) {
                PersonProfile* p = new PersonProfile(name, email);
                for (int i = 0; i < v.size(); i++) {
                    p->AddAttValPair(v[i]);
                    vector<string>* ptr = m_treeByPair.search(v[i].attribute + ',' + v[i].value);
                    if (ptr == nullptr) {
                        vector<string> emails;
                        emails.push_back(email);
                        m_treeByPair.insert(v[i].attribute + ',' + v[i].value, emails);
                    }
                    else {
                        ptr->push_back(email);
                    }
                }
                m_treeByEmail.insert(email, p);
                m_personPtr.push_back(p);
                count = 0;
                name = "";
                email = "";
                v.clear();
                
                continue;
            }
        }
        memberFile.close();
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
    if (m_treeByPair.search(s) == nullptr) {
        return v;
    }
    else {
        return *(m_treeByPair.search(s));
    }
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {
    if (m_treeByEmail.search(email) != nullptr) {
        return *m_treeByEmail.search(email);
    }
    else {
        return nullptr;
    }
}

AttValPair MemberDatabase::parser(string line) {
    int count = 0;
    string attr = "";
    string value = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ',') {
            count++;
            continue;
        }
        else {
            if (count == 0) {
                attr += line[i];
            }
            else {
                value += line[i];
            }
        }
    }
    return AttValPair(attr, value);
}

