#include <iostream>
#include <vector>


int readInput()
{
    int disk;
    std::cin >> disk;
    return disk;
}

class towerOfHanoi
{
public:
    int run(int disk, std::vector<int> &source, std::vector<int> &destination, std::vector<int> &auxiliary)
    {
        if (disk == 1)
        {
            destination.push_back(source.back());
            source.pop_back();
            return 1;
        }
        int moves = run(disk - 1, source, auxiliary, destination);
        destination.push_back(source.back());
        source.pop_back();
        moves += 1;

        moves += run(disk - 1, auxiliary, destination, source);
        return moves;
    }
};
int main()
{
    freopen("ex02.inp", "r", stdin);
    int disk = readInput();
    std::vector<int> A;
    std::vector<int> B;
    std::vector<int> C;
    for (int i = disk; i >= 1; --i)
    {
        A.push_back(i);
    }
    towerOfHanoi _towerOfHanoi;
    int numberOfMoves = _towerOfHanoi.run(disk, A, C, B);
    for (int i = C.size() - 1; i >= 0; --i)
    {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Total moves: " << numberOfMoves << std::endl;
}