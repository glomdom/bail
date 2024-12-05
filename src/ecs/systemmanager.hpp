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

#include <memory>
#include <tuple>
#include <vector>
#include <utility>

#include "system.hpp"
#include "componentstorage.hpp"

namespace bail::ecs {

class SystemBase {
public:
    virtual ~SystemBase() = default;

    virtual void update(float dt) = 0;
};

template <typename... Components>
class SystemWrapper : public SystemBase {
public:
    SystemWrapper(std::unique_ptr<System<Components...>> system, std::tuple<ComponentStorage<Components>&...> storages)
        : system(std::move(system)), storages(std::move(storages)) {}

    void update(float dt) override {
        std::apply([this, dt](ComponentStorage<Components>&... storages) {
            system->update(dt, storages...);
        }, storages);
    }

private:
    std::unique_ptr<System<Components...>> system;
    std::tuple<ComponentStorage<Components>&...> storages;
};

class SystemManager {
public:
    template <typename SystemType, typename... Components>
    void addSystem(ComponentStorage<Components>&... storages) {
        static_assert(std::is_default_constructible_v<SystemType>, "SystemType must be default constructible!");

        auto system = std::make_unique<SystemType>();
        auto wrapper = std::make_unique<SystemWrapper<Components...>>(
            std::move(system),
            std::tie(storages...)
        );

        systems.push_back(std::move(wrapper));
    }

    void update(float dt) {
        for (auto& system : systems) {
            system->update(dt);
        }
    }

private:
    std::vector<std::unique_ptr<SystemBase>> systems;
};

}
