#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <algorithm>

#undef DEBUG
#define BAND	10	/* 以10000进制进行计算 */

class BigInt
{
  public:
    friend std::ostream& operator << (std::ostream &o, const BigInt &c);
    
    BigInt(const std::string &s = "")
    {
      str2vector(s);
    }
    
    BigInt(const BigInt &bi)
    {
      neg = bi.neg;
      bint.assign(bi.bint.begin(), bi.bint.end());
    }

    BigInt operator + (const BigInt &c)
    {
      BigInt tmp;
     
      if (neg && c.neg) /* 两者都是负, 求和，符号为负 */
      {
	tmp.neg = true;
	tmp.bint = Sum(bint, c.bint);
      }
      else if (!neg && !c.neg)
      {
        tmp.neg = false;
	tmp.bint = Sum(bint, c.bint); 
      }
      else if (!neg && c.neg)
      {
	tmp.bint = Diff(bint, c.bint, tmp.neg);
      }
      else if (neg && !c.neg)
      {
        tmp.bint = Diff(c.bint, bint, tmp.neg);
      }
      return (tmp);
    }
    
    BigInt operator - (const BigInt &c)
    {
      BigInt tmp;
      if (neg && c.neg) /* 两者都是负, 求差 */
      {
        tmp.bint = Diff(c.bint, bint, tmp.neg);
	
      }
      else if (!neg && !c.neg)
      {
	tmp.bint = Diff(bint, c.bint, tmp.neg);
        
      }
      else if (!neg && c.neg)
      {
	tmp.neg = true;
	tmp.bint = Sum(bint, c.bint);
      }
      else if (neg && !c.neg)
      {
	tmp.neg = false;
	tmp.bint = Sum(bint, c.bint); 
      }
      return (tmp);
    }
    
    BigInt operator * (const BigInt &c)
    {
      BigInt tmp;
      if ((neg && c.neg) || (!neg && !c.neg))
      {
	tmp.neg = false; 
        tmp.bint = Multi(bint, c.bint);
      }
      else if ((!neg && c.neg) || (neg && !c.neg))
      {
	tmp.neg = true;
	tmp.bint = Multi(bint, c.bint);
      }
      return (tmp);
    }

  private:
    inline int bandsize(int band)
    {
      int sz = 0;
      while ((band = band / 10))
	sz++;
      return (sz);
    }

    inline void str2vector(const std::string &s)
    {
      /* 将字符串以4个数字为一组，转换为int，存储到vector<int>中 */
      std::string s1;
      int val, size = bandsize(BAND);
      neg = false;
      for (ssize_t pos = s.size() - size; pos > -size; pos -= size)
      {
	if (pos >= 0)
	  s1.assign(s, pos, size);
	else
	  s1.assign(s, 0, size + pos);

	if (s1.compare("-") == 0)
	{
	  neg = true;
	  break;
	}

	val = atoi(s1.c_str());
	if (val < 0)
	  neg = true;
        #ifdef DEBUG
	std::cout << s1 << "-----" << val << std::endl;
        #endif
	bint.push_back(abs(val));
      }
    }

    std::vector<int> Sum(const std::vector<int> &i1, const std::vector<int> &i2);
    std::vector<int> Diff(const std::vector<int> &i1, const std::vector<int> &i2, bool &ret);
    std::vector<int> Multi(const std::vector<int> &i1, const std::vector<int> &i2);
    
    bool neg;
    std::vector<int> bint; /* bint[0] 存储的是最低位 */
};

std::vector<int> BigInt::Sum(const std::vector<int> &i1, const std::vector<int> &i2)
{
  std::vector<int> tmp;
  ssize_t l1, l2;
  int sum, s1, s2, carry;
  
  for(carry = 0, l1 = 0, l2 = 0; l1 < i1.size() || l2 < i2.size(); l1++, l2++)
  {
    s1 = l1 < i1.size() ? i1.at(l1) : 0;
    s2 = l2 < i2.size() ? i2.at(l2) : 0;
    sum = s1 + s2 + carry;
    carry = sum / BAND;
    tmp.push_back(sum % BAND);
  }
  if (sum >= BAND) /* 最后一个进位 */
    tmp.push_back(carry);

  return (tmp);
}

std::vector<int> BigInt::Diff(const std::vector<int> &i1, const std::vector<int> &i2, bool &ret)
{
  std::vector<int> tmp;
  ssize_t l1, l2;
  int diff, d1, d2, dd, carry;

  if (i1.size() < i2.size())
    ret = true;
  else if (i1.size() > i2.size())
    ret = false;
  else if (i1.size() == i2.size())
  {
    for (l1 = i1.size() - 1; l1 >= 0; l1--)
    {
      if (i1.at(l1) != i2.at(l1))
	break;
    }

    if (l1 >= 0)
    {
      if (i1.at(l1) < i2.at(l1))
	ret = true;
      else if (i1.at(l1) > i2.at(l1))
	ret = false;
    }
    else
    {
      ret = false;
      tmp.push_back(0);
      return (tmp);
    }
  }

  for(carry = 0, l1 = 0, l2 = 0; l1 < i1.size() || l2 < i2.size();l1++, l2++)
  {
    d1 = l1 < i1.size() ? i1.at(l1) : 0;
    d2 = l2 < i2.size() ? i2.at(l2) : 0;
    dd = ret ? d2 - d1 : d1 - d2;
    diff  = dd - carry;
    carry = diff < 0 ? 1 : 0;
    diff += BAND;
    
    tmp.push_back(diff);
  }
  return (tmp);
}

std::vector<int> BigInt::Multi(const std::vector<int> &i1, const std::vector<int> &i2)
{
  std::vector<int> tmp;
  return (tmp);
}

std::ostream& operator << (std::ostream &o, const BigInt &c)
{
  if (c.neg)
    o << "-";
  for(ssize_t i = c.bint.size() - 1; i >= 0; i--)
  {
    o << c.bint.at(i);
  }
  return (o);
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s 12345 3747\n", argv[0]);
    return (-1);
  }

  std::string s_first(argv[1]);
  std::string s_second(argv[2]);
  long long i_first  = atoll(s_first.c_str());
  long long i_second = atoll(s_second.c_str());
  BigInt bi1(s_first.c_str());
  BigInt bi2(s_second.c_str());

  std::cout << ">>>>>>> string: " << std::endl;
  std::cout << "bi1 = " << bi1 << std::endl;
  std::cout << "bi2 = " << bi2 << std::endl;
  std::cout << "bi1 + bi2 = " << bi1 + bi2 << std::endl;
  
  std::cout << ">>>>>>> int: " << std::endl;
  std::cout << "bi1 = " << i_first << std::endl;   
  std::cout << "bi2 = " << i_second << std::endl; 
  std::cout << "bi1 + bi2 = " << i_first + i_second << std::endl;

  return (0);
}
