/*
    Copyright (C) 2024  glomdom

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "entitymanager.hpp"

#include <stdexcept>

namespace bail::ecs {

Entity EntityManager::createEntity() {
    if (!availableEntities.empty()) {
        Entity id = availableEntities.front();
        availableEntities.pop();

        return id;
    }

    if (next >= generations.size()) {
        generations.resize(next + 1, 0);
    }

    return next++;
}

void EntityManager::destroyEntity(Entity entity) {
    if (entity < generations.size()) {
        ++generations[entity];
        availableEntities.push(entity);

        for (const auto& remover : removers) {
            remover(entity);
        }
    }
}

bool EntityManager::isValid(Entity entity, uint32_t generation) const {
    bool inRange = entity < generations.size();
    bool generationMatch = inRange && generations[entity] == generation;

    return generationMatch;
}

Generation EntityManager::getEntityGeneration(Entity entity) const {
    if (entity >= generations.size()) {
        throw std::runtime_error("invalid entity id");
    }

    return generations[entity];
}

}