#ifndef MATCH_MAKER_H
#define MATCH_MAKER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "provided.h"

class MemberDatabase;

class AttributeTranslator;

class MatchMaker {
    public:
        MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
        ~MatchMaker();
        std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
    private:
        const MemberDatabase* m_db;
        const AttributeTranslator* m_at;
        
    
};

#endif
