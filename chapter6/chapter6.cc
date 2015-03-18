#include <iostream>
#include <bitset>
#include <stdexcept>
using namespace std;

int main()
{
  bitset<100> bs;

  for (size_t i = 0; i < bs.size(); i++)
    bs[i] = 1;

  try
  {
    bs.to_ulong();
  }
  catch(runtime_error err)
  {
    cout << __FILE__ << ":" << __LINE__ << err.what() << endl;
  }

  return (0);
}
