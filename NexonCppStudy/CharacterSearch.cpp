#include "CharacterSearch.h"

Character* findCharacterById(
    std::vector<Character>& party,
    int targetId
)
{
    for (Character& member : party)
    {
        if (member.getId() == targetId)
        {
            return &member;
        }
    }

    return nullptr;
}