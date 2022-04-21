#include <bits/stdc++.h>
using namespace std;

struct SymbolBody
{
  string type = "number";
  string value;
};

class JxBlockProcessor
{
protected:
  int numBlocks = 0;
  vector<string> blocks;
  vector<string> errors;

public:
  unordered_map<string, SymbolBody> symbolTable;

  void findBlocks(string prog);
  // void processBlock(string block);
  int getTotalBlocks();
  string getBlock(int i);
};