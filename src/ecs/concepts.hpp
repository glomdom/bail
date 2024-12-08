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