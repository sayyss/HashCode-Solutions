#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <ctype.h>
#include <math.h>
#include "a.h"

using namespace std;

#define loop(n) for (int i = 0; i < n; ++i) 
#define loop2(k,n) for (int i = k; i <= n; ++i) 
#define loopb(k,n) for (int i = k; i >= n; --i)
#define remove_space(x) x.erase(remove(x.begin(), x.end(), ' '), x.end())
typedef long long ll;

float Lscores[L];

int main(){
    for (int i = 0; i < L; i++)
    {
        Lscores[i] = getScore(i);
    }

    int sortedBooksIndices[B];
    for (int i = 0; i < B; i++)
    {
        sortedBooksIndices[i] = i;
    }

    sort(sortedBooksIndices, sortedBooksIndices + B, compareBooks);

    int libIndices[L];
    for (int i = 0; i < L; i++)
    {
        libIndices[i] = i;
    }
    sort(libIndices, libIndices + L, compareScores);

    vector<int> resLibraries;
    vector<vector<int>> resBooks;
    vector<int> scannedBooks;
    int timeRemaining = D;
    int numResLibraries = 0;
    for (int i = 0; i < L; i++)
    {
        if (signup_duration_per_library[libIndices[i]] < timeRemaining)
        {
            resLibraries[numResLibraries] = libIndices[i];
            numResLibraries += 1; timeRemaining -= signup_duration_per_library[libIndices[i]];
            int numBooksAddedFromThisLibrary = 0;
            for (int j = 0; j < books_per_library[libIndices[i]]; j++)
            {
                if (!count(scannedBooks.begin(), scannedBooks.end(), books_in_library[libIndices[i]][j]))
                {
                    scannedBooks[scannedBooks.size()] = books_in_library[libIndices[i]][j];
                    resBooks[numResLibraries - 1][numBooksAddedFromThisLibrary] = books_in_library[libIndices[i]][j];
                    numBooksAddedFromThisLibrary += 1;
                }
            }
        }
    }
    cout << numResLibraries << "\n";
    for (int i = 0; i < numResLibraries; i++)
    {
        int numBooksFromThisLibrary = resBooks[i].size();
        cout << resLibraries[i] << " " << numBooksFromThisLibrary << "\n";
        for (int j = 0; j < numBooksFromThisLibrary; j++)
            cout << resBooks[i][j] << " ";
    }
	return 0;
}


float getScore(int libIndex)
{
    float Nj = books_per_library[libIndex];
    float Mj = scan_per_day_per_library[libIndex];
    float T = signup_duration_per_library[libIndex];
    float sigma_scores = 0;
    for (int i = 0; i < Nj; i++)
    {
        sigma_scores += books[books_in_library[libIndex][i]];
    }
    float score = (Nj / (T + (Nj/Mj))) * (sigma_scores / Nj);
    return score;
}

bool compareScores(int ind1, int ind2)
{
    return Lscores[ind1] > Lscores[ind2];
}

bool compareBooks(int ind1, int ind2)
{
    return books[ind1] > books[ind2];
}