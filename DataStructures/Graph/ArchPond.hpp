#include <iostream>
#pragma once

template <class T, typename U>
struct ArchPond{
    public:
        int destinyIndex;
        T weight;
        U label;

        friend std::ostream& operator<<(std::ostream& os, const ArchPond& arch){
            os << "DestinyIndex: " << arch.destinyIndex << " Weight: " << arch.weight << " Label: " << arch.label;
            return os;
        }
};
