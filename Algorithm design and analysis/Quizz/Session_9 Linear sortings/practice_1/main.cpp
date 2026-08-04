#include <stdio.h>
#include <iostream>

using namespace std;

const int maxn = 1000005;

int n;
int id[maxn];
long long score[maxn];

int idTemp[maxn];
long long scoreTemp[maxn];

// COUNTING-SORT-BY-ID(players, n):
//     range = 2n + 1
//     C = array[0..range-1] khởi tạo 0

//     for i = 1 to n:
//         C[players[i].id + n] += 1          // đếm tần suất

//     for j = 1 to range-1:
//         C[j] += C[j-1]                      // cộng dồn → vị trí cuối

//     B = array[1..n]
//     for i = n downto 1:                     // duyệt ngược để ổn định (stable)
//         B[C[players[i].id + n]] = players[i]
//         C[players[i].id + n] -= 1

//     return B

void coutingsortbyiD()
{
    int range = 2 * n + 1;
    int c[2 * maxn + 5];
    for (int i = 0; i < range; i++)
    {
        c[i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        int key = id[i] + n;
        c[key]++;
    }

    for (int i = 1; i < range; i++)
    {
        c[i] += c[i - 1];
    }

    for (int i = n; i >= 1; i--)
    {
        int key = id[i] + n;
        idTemp[c[key]] = id[i];
        c[key]--;
    }

    for (int i = 1; i <= n; i++)
    {
        id[i] = idTemp[i];
    }
}

// RADIX-SORT-BY-SCORE(players, n):
//     players = COUNTING-SORT-BY-DIGIT(players, n, 0)   // sắp theo d0 = score mod n
//     players = COUNTING-SORT-BY-DIGIT(players, n, 1)   // sắp theo d1 = score div n
//     return players

// COUNTING-SORT-BY-DIGIT(players, n, digit):
//     C = array[0..n-1] khởi tạo 0

//     for i = 1 to n:
//         key = (digit==0) ? players[i].score mod n : players[i].score div n
//         C[key] += 1

//     for j = 1 to n-1:
//         C[j] += C[j-1]

//     B = array[1..n]
//     for i = n downto 1:              // stable
//         key = (digit==0) ? players[i].score mod n : players[i].score div n
//         B[C[key]] = players[i]
//         C[key] -= 1

//     return B

void coutingsortbydigit(int digitpos)
{
    int base = n + 1;
    int c[maxn + 5];
    for (int i = 0; i < base; i++)
    {
        c[i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        int key;
        if (digitpos == 0)
        {
            key = score[i] % base;
        }
        else
        {
            key = score[i] / base;
        }
        c[key]++;
    }

    for (int i = 1; i < base; i++)
    {
        c[i] += c[i - 1];
    }

    for (int i = n; i >= 1; i--)
    {
        int key;
        if (digitpos == 0)
        {
            key = score[i] % base;
        }
        else
        {
            key = score[i] / base;
        }
        scoreTemp[c[key]] = score[i];
        c[key]--;
    }

    for (int i = 1; i <= n; i++){
        score[i] = scoreTemp[i];
    }
}

void radixsortbyscore(){
    coutingsortbydigit(0);
    coutingsortbydigit(1);
}

int main()
{
    freopen("ex01.inp", "r", stdin);
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> id[i];
    for (int i = 1; i <= n; i++)
        cin >> score[i];

    coutingsortbyiD();
    cout << "Sorted by ID:" << endl;
    for (int i = 1; i <= n; i++)
        cout << id[i] << " ";
    cout << endl;

    radixsortbyscore();
    cout << "Sorted by Score:" << endl;
    for (int i = 1; i <= n; i++)
        cout << score[i] << " ";
    cout << endl;
 
    return 0;
}