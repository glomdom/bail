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

#include <any>
#include <memory>
#include <typeindex>
#include <vector>

#include "componentstorage.hpp"
#include "concepts.hpp"
#include "system.hpp"

namespace bail::ecs {

class SystemManager {
public:
    EntityManager& getEntityManager();
    void update(float dt);

    template <SystemConcept T, typename... Args>
    T& addSystem(Args&&... args) {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        systems.emplace_back(std::move(system));

        return static_cast<T&>(*systems.back());
    }

    template <ComponentConcept T>
    ComponentStorage<T>& getStorage() {
        auto typeIndex = std::type_index(typeid(ComponentStorage<T>));
        if (componentStorages.find(typeIndex) == componentStorages.end()) {
            componentStorages[typeIndex] = std::make_any<ComponentStorage<T>>();
        }

        return *std::any_cast<ComponentStorage<T>>(&componentStorages[typeIndex]);
    }

private:
    EntityManager entityManager;
    std::vector<std::unique_ptr<System>> systems;
    std::unordered_map<std::type_index, std::any> componentStorages;
};

}
