#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "MatchMaker.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "PersonProfile.h"
#include "RadixTree.h"
#include "provided.h"

using namespace std;

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) :m_db(&mdb), m_at(&at){

}

MatchMaker::~MatchMaker() {
    
}

bool comp(const EmailCount& e1, const EmailCount& e2) {
    // comes firts if count is larger,
    // when count is same, in incrasing alphabetical order
    if (e1.count > e2.count) return true;
    else if (e1.count < e2.count) return false;
    else if (e1.email < e2.email) return true;
    else return false;
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
    vector<AttValPair> v; // pair of this person
    vector<AttValPair> vc; // compatible pairs
    vector<string> vm; // matching members, a vector of emails
    vector<EmailCount> ve;
    unordered_map<string, int> m_map; // a map that contains the email and time it appears
    const PersonProfile* pp = m_db->GetMemberByEmail(email);
    
    int size = pp->GetNumAttValPairs();
    for (int i = 0; i < size; i++) {
        AttValPair temp;
        if (pp->GetAttVal(i, temp)) {
            v.push_back(temp);
        }
    }
    
    size = v.size();
    PersonProfile compatiblePerson("", "");
    // a person has no repeated attribute value pairs, saves time
    for (int j = 0; j < size; j++) {
        vc = m_at->FindCompatibleAttValPairs(v[j]);
        for (int k = 0; k < vc.size(); k++) {
            // add each compatible to this compatible person
            compatiblePerson.AddAttValPair(vc[k]);
        }
    }
    
    size = compatiblePerson.GetNumAttValPairs();
    for (int a = 0; a < size; a++) {
        AttValPair attval;
        compatiblePerson.GetAttVal(a, attval); // this is O(1)
        vm = m_db->FindMatchingMembers(attval); // find all members of give attval
        for (int c = 0; c < vm.size(); c++) {
            if (vm[c] == email) {
                continue;
            }
            else {
                m_map[vm[c]]++; // put them in a map
            }
            
        }
    }
    
    for (unordered_map<string, int>::iterator p = m_map.begin(); p != m_map.end(); p++) {
        if (p->second >= threshold) {
            ve.push_back(EmailCount(p->first, p->second));
        }
    }
    sort(ve.begin(), ve.end(), comp); // sort
    return ve;
}




