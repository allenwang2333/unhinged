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
        struct Counter {
            Counter(std::string attr) :m_attr(attr), m_number (0){}
            std::string m_attr;
            int m_number;
        };
        std::vector<Counter> m_cntVec;
        RadixTree<std::vector<AttValPair>> m_pair;
};

#endif
