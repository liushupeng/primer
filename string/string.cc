#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

#if 0
#define DEBUG
#endif

class String
{
  public:
    friend std::ostream & operator << (std::ostream &out, String &s);

    String () : str(new char[1]), size(0), capacity(0)
    { *str = '\0'; };

    String(const char *s): size(0), capacity(0)
    {
      if (s != NULL)
      {
	size = strlen(s);
	capacity = size;
	str = new char[capacity + 1];
	strcpy(str, s);
      }
    }
    
    String(const String &s)
    {
      if (s.str)
      {
	size = s.size;
	capacity = s.capacity;
	str = new char[capacity + 1];
	strcpy(str, s.str);
      }
    }

    String operator = (const String &s)
    {
      String tmp(s);

      std::swap(size, tmp.size);
      std::swap(capacity, tmp.capacity);
      std::swap(str, tmp.str);

      return (*this);
    }

    ~String()
    {
      if (str)
	delete [] str;
    }

  private:
    char *str;
    size_t size;
    size_t capacity;
};

std::ostream & operator << (std::ostream &out, String &s)
{
  out << s.str;
  return (out);
}

String func(const String &s)
{
  String ret(s);
  return (ret);
}

int main(int argc, char **argv)
{
  String s1("hello world");
  String s2;

  std::cout << s1 << std::endl;
  std::cout << s2 << std::endl;
  s2 = s1;
  std::cout << s2 << std::endl;

  String s3 = func(s2);
  std::cout << s3 << std::endl;

  std::vector<String> svec;
  svec.push_back(s1);
  svec.push_back(s2);
  svec.push_back(s3);

  for (std::vector<String>::iterator iter = svec.begin(); iter != svec.end(); iter++)
  {
    std::cout << "["<< iter - svec.begin() << "] " << *iter << std::endl;
  }

  return (0);
}

