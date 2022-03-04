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
        struct Data {
            std::string m_attr;
            int m_size;
            RadixTree<std::vector<AttValPair>> m_pair;
        };
        std::vector<Data> m_data;
};

#endif
