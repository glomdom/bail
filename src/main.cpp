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

#include "ecs/systemmanager.hpp"
#include "systems/input.hpp"

#include "raylib.h"

using namespace bail;

int main() {
    try {
        InitWindow(800, 600, "bail engine v0.0.0.0.0.0a");

        ecs::SystemManager systemManager;
        auto& inputSystem = systemManager.addSystem<systems::InputSystem>();

        inputSystem.registerHook(KEY_SPACE, systems::KeyAction::Press, []() {
            std::cout << "space pressed\n";
        });

        inputSystem.registerHook(KEY_SPACE, systems::KeyAction::Release, []() {
            std::cout << "space released\n";
        });

        while (!WindowShouldClose()) {
            systemManager.update(1.0f / 60.0f);

            BeginDrawing();
            ClearBackground(RAYWHITE);
            EndDrawing();
        }

        CloseWindow();
    } catch (std::exception& e) {
        std::cerr << e.what();

        CloseWindow();
    }

    return EXIT_SUCCESS;
}