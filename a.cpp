#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <fstream>

// Things inside a class are private by default
class Library {
public:
  void
    ComputeStats() {
    assert(counts.empty());
    counts.resize(18);
    for (std::string str : words) {
      int len = str.size();
      if (len)
        ++counts[len];
    }
  }
  void
    PrintStats() const {
    std::cout << "Stats of the Library Data are: "
      << std::endl;
    for (int i = 1;i < counts.size();i++) {
      std::cout << "[ " << i << " ]\t"
        << counts[i] << std::endl;
    }
  }
  std::string
    GetWord(int i) const {
    assert(i >= 0 && i < words.size());
    return words[i];
  }
  void
    ReadFromFile(std::string filename) {
    std::fstream file;
    file.open(filename);
    while (!file.eof()) {
      std::string line;
      getline(file, line);
      if (!line.empty())
        words.push_back(line);
    }
    std::cout << "Successfully read " << words.size()
      << " words from " << filename << std::endl;
  }

private:
  std::vector<std::string> words;
  std::vector<int> counts;
};

// Things inside a struct are public by default
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
  Library lib;
  lib.ReadFromFile("wordlist.txt");
  lib.ComputeStats();
  lib.PrintStats();
}

