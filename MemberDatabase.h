#ifndef MEMBER_DATABASE_H
#define MEMBER_DATABASE_H

#include <string>
#include <vector>
#include "RadixTree.h"

class AttValPair;

class PersonProfile;

class MemberDatabase {
    public:
        MemberDatabase();
        ~MemberDatabase();
        bool LoadDatabase(std::string filename);
        std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
        const PersonProfile* GetMemberByEmail(std::string email) const;
    private:
        
};

#endif
