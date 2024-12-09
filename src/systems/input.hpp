#include <functional>
#include <unordered_map>
#include <vector>

#include "ecs/system.hpp"

namespace bail::systems {

enum class KeyAction { Press, Release };

using KeyCode = int;
using InputCallback = std::function<void()>;

class InputSystem : public ecs::System {
public:
    void registerHook(KeyCode key, KeyAction action, InputCallback callback);
    void update(float dt) override;

private:
    std::unordered_map<KeyCode, std::unordered_map<KeyAction, std::vector<InputCallback>>> callbacks;
};

}