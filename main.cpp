//main.cpp

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
using namespace std;

const std::string MEMBERS_FILE    = "/Users/allenwang/Desktop/project4/project4/members.txt";
const std::string TRANSLATOR_FILE = "/Users/allenwang/Desktop/project4/project4/translator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

void test() {
    MemberDatabase data;
    data.LoadDatabase(MEMBERS_FILE);
    AttValPair at1("trait", "inert");
    vector<std::string> ptr1 = data.FindMatchingMembers(at1);
    assert(ptr1.size() == 1389);

    AttValPair at2("trait", "odd");
    vector<std::string> ptr2 = data.FindMatchingMembers(at2);
    assert(ptr2.size() == 1479);

    AttValPair at3("job", "curator");
    vector<std::string> ptr3 = data.FindMatchingMembers(at3);
    assert(ptr3.size() == 4362);

    AttValPair at4("hobby", "improv");
    vector<std::string> ptr4 = data.FindMatchingMembers(at4);
    assert(ptr4.size() == 6303);

    AttValPair at5("hobby", "painting");
    vector<std::string> ptr5 = data.FindMatchingMembers(at5);
    assert(ptr5.size() == 6281);

    AttValPair at6("nononono", "nonoonoonn");
    vector<std::string> ptr6 = data.FindMatchingMembers(at6);
    assert(ptr6.empty());

    const PersonProfile *pp1 = data.GetMemberByEmail("AbFow2483@charter.net");
    assert(pp1->GetName() == "Abdullah Fowler");
    assert(pp1->GetNumAttValPairs() == 12);
    assert(pp1->GetEmail() == "AbFow2483@charter.net");

    const PersonProfile *pp2 = data.GetMemberByEmail("KingsleyW6127@yandex.com");
    assert(pp2->GetName() == "Kingsley Wade");
    assert(pp2->GetNumAttValPairs() == 6);
    assert(pp2->GetEmail() == "KingsleyW6127@yandex.com");

    const PersonProfile *pp3 = data.GetMemberByEmail("KyWo9@charter.net");
    assert(pp3->GetName() == "Kyle Wood");
    assert(pp3->GetNumAttValPairs() == 11);
    assert(pp3->GetEmail() == "KyWo9@charter.net");

    const PersonProfile *pp4 = data.GetMemberByEmail("nonoononno@nonon.com");
    assert(pp4 == nullptr);
}

int main() {
    test();
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
        ;

    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
      // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

      // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}
