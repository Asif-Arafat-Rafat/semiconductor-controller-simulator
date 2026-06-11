#include "RecipeLoader.h"

#include <nlohmann/json.hpp>

#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

ProcessRecipe RecipeLoader::loadFromFile(
    const std::string& filePath
) const
{
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Failed to open recipe file: " + filePath
        );
    }

    json data;
    file >> data;

    if (!data.contains("name")) {
        throw std::runtime_error(
            "Recipe is missing 'name'"
        );
    }

    if (!data.contains("steps")) {
        throw std::runtime_error(
            "Recipe is missing 'steps'"
        );
    }

    ProcessRecipe recipe(
        data.at("name").get<std::string>()
    );


    if (data.at("steps").empty()) {
    throw std::runtime_error(
        "Recipe must contain at least one step"
    );
}
    for (const auto& step : data.at("steps")) {
        if(!step.contains("name") || !step.contains("targetTemperature") || !step.contains("durationSeconds")) {
            throw std::runtime_error(
                "Step is missing required fields"
            );
        }

        const std::string name =
            step.at("name").get<std::string>();

        const double temperature =
            step.at("targetTemperature").get<double>();

        const int duration =
            step.at("durationSeconds").get<int>();

        if (name.empty()) {
            throw std::runtime_error(
                "Recipe step name cannot be empty"
            );
        }

        if (duration <= 0) {
            throw std::runtime_error(
                "Recipe step duration must be greater than zero"
            );
        }

        recipe.addStep(
            ProcessStep(
                name,
                temperature,
                duration
            )
        );
    }

    return recipe;
}