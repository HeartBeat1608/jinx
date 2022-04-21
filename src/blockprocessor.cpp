#include <blockprocessor.hpp>
#include <logger.hpp>
#include <keywords.hpp>

void JxBlockProcessor::findBlocks(string prog)
{
  int b_start_pos = -1;
  stringstream ss(prog), cblock;
  string line;
  int lno = 0;
  while (getline(ss, line))
  {
    lno++;
    const string newline = "\n";
    int begin_pos = line.find(JX_BLOCK_BEGIN);
    int end_pos = line.find(JX_BLOCK_END);

    // if 'begin' keyword is found
    if (begin_pos != line.npos)
    {
      if (b_start_pos != -1)
        jlog << "New block defined before ending previous block (@ line " << lno << ")" << endl, exit(1);
      // set begin position for block
      b_start_pos = lno;
      cblock << line << newline;
      continue;
    }

    // if 'end' keyword is found
    if (end_pos != line.npos)
    {
      if (b_start_pos == -1)
        jlog << "Block ending found without 'begin' (@ line " << lno << ")" << endl, exit(1);

      // get block from program and add to array
      cblock << line << newline;
      b_start_pos = -1;
      numBlocks++;
      blocks.push_back(cblock.str());

      // prepare for next block
      cblock.str(string());
      continue;
    }

    cblock << line << newline;
  }

  if (b_start_pos != -1)
  {
    // some block was incomplete
    jlog << "Unclosed block found (@ line " << lno << ")" << endl;
    exit(1);
  }
}

// void JxBlockProcessor::processBlock(string block)
// {
//   // each block contains begin, end and body.
//   stringstream ss(block);
//   string block_name = "", line;
//   Tokenizer tokenizer;

//   while (getline(ss, line))
//   {
//     jlog << line << endl;
//     int pos;
//     if ((pos = line.find(JX_BLOCK_BEGIN)) != line.npos)
//     {
//       // get the name of the block from the begin line
//       string sub = line.substr(pos + JX_BLOCK_BEGIN.length());
//       auto itr = sub.begin();
//       while (itr != sub.end())
//       {
//         if (!(*itr == ' ' && block_name != ""))
//         {
//           block_name += *itr;
//         }
//         itr++;
//       }

//       if (block_name == "")
//         jlog << "No block name found" << endl, exit(0);
//     }
//     else if ((pos = line.find(JX_BLOCK_END)) != line.npos)
//     {
//       string sub = line.substr(pos + JX_BLOCK_END.length());
//       auto itr = sub.begin();
//       string bname = "";
//       while (itr != sub.end())
//       {
//         if (!(*itr == ' ' && bname != ""))
//         {
//           bname += *itr;
//         }
//         itr++;
//       }

//       if (block_name != bname)
//         jlog << "mismatch block begin and end" << endl, exit(0);
//     }
//     else
//     {
//       // process the line
//       auto tokens = tokenizer.getTokens(line, *this);
//       for (auto x : tokens)
//         cout << x;
//     }
//   }
// }

string JxBlockProcessor::getBlock(int i)
{
  return blocks.at(i);
}

int JxBlockProcessor::getTotalBlocks() { return numBlocks; }