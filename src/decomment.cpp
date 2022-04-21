#include <bits/stdc++.h>
#include <decomment.hpp>
using namespace std;

string DeComment::removeComments(string prog)
{
  string line = "";
  istringstream stream(prog);
  ostringstream outstream;

  // optimize for faster operations
  // unlink from the stdin and stdout streams
  stream.sync_with_stdio(false);
  outstream.sync_with_stdio(false);

  int pos = -1;

  while (getline(stream, line))
  {
    pos = line.find_first_of("!#");
    if (pos == line.npos)
      outstream << line << "\n";
    else if (pos > 0)
    {
      string sline = line.substr(0, pos), subline = "";
      auto itr = sline.begin();
      while (itr != sline.end())
      {
        if (*itr != ' ')
          subline += *itr;
        itr++;
      }
      if (subline.length() > 0)
        outstream << subline << "\n";
    }
  }

  return outstream.str();
}