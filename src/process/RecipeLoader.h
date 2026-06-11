#pragma once

#include "ProcessRecipe.h"

#include <string>

class RecipeLoader {
public:
    ProcessRecipe loadFromFile(
        const std::string& filePath
    ) const;
};