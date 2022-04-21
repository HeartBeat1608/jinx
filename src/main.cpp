#include <decomment.hpp>
#include <logger.hpp>
using namespace std;

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

int main(int argc, char const *argv[])
{
  if (argc < 2)
  {
    cout << "USAGE:" << endl;
    cout << "jxc <path-to-source-file>" << endl;
    return 1;
  }

  const string finPath = argv[1];
  string program = readProgram(finPath);

  jlog << "Source Read Complete\n";
  cout << program << endl;

  return 0;
}
