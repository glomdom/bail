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

#include <tuple>

#include "aliases.hpp"
#include "componentstorage.hpp"

namespace bail::ecs {

template <typename FirstComponent, typename... OtherComponents>
class Query {
public:
    Query(ComponentStorage<FirstComponent>& first, ComponentStorage<OtherComponents>&... storages)
        : firstStorage(first), otherStorages(std::tie(storages...)) {}

    template <typename Func>
    void forEach(Func&& func) {
        firstStorage.forEach([&](Entity entity, FirstComponent& firstComponent) {
            if ((std::get<ComponentStorage<OtherComponents>&>(otherStorages).get(entity).has_value() && ...)) {
                func(
                    entity,
                    firstComponent,
                    std::get<ComponentStorage<OtherComponents>&>(otherStorages).get(entity)->get()...
                );
            }
        });
    }

private:
    ComponentStorage<FirstComponent>& firstStorage;
    std::tuple<ComponentStorage<OtherComponents>&...> otherStorages;
};


}