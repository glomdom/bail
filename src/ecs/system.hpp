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
#include "query.hpp"

namespace bail::ecs {

template <typename... Components>
class System {
public:
    virtual ~System() = default;
    
    virtual void update(float dt, ComponentStorage<Components>&... storages) = 0;
};

template <typename... Components>
class QuerySystem : public System<Components...> {
protected:
    Query<Components...> createQuery(ComponentStorage<Components>&... storages) {
        return Query(storages...);
    }
};

}