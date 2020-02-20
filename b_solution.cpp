#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <ctype.h>
#include "b.h"

using namespace std;

#define loop(n) for (int i = 0; i < n; ++i) 
#define loop2(k,n) for (int i = k; i <= n; ++i) 
#define loopb(k,n) for (int i = k; i >= n; --i)
#define remove_space(x) x.erase(remove(x.begin(), x.end(), ' '), x.end())
typedef long long ll;

bool compareSignupDays(int ind1, int ind2) {
    return signup_duration_per_library[ind1] < signup_duration_per_library[ind2];
}

int main(){

    int libIndices[L];
    for (int i = 0; i < L; i++)
    {
        libIndices[i] = i;
    }

    sort(libIndices, libIndices + L, compareSignupDays);

    vector<int> resLibraries;
    vector<vector<int>> resBooks;
    vector<int> scannedBooks;
    int timeRemaining = D;
    int numResLibraries = 0;
    for (int i = 0; i < L; i++)
    {
        if (signup_duration_per_library[libIndices[i]] < timeRemaining)
        {
            int currentLibrary = libIndices[i];
            vector<int> booksFromThisLibrary = {};

            for (int j = 0; j < books_per_library[libIndices[i]]; j++)
            {
                if (!count(scannedBooks.begin(), scannedBooks.end(), books_in_library[libIndices[i]][j]))
                {
                    scannedBooks.push_back(books_in_library[libIndices[i]][j]);
                    booksFromThisLibrary.push_back(books_in_library[libIndices[i]][j]);
                }
            }
            if (!booksFromThisLibrary.empty()) {
                resLibraries.push_back(libIndices[i]);
                numResLibraries += 1; timeRemaining -= signup_duration_per_library[libIndices[i]];
                resBooks.push_back(booksFromThisLibrary);
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
        cout << "\n";
    }

	return 0;
}

