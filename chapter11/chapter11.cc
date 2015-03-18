#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

int main(void)
{
  vector<int>	ivec;

  for (vector<int>::size_type i = 0; i != 10; i++)
    ivec.push_back(i);

  vector<int>::iterator ret = find(ivec.begin(), ivec.end(), 18);
  if (ret != ivec.end())
    cout << "find key ..." << endl;
  return 0;
}
