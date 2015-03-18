#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <set>
using namespace std;

class TextQuery
{
  public:
    void read_file(ifstream &is)
    {
      store_file(is);
      bulid_map();
    }
    set<int> run_query(const string &) const;
    void print_result(const string &, set<int> &) const;
  private:
    void store_file(ifstream &is);
    void bulid_map(void);
    vector<string>		word_line;
    map< string, set<int> >	word;
};

void TextQuery::store_file(ifstream &is)
{
  string	line;
  while (getline(is, line))
    word_line.push_back(line);
}

void TextQuery::bulid_map(void)
{
  for (vector<string>::iterator iter = word_line.begin(); iter != word_line.end(); iter++)
  {
    string		w;
    istringstream	line(*iter);
    while (line >> w)
      word[w].insert(iter - word_line.begin());	/* word[w]的值就是set<int>!! */
  }
}

set<int> TextQuery::run_query(const string &s) const
{
  map< string, set<int> >::const_iterator iter = word.find(s);
  if (iter != word.end())
    return (iter->second);
  else
    return (set<int>());
}

void TextQuery::print_result(const string &s, set<int> &lno) const
{
  cout << s << " occure " << lno.size() << " times" << endl;
  for (set<int>::iterator iter = lno.begin(); iter != lno.end(); iter++)
    cout << "    (line " << *iter << ") " << word_line[*iter] << endl;
}

int main(int argc, const char **argv)
{
  TextQuery	tq;
  ifstream 	ifs;
  string	s;

  if (argc != 2)
  {
    cout << "Usage(): " << argv[0] << " filename" << endl;
    return (-1);
  }

  ifs.open(argv[1]);
  if (!ifs.good())
  {
    cout << "open file: " << argv[1] << " error" << endl;
    return (-1);
  }

  tq.read_file(ifs);
  ifs.close();
  while (true)
  {
    cout << "enter word to look for, or 'q' to quit : ";
    cin >> s;
    if (s == "q")	break;
    set<int> lno = tq.run_query(s);
    tq.print_result(s, lno);
  }

  return (0);
}
