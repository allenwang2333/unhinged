#ifndef MEMBER_DATABASE_H
#define MEMBER_DATABASE_H

#include <string>
#include <vector>
#include "RadixTree.h"
#include "provided.h"

class PersonProfile;

class MemberDatabase {
    public:
        MemberDatabase();
        ~MemberDatabase();
        bool LoadDatabase(std::string filename);
        std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
        const PersonProfile* GetMemberByEmail(std::string email) const;
    private:
        RadixTree<PersonProfile*> m_treeByEmail; // email -----> PersonProfile
        std::vector<PersonProfile*> m_personPtr; // stores pointers of dynamically allocated memory
        RadixTree<std::vector<std::string>> m_treeByPair; // attribute ------> email
};

#endif
