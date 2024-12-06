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

#include <stdexcept>
#include <unordered_map>

#include "aliases.hpp"
#include "concepts.hpp"
#include "entitymanager.hpp"

namespace bail::ecs {

template <ComponentConcept Component>
class ComponentStorage {
public:
    void add(Entity entity, Component component) {
        if (components.contains(entity)) {
            throw std::logic_error(std::format("component already exists for entity with id {}", entity));
        }

        components[entity] = std::move(component);
    }

    void remove(Entity entity) {
        if (components.contains(entity)) {
            throw std::logic_error(std::format("component not found for entity with id {}", entity));
        }

        components.erase(entity);
    }

    Component& get(Entity entity) {
        if (!contains(entity)) {
            throw std::out_of_range(std::format("entity {} does not have components", entity));
        }

        return components.at(entity);
    }

    bool contains(Entity entity) const {
        return components.contains(entity);
    }

    auto& getComponents() {
        return components;
    }

    template <typename Func>
    void forEach(Func func) {
        for (auto& [entity, component] : components) {
            func(entity, component);
        }
    }

private:
    std::unordered_map<Entity, Component> components;
    EntityManager manager;
};

}