#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <fstream>

std::string
ToUpper(std::string s) {
  std::string out;
  for (char c : s)
    out.push_back(toupper(c));
  return out;
}

struct Word {
  Word() {};
  Word(std::string str) : word(str) {}
  std::string word;
  int len() { return word.length(); }
};
typedef std::vector<Word*> Words;
typedef std::unordered_map<std::string, Words> WordMap;

// Things inside a class are private by default
class Library {
public:
  Library() {}
  ~Library() { for (Word* w : words_) delete w; }
  void
    Find(const std::string& s) const {
    auto it = word_map_.find(s);
    if (it != word_map_.end()) {
      for (const Word* w : it->second)
        std::cout << w->word << " ";
      std::cout << std::endl;
    }
    else
      std::cout << "No Combinations" << std::endl;
  }
  bool
    Has(Word w) const {
    auto it = word_map_.find(w.word);
    // word_map_.end() returns true if element is not found
    if (it == word_map_.end()) return false;
    else return true;
    // alternative approach
    // return word_map_.count(w.word) > 0;
  }
  void
    ComputeStats() {
    assert(counts_.empty());
    counts_.resize(18);
    for (Word* w : words_) {
      int len = w->word.size();
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
    return words_[i]->word;
  }
  void
    PatternHash(Word* w) {
    const int len = w->len();
    int num_patterns = 1 << len;
    // std::cout << num_patterns << std::endl;
    for (int i = 0;i < num_patterns;i++) {
      std::string temp = w->word;
      for (int j = 0;j < len;j++) {
        if ((i >> j) & 1) temp[j] = '-';
      }
      // std::cout << temp << std::endl;
      word_map_[temp].push_back(w);
    }
  }
  void
    Read(std::string filename) {
    std::fstream file;
    file.open(filename);
    while (file.is_open() && !file.eof()) {
      std::string line;
      getline(file, line);
      if (!line.empty()) {
        line = ToUpper(line);
        Word* w = new Word(line);
        words_.push_back(w);
        PatternHash(w);
      }
    }
    std::cout << "Successfully read " << words_.size()
      << " words from " << filename << std::endl;
  }
  void
    DebugBuckets() const {
    for (int i = 0; i < word_map_.bucket_count();i++) {
      std::cout << "[" << i << "]" << word_map_.bucket_size(i) << std::endl;
    }
  }

private:
  // Generally its a convention to keep _
  // For the Pvt members at the end
  Words words_;   // Master Vector of Words
  WordMap word_map_;    // Pattern Hash
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
  lib.Read("wordlist.txt");
  // lib.ComputeStats();
  // lib.PrintStats();
  // lib.DebugBuckets();
  lib.Find("D--");
  lib.Find("C--");
  lib.Find("D----");
  lib.Find("A----");
  lib.Find("C-----T");
  lib.Find("EN---");
  lib.Find("PO---");
}

