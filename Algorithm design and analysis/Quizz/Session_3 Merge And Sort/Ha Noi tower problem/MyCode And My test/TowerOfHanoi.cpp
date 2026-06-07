#include "TowerOfHanoi.hpp"
#include <iostream>

void displayMove(int disk, const std::string& from, const std::string& to) {
    std::cout << "Move disk " << disk << " from " << from << " to " << to << std::endl;
}

int TowerOfHanoi::run(int disk, Pole &source, Pole &destination, Pole &auxiliary)
{
    if (disk == 1)
    {
        displayMove(disk, source.name, destination.name);
        destination.disks.push_back(source.disks.back());
        source.disks.pop_back();
        return 1;
    }
    int moves = TowerOfHanoi::run(disk - 1, source, auxiliary, destination);
    
    displayMove(disk, source.name, destination.name);
    destination.disks.push_back(source.disks.back());
    source.disks.pop_back();
    moves += 1;

    moves += TowerOfHanoi::run(disk - 1, auxiliary, destination, source);
    return moves;
}