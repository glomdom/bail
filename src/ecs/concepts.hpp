#pragma once

#include <concepts>
#include <type_traits>

namespace bail::ecs {

template <typename T>
concept ComponentConcept = std::is_trivially_copyable_v<T> && std::is_default_constructible_v<T>;

template <typename T>
concept SystemConcept = requires(T t, float dt) {
    { t.update(dt) } -> std::same_as<void>;
};

}