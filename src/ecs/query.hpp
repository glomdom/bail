#pragma once

#include <tuple>

#include "aliases.hpp"
#include "componentstorage.hpp"

namespace bail::ecs {

template <typename FirstComponent, typename... OtherComponents>
class Query {
public:
    Query(ComponentStorage<FirstComponent>& first, ComponentStorage<OtherComponents>&... storages)
        : firstStorage(first), otherStorages(std::tie(storages...)) {}

    template <typename Func>
    void forEach(Func&& func) {
        firstStorage.forEach([&](Entity entity, FirstComponent& firstComponent) {
            if ((std::get<ComponentStorage<OtherComponents>&>(otherStorages).get(entity).has_value() && ...)) {
                func(
                    entity,
                    firstComponent,
                    std::get<ComponentStorage<OtherComponents>&>(otherStorages).get(entity)->get()...
                );
            }
        });
    }

private:
    ComponentStorage<FirstComponent>& firstStorage;
    std::tuple<ComponentStorage<OtherComponents>&...> otherStorages;
};


}