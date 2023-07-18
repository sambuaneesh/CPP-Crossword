#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <fstream>

std::string
ToUpper(std::string s) {
  std::string out;
  for (char c : s)
    out.push_back(toupper(c));
  return out;
}

const int num_buckets = 501;

// hash function
int
bucket(std::string s) {
  assert(!s.empty());
  int out = s[0] - 'A';
  for (char c : s)
    out = ((out * 217) + c) % num_buckets;
  assert(out >= 0 && out < num_buckets);
  return out;
}

struct Word {
  Word(std::string str) : word(str) {}
  std::string word;
};
typedef std::vector<Word> Words;

// Things inside a class are private by default
class Library {
public:
  Library() {
    shelves_.resize(num_buckets);
  }
  bool
    Has(Word w) const {
    w.word = ToUpper(w.word);
    for (Word word : shelves_[bucket(w.word)])
      if (word.word == w.word)
        return true;
    return false;
  }
  void
    ComputeStats() {
    assert(counts_.empty());
    counts_.resize(18);
    for (Word w : words_) {
      int len = w.word.size();
      if (len)
        ++counts_[len];
    }
  }
  void
    PrintStats() const {
    std::cout << "Stats of the Library Data are: "
      << std::endl;
    for (int i = 1;i < counts_.size();i++) {
      std::cout << "[ " << i << " ]\t"
        << counts_[i] << std::endl;
    }
  }
  std::string
    GetWord(int i) const {
    assert(i >= 0 && i < words_.size());
    return words_[i].word;
  }
  void
    ReadFromFile(std::string filename) {
    std::fstream file;
    file.open(filename);
    while (!file.eof()) {
      std::string line;
      getline(file, line);
      if (!line.empty()) {
        line = ToUpper(line);
        words_.push_back(Word(line));
        shelves_[bucket(line)].push_back(Word(line));
      }
    }
    std::cout << "Successfully read " << words_.size()
      << " words from " << filename << std::endl;
  }
  void
    DebugBuckets() {
    for (int i = 0; i < shelves_.size();i++) {
      std::cout << "[" << i << "]" << "\t"
        << shelves_[i].size() << std::endl;
    }
  }

private:
  Words words_;
  std::vector<Words> shelves_;
  std::vector<int> counts_;
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
      if (!line.empty() && line[0] != '#') {
        line = ToUpper(line);
        lines.push_back(line);
      }
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
  // Grid grid("Main Grid");
  // grid.Print();
  // grid.Load("grid");
  // grid.Check();
  // grid.Print();
  Library lib;
  lib.ReadFromFile("wordlist.txt");
  lib.ComputeStats();
  lib.PrintStats();
  // lib.DebugBuckets();
}

