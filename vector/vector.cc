#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <memory>

#if 0
#define DEBUG
#endif

template <typename T> class Vector
{
  public:
    Vector() : element(0), first_free(0), end(0) {};
    
    bool empty() { return (element == first_free); }
    size_t size() { return (first_free - element); }
    size_t capacity() { return (end - element); }
    void push_back(const T &t);
    
    void print()
    {
      for (T *p = element; p != first_free; p++)
	std::cout << *p << std::endl;
    }

    ~Vector()
    {
      /* 逆向析构每个元素 */
      for (T *p = first_free; p != element;)
	alloc.destroy(--p);
      
      /* 释放内存 */
      if (element)
	alloc.deallocate(element, end - element);
    }

  private:
    static std::allocator<T> alloc;
    void reallocate();
    T *element;
    T *first_free; /* 指向空闲内存的第一个位置 */
    T *end;
};

template <typename T> std::allocator<T> Vector<T>::alloc;

template <typename T> void Vector<T>::reallocate()
{
  std::ptrdiff_t oldsize = first_free - element;
  std::ptrdiff_t newcapacity = 2 * std::max(static_cast<int>(oldsize), 1);
  
  T *newelement = alloc.allocate(newcapacity);
  std::uninitialized_copy(element, end, newelement);

  /* 逆向析构每个元素 */
  for (T *p = first_free; p != element;)
    alloc.destroy(--p);
  
  /* 释放内存 */
  if (element)
    alloc.deallocate(element, end - element);
  
  element = newelement;
  first_free = newelement + oldsize;
  end = element + newcapacity;
}

template <typename T> void Vector<T>::push_back(const T &t)
{
  if (first_free == end)
    reallocate();
  
  Vector<T>::alloc.construct(first_free, t);
  first_free++;
}

int main(int argc, char **argv)
{
  Vector<int> ivec;
  ivec.push_back(12);
  ivec.push_back(15);
  ivec.push_back(19);
  ivec.push_back(21);
  ivec.push_back(33);
  ivec.print();
  
  Vector<std::string> svec;
  svec.push_back("hello");
  svec.push_back("world");
  svec.push_back("hello");
  svec.push_back("C++");
  svec.push_back("!");
  svec.print();

  return (0);
}

