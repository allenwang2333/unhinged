#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "MatchMaker.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "RadixTree.h"

using namespace std;

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
    m_db = &mdb;
    m_at = &at;
}

MatchMaker::~MatchMaker() {
    
}

bool comp(const EmailCount& e1, const EmailCount& e2) {
    if (e1.count > e2.count) return true;
    else if (e1.count < e2.count) return false;
    else if (e1.email < e2.email) return true;
    else return false;
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
    vector<AttValPair> v; // pair of this person
    vector<AttValPair> vc; // compatible pairs
    vector<string> vm;
    vector<EmailCount> ve;
    unordered_map<string, int> m_map;
    const PersonProfile* pp = m_db->GetMemberByEmail(email);
    int size = pp->GetNumAttValPairs();
    for (int i = 0; i < size; i++) {
        AttValPair av;
        if (pp->GetAttVal(i, av)) {
            v.push_back(av);
        }
    }
    size = v.size();
    for (int j = 0; j < size; j++) {
        vc = m_at->FindCompatibleAttValPairs(v[j]);
        for (int k = 0; k < vc.size(); k++) {
            vm = m_db->FindMatchingMembers(vc[k]);
            for (int l = 0; l < vm.size(); l++) {
                auto it = m_map.find(vm[l]);
                if (it == m_map.end()) {
                    m_map.insert(make_pair(vm[l], 1));
                }
                else {
                    it->second++;
                }
            }
        }
    }
    for (unordered_map<string, int>::iterator p = m_map.begin(); p != m_map.end(); p++) {
        if (p->second >= threshold) {
            ve.push_back(EmailCount(p->first, p->second));
        }
    }
    sort(ve.begin(), ve.end(), comp);
    return ve;
}




