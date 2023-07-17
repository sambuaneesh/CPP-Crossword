#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

struct
  Grid {
  std::vector<std::string> lines;
  int
    Rows() {
    return lines.size();
  }
  void
    Load() {
    lines.push_back("DOG....");
    lines.push_back("---....");
    lines.push_back("----...");
    lines.push_back("-------");
    lines.push_back("...----");
    lines.push_back("....---");
    lines.push_back("....CAT");
  }
  void
    Check() {
    for (std::string s : lines) assert(s.size() == Rows());
  }
  void
    Print() {
    std::cout << "Number of Rows: " << Rows() << std::endl;
    for (std::string str : lines) {
      for (char c : str)
        std::cout << '|' << c;
      std::cout << '|' << std::endl;
    }
    std::cout << std::endl;
  }
};


int
main() {
  Grid grid;
  grid.Print();
  grid.Load();
  grid.Check();
  grid.Print();
}

