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

#pragma once

#include <functional>
#include <queue>
#include <vector>

#include "aliases.hpp"
#include "componentstorage.hpp"

namespace bail::ecs {

class EntityManager {
public:
    Entity createEntity();
    void destroyEntity(Entity entity);

    template <typename Component>
    void registerStorage(ComponentStorage<Component>& storage) {
        removers.emplace_back([&storage](Entity entity) {
            storage.remove(entity);
        });
    }

    bool isValid(Entity entity, uint32_t generation) const;

private:
    std::queue<uint32_t> availableEntities;
    std::vector<uint32_t> generations;
    uint32_t next = 0;

    std::vector<std::function<void(Entity)>> removers;
};

}