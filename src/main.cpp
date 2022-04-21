#include <decomment.hpp>
#include <logger.hpp>
#include <blockprocessor.hpp>
#include <keywords.hpp>
using namespace std;

vector<string> processTokens(string line, JxBlockProcessor &processor)
{
  vector<string> tokens;
  stringstream ss(line);
  string w, kw, t, v;

  while (!ss.eof())
  {
    ss >> w;
    int pos;
    if ((pos = w.find(JX_DTYPE_NUMBER)) != w.npos)
    {
      ss >> t;
      if (t == "")
        jlog << "No variable name provided", exit(1);
      ss >> w;
      if (w != "=")
        jlog << "Variable assignmet must be done using '=' operator", exit(1);
      ss >> v;
      if (v == "")
        jlog << "Variable not assigned a value of type " << JX_DTYPE_NUMBER, exit(1);

      SymbolBody sbody;
      sbody.type = JX_DTYPE_NUMBER;
      sbody.value = v;

      processor.symbolTable.insert({t, sbody});
    }
    else if ((pos = w.find(JX_PRINT)) != w.npos)
    {
      // print command, prints to cout
      while (!ss.eof())
      {
        ss >> t;
        auto tpos = processor.symbolTable.find(t);
        if (tpos == processor.symbolTable.end())
        {
          jlog << "Undefined symbol " << t;
          exit(1);
        }
        cout << tpos->second.value << JX_SEP;
      }
      cout << JX_NL;
    }
  }
  return tokens;
}

void processBlock(string block, JxBlockProcessor &processor)
{
  stringstream ss(block);
  string block_name = "", line;

  while (getline(ss, line))
  {
    int pos;
    if ((pos = line.find(JX_BLOCK_BEGIN)) != line.npos)
    {
      // get the name of the block from the begin line
      string sub = line.substr(pos + JX_BLOCK_BEGIN.length());
      auto itr = sub.begin();
      while (itr != sub.end())
      {
        if (!(*itr == ' ' && block_name != ""))
        {
          block_name += *itr;
        }
        itr++;
      }

      if (block_name == "")
        jlog << "No block name found" << endl, exit(0);
    }
    else if ((pos = line.find(JX_BLOCK_END)) != line.npos)
    {
      string sub = line.substr(pos + JX_BLOCK_END.length());
      auto itr = sub.begin();
      string bname = "";
      while (itr != sub.end())
      {
        if (!(*itr == ' ' && bname != ""))
        {
          bname += *itr;
        }
        itr++;
      }

      if (block_name != bname)
        jlog << "mismatch block begin and end" << endl, exit(0);
    }
    else
    {
      // process the line
      auto tokens = processTokens(line, processor);
      for (auto x : tokens)
        cout << x;
    }
  }
}

string readProgram(const string &filepath)
{
  auto ss = ostringstream();
  ifstream input_stream(filepath);

  if (!input_stream.is_open())
  {
    jlog << "jxc could not find the source file " << filepath << "\n";
    jlog << "Fix: Make sure that the file is in the currect path and is accessible by the jxc compiler" << endl;
    exit(1);
  }

  ss << input_stream.rdbuf();
  return ss.str();
}

void printSymbolTable(JxBlockProcessor &proc)
{
  auto itr = proc.symbolTable.begin();
  while (itr != proc.symbolTable.end())
  {
    cout << itr->first << " | " << itr->second.type << " | " << itr->second.value << JX_NL;
    itr++;
  }
}

int main(int argc, char const *argv[])
{
  if (argc < 2)
  {
    cout << "USAGE:" << JX_NL;
    cout << "jxc <path-to-source-file>" << endl;
    return 1;
  }

  const string finPath = argv[1];
  string program = readProgram(finPath);

  DeComment dcmt;
  program = dcmt.removeComments(program);

  // parse the blocks
  JxBlockProcessor block_processor;
  block_processor.findBlocks(program);

  for (int i = 0; i < block_processor.getTotalBlocks(); i++)
  {
    processBlock(block_processor.getBlock(i), block_processor);
  }

  return 0;
}
