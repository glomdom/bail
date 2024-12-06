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

#include <format>
#include <stdexcept>

#include "aliases.hpp"

namespace bail::ecs {

Entity EntityManager::createEntity() {
    if (!availableEntities.empty()) {
        Entity id = availableEntities.front();
        availableEntities.pop();
        ++generationCounters[id];

        return id;
    }

    Entity id = nextEntity++;
    generationCounters[id] = 0;

    return id;
}

void EntityManager::destroyEntity(Entity entity) {
    if (!isValid(entity)) {
        return;
    }

    availableEntities.push(entity);
    ++generationCounters[entity];

    for (const auto& remover : removers) {
        remover(entity);
    }
}

void EntityManager::registerRemover(std::function<void(Entity)> remover) {
    removers.push_back(remover);
}

bool EntityManager::isValid(Entity entity) const {
    return generationCounters.find(entity) != generationCounters.end();
}

Generation EntityManager::getEntityGeneration(Entity entity) const {
    if (!isValid(entity)) {
        throw std::runtime_error(std::format("invalid entity with id {}", entity));
    }

    return generationCounters.at(entity);
}

}