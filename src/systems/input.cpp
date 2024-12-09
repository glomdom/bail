#include "input.hpp"

#include "raylib.h"

namespace bail::systems {

void InputSystem::registerHook(KeyCode key, KeyAction action, InputCallback callback) {
    callbacks[key][action].push_back(std::move(callback));
}

void InputSystem::update(float dt) {
    for (const auto& [key, actions] : callbacks) {
        if (IsKeyPressed(key) && actions.count(KeyAction::Press)) {
            for (auto& callback : actions.at(KeyAction::Press)) {
                callback();
            }
        }

        if (IsKeyReleased(key) && actions.count(KeyAction::Release)) {
            for (auto& callback : actions.at(KeyAction::Release)) {
                callback();
            }
        }
    }
}

}