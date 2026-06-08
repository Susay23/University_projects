#include <iostream>
#include <vector>

#include "TowerOfHanoi.hpp"

int readInput() {
    int disk;
    std::cin >> disk;
    return disk;
}

int main()
{
    freopen("ex02_inp.txt", "r", stdin);
    int disk = readInput();
    Pole A{"A", {}};
    Pole B{"B", {}};
    Pole C{"C", {}};
    for (int i = disk; i >= 1; --i) 
    {
        A.disks.push_back(i);
    }

    TowerOfHanoi hanoi;
    int numberOfMoves = hanoi.run(disk, A, C, B);
    std::cout << "Final state of pole C: ";
    for (int i = (int)C.disks.size() - 1; i >= 0; --i) 
    {
        std::cout << C.disks[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Total moves: " << numberOfMoves << std::endl;
}