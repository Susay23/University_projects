#pragma once
#include <vector>
#include <string>

struct Pole {
    std::string name;
    std::vector<int> disks;
};

class TowerOfHanoi
{
    public:
        int run(int disk, Pole& source, Pole& destination, Pole& auxiliary);
};