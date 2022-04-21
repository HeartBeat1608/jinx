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
      outstream << line;
    else if (pos > 0)
      outstream << line.substr(0, pos);
  }

  return outstream.str();
}