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

#include "componentstorage.hpp"
#include "concepts.hpp"

namespace bail::ecs {

class System {
public:
    virtual ~System() = default;
    virtual void update(float dt) = 0;

    template <ComponentConcept... Components>
    auto createQuery(ComponentStorage<Components>&... storages) {
        return [&, this](auto&& func) {
            for (auto& [entity, component] : std::get<0>(std::forward_as_tuple(storages...)).getComponents()) {
                if ((storages.contains(entity) && ...)) {
                    func(entity, storages.get(entity)...);
                }
            }
        };
    }
};

}