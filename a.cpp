#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <fstream>

struct Grid {
  std::vector<std::string> lines;
  std::string name;
  Grid
  (std::string n = "UNTITLED") {
    name = n;
  }
  int Rows() const { return lines.size(); }
  void
    Load(std::string filename) {
    std::fstream file;
    file.open(filename);
    while (!file.eof()) {
      std::string line;
      getline(file, line);
      if (!line.empty() && line[0] != '#')
        lines.push_back(line);
    }
  }
  void
    Check() const {
    for (std::string s : lines) assert(s.size() == Rows());
  }
  void
    Print() const {
    std::cout << "# " << name << std::endl;
    std::cout << "Number of Rows: " << Rows() << std::endl;
    for (std::string str : lines) {
      std::cout << "  ";
      for (char c : str)
        std::cout << '|' << c;
      std::cout << '|' << std::endl;
    }
    std::cout << std::endl;
  }
};


int
main() {
  Grid grid("Main Grid");
  grid.Print();
  grid.Load("grid");
  grid.Check();
  grid.Print();
}

