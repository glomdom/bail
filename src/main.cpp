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

class MovementSystem : public ecs::System<Transform, Velocity> {
public:
    MovementSystem() = default;

    void update(float dt, ecs::ComponentStorage<Transform>& transforms, ecs::ComponentStorage<Velocity>& velocities) override {
        transforms.forEach([&](ecs::Entity entity, Transform& transform) {
            if (auto velocity = velocities.get(entity)) {
                transform.x += velocity->get().dx * dt;
                transform.y += velocity->get().dy * dt;
            }
        });
    }
};

int main() {
    ecs::EntityManager entityManager;
    ecs::ComponentStorage<Transform> transforms;
    ecs::ComponentStorage<Velocity> velocities;
    ecs::SystemManager systemManager;

    entityManager.registerStorage(transforms);
    entityManager.registerStorage(velocities);

    auto entity = entityManager.createEntity();
    transforms.add(entity, {0, 0});
    velocities.add(entity, {1, 1});

    systemManager.addSystem<MovementSystem>(transforms, velocities);

    const float dt = 1.0f / 60.0f;
    for (int i = 0; i < 10; ++i) {
        auto transform = transforms.get(entity);
        if (transform) {
            std::cout << "entity position -> (" << transform->get().x << ", " << transform->get().y << ")\n";
        }

        systemManager.update(dt);
    }

    entityManager.destroyEntity(entity);

    if (!transforms.get(entity)) {
        std::cout << "transform component cleaned up successfully\n";
    }

    if (!velocities.get(entity)) {
        std::cout << "velocity component cleaned up successfully\n";
    }

    return 0;
}