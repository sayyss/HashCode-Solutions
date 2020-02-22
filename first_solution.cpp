#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <ctype.h>
#include <math.h>
#include <fstream>

using namespace std;

#define loop(n) for (int i = 0; i < n; ++i) 
#define loop2(k,n) for (int i = k; i <= n; ++i) 
#define loopb(k,n) for (int i = k; i >= n; --i)
#define remove_space(x) x.erase(remove(x.begin(), x.end(), ' '), x.end())
typedef long long ll;

int B, D, L;
vector<int> books, books_per_library, scan_per_day_per_library, signup_duration_per_library;
vector<vector<int>> books_in_library;
vector<float> Lscores;

bool compareScores(int ind1, int ind2)
{
    return Lscores[ind1] > Lscores[ind2];
}

bool compareBooks(int ind1, int ind2)
{
    return books[ind1] > books[ind2];
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
    float time_taken = T + (Nj / Mj);
    float score = (Nj * sigma_scores) / (time_taken * time_taken);
    return score;
}

void readFromFile(string filename)
{
    ifstream infile;
    infile.open(filename, ios::in);

    infile >> B >> L >> D;
    int temp;
    for (int i = 0; i < B; i++)
    {
        infile >> temp;
        books.push_back(temp);
    }
    for (int i = 0; i < L; i++)
    {
        infile >> temp;
        books_per_library.push_back(temp);
        infile >> temp;
        signup_duration_per_library.push_back(temp);
        infile >> temp;
        scan_per_day_per_library.push_back(temp);
        books_in_library.push_back({});
        for (int j = 0; j < books_per_library[i]; j++)
        {
            infile >> temp;
            books_in_library[i].push_back(temp);
        }
    }
}

int main(){

    readFromFile("e_so_many_books.txt");

    for (int i = 0; i < L; i++)
    {
        Lscores.push_back(getScore(i));
    }

    vector<int> libIndices;
    for (int i = 0; i < L; i++)
    {
        libIndices.push_back(i);
    }
    sort(libIndices.begin(), libIndices.end(), compareScores);

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

            sort(books_in_library[libIndices[i]].begin(), books_in_library[libIndices[i]].end(), compareBooks);

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
