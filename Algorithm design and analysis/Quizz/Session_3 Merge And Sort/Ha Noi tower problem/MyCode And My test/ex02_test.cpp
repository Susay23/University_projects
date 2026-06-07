#include "TowerOfHanoi.hpp"
#include <iostream>
#include <gtest/gtest.h> 

TEST(TowerOfHanoiTest, TestMoveDisks) {
    TowerOfHanoi hanoi;
    Pole source{"A", {3, 2, 1}};
    Pole destination{"C", {}};
    Pole auxiliary{"B", {}};
    int numberOfMoves = hanoi.run(3, source, destination, auxiliary);
    EXPECT_EQ(numberOfMoves, 7);
}

TEST(TowerOfHanoiTest, TestMoveWithSteps)
{
    TowerOfHanoi hanoi;
    Pole source{"A", {3, 2, 1}};
    Pole destination{"C", {}};
    Pole auxiliary{"B", {}};
    std::string expectedSteps = "Move disk 1 from A to C\nMove disk 2 from A to B\nMove disk 1 from C to B\nMove disk 3 from A to C\nMove disk 1 from B to A\nMove disk 2 from B to C\nMove disk 1 from A to C\n";
    
    testing::internal::CaptureStdout();
    hanoi.run(3, source, destination, auxiliary);
    std::string actualSteps = testing::internal::GetCapturedStdout();

    EXPECT_EQ(actualSteps, expectedSteps);
}

TEST(TowerOfHanoiTest, TestMoveManyDisks) {
    TowerOfHanoi hanoi;
    for(int i = 1; i <= 20; ++i) {
        std::cout << "Testing with " << i << " disks..." << std::endl;
        Pole source{"A", {}};
        Pole destination{"C", {}};
        Pole auxiliary{"B", {}};
        for(int j = i; j >= 1; --j) {
            source.disks.push_back(j);
        }
        int numberOfMoves = hanoi.run(i, source, destination, auxiliary);
        EXPECT_EQ(numberOfMoves, (1 << i) - 1);
    }
}
