#define B 6
#define L 2
#define D 7
int books[B] {1,2,3,6,5,4};
int books_per_library[L] = {5 ,4 ,};
int signup_duration_per_library[L] = {2 ,3 ,};
int scan_per_day_per_library[L] = {2,1,};
#include <vector>
std::vector<int> books_in_library[L] =
{
	{0,1,2,3,4},
	{0,2,3,5}
};
