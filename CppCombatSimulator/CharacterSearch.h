#pragma once

#include "Character.h"

#include <vector>

Character* findCharacterById(
    std::vector<Character>& party,
    int targetId
);