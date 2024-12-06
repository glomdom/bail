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

#include <exception>
#include <iostream>

#include "ecs/entitymanager.hpp"
#include "ecs/componentstorage.hpp"
#include "ecs/system.hpp"
#include "ecs/systemmanager.hpp"

using namespace bail;

struct Transform {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

struct Gravity {
    float force = 9.8f;
};

struct Lifetime {
    float timeLeft;
};

class GravitySystem : public ecs::System {
public:
    GravitySystem(ecs::ComponentStorage<Velocity>& velocities, ecs::ComponentStorage<Gravity>& gravities)
        : velocities(velocities), gravities(gravities) {}

    void update(float dt) override {
        auto query = createQuery();
        query([&](ecs::Entity entity, Velocity& velocity, Gravity& gravity) {
            velocity.dy += gravity.force * dt;
        });
    }

private:
    ecs::ComponentStorage<Velocity>& velocities;
    ecs::ComponentStorage<Gravity>& gravities;
};

int main() {
    try {
        ecs::SystemManager systemManager;
        auto entity1 = systemManager.getEntityManager().createEntity();

        auto& transforms = systemManager.getStorage<Transform>();
        auto& velocities = systemManager.getStorage<Velocity>();
        auto& gravities = systemManager.getStorage<Gravity>();
        auto& lifetimes = systemManager.getStorage<Lifetime>();

        transforms.add(entity1, { 0, 0 });
        velocities.add(entity1, { 10, 0 });
        gravities.add(entity1, { 9.8f });
        lifetimes.add(entity1, { 5.0f });

        auto& gravitySystem = systemManager.addSystem<GravitySystem>(velocities, gravities);

        const float dt = 1.0f / 60.0f;
        for (int i = 0; i < 600; ++i) {
            systemManager.update(dt);

            std::cout << "frame: " << i << "\n";

            transforms.forEach([](ecs::Entity entity, Transform& transform) {
                std::cout << "Entity " << entity << " position -> (" << transform.x << ", " << transform.y << ")\n";
            });
        }
    } catch (std::exception& e) {
        std::cerr << e.what();
    }

    return 0;
}