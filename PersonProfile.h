#ifndef PERSONAL_PROFILE_H
#define PERSONAL_PROFILE_H

#include <string>
#include <vector>
#include "provided.h"
#include "RadixTree.h"

class PersonProfile {
    public:
        PersonProfile(std::string name, std::string email);
        ~PersonProfile();
        std::string GetName() const;
        std::string GetEmail() const;
        void AddAttValPair(const AttValPair& attval);
        int GetNumAttValPairs() const;
        bool GetAttVal(int attribute_num, AttValPair& attval) const;
    private:
        std::string m_name;
        std::string m_email;
        int m_num;
        RadixTree<std::vector<std::string>> m_tree; // a tree indicating whether exists
        std::vector<AttValPair> m_pair;  // a vector of attrval pari for retireval
};

#endif
