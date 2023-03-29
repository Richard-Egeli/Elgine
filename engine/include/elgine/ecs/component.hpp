#pragma once

using ComponentId = unsigned long long int;

struct Component {
    ComponentId id;
    static ComponentId componentIdCounter;

    template <typename T>
    static ComponentId GetId() {
        static ComponentId id = componentIdCounter++;
        return id;
    }
};
