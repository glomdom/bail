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

#include <optional>
#include <unordered_map>

#include "aliases.hpp"

namespace bail::ecs {

template <typename Component>
class ComponentStorage {
    using ComponentMap = std::unordered_map<Entity, Component>;

public:
    void add(Entity entity, Component component) {
        components[entity] = std::move(component);
    }

    void remove(Entity entity) {
        components.erase(entity);
    }
    
    std::optional<std::reference_wrapper<Component>> get(Entity entity) {
        auto it = components.find(entity);
        if (it != components.end()) {
            return std::ref(it->second);
        }

        return std::nullopt;
    }

    template <typename Callback>
    void forEach(Callback&& callback) {
        for (auto& [entity, component] : components) {
            callback(entity, component);
        }
    }

    auto begin() { return components.begin(); }
    auto end() { return components.end(); }

private:
    ComponentMap components;
};

}