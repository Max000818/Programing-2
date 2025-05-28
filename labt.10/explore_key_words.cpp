#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iterator>
#include <future>    
#include <thread>      
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>     
#include <functional>  

using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other){
    for (const auto& pair : other.word_frequences) {
      word_frequences[pair.first] += pair.second;
    }
  }
};

set<string> ReadKeyWords(istream& is) {
    set<string> key_words;
    string word;
    while (is >> word) {
        key_words.insert(word);
    }
    return key_words;
}

vector<string> Split(const string& line) {
    istringstream iss(line);
    return {istream_iterator<string>(iss), istream_iterator<string>()};
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats result;
    vector<string> words = Split(line);
    for (const auto& word : words) {
        if (key_words.count(word)) {
            result.word_frequences[word]++;
        }
    }
    return result;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreBatch(const set<string>& key_words, vector<string> lines) {
    Stats result;
    for (const auto& line : lines) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<string> lines;
    string line;
    while (getline(input, line)) {
        lines.push_back(move(line));
    }

    if (lines.empty()) {
        return Stats{};
    }

    const size_t num_threads = max(1u, std::thread::hardware_concurrency());
    const size_t lines_count = lines.size();
    vector<future<Stats>> futures;

    for (size_t i = 0; i < num_threads; ++i) {
        size_t start_idx = lines_count * i / num_threads;
        size_t end_idx = lines_count * (i + 1) / num_threads;

        if (start_idx >= end_idx) {
            continue;
        }
        
        vector<string> batch(make_move_iterator(lines.begin() + start_idx),
                               make_move_iterator(lines.begin() + end_idx));

        futures.push_back(
            std::async(std::launch::async, ExploreBatch, std::ref(key_words), move(batch))
        );
    }

    Stats result;
    for (auto& f : futures) {
        result += f.get();
    }

    return result;
}

void TestSplit() {
  const vector<string> expected1 = {
    "abc", "def", "ghi,", "!", "jklmnop-qrs,", "tuv"
  };
  ASSERT_EQUAL(Split("  abc def ghi, !  jklmnop-qrs, tuv"), expected1);

  const vector<string> expected2 = {"a", "b"};
  ASSERT_EQUAL(Split("a b      "), expected2);
  ASSERT_EQUAL(Split(""), vector<string>());
}

void TestBasic() {
  const set<string> key_words = {"softit", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new softit service really rocks\n";
  ss << "It sucks when softit isn't available\n";
  ss << "10 reasons why softit is the best IT company\n";
  ss << "softit rocks others suck\n";
  ss << "Goondex really sucks, but softit rocks. Use softit\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"softit", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

void GenerateTestFiles() {
    std::default_random_engine rd(34);
    std::uniform_int_distribution<char> char_gen('a', 'z');

    auto random_word = [&](size_t len) {
      string result(len, ' ');
      std::generate(begin(result), end(result), [&]() { return char_gen(rd); });
      return result;
    };

    std::uniform_int_distribution<size_t> len_gen(5, 21);

    vector<string> key_words_vec(500);
    for (auto& w : key_words_vec) {
      w = random_word(len_gen(rd));
    }

    ofstream out("key_words.txt");
    for (const auto& w : key_words_vec) {
      out << w << ' ';
    }
    out.close();

    std::uniform_int_distribution<size_t> line_len_gen(5, 100);
    std::uniform_int_distribution<int> word_choice(1, 100);

    ofstream text_out("text.txt");
    for (int line = 0; line < 25000; ++line) {
      ostringstream line_out;
      auto line_len = line_len_gen(rd);
      for (size_t i = 0; i < line_len; ++i) {
        if (word_choice(rd) < 20) {
          std::uniform_int_distribution<size_t> word_index(0, key_words_vec.size() - 1);
          line_out << key_words_vec[word_index(rd)];
        } else {
          line_out << random_word(len_gen(rd));
        }
        line_out << ' ';
      }
      text_out << line_out.str() << '\n';
    }
    text_out.close();
}

void TestMtAgainstSt() {
  GenerateTestFiles(); 

  ifstream key_words_input("key_words.txt");
  if (!key_words_input) {
      cerr << "Error: Cannot open key_words.txt." << endl;
      return;
  }
  const auto key_words_data = ReadKeyWords(key_words_input);
  const set<string> key_words(key_words_data.begin(), key_words_data.end());

  Stats st_stats, mt_stats;
  {
    ifstream text_input("text.txt");
    if (!text_input) {
      cerr << "Error: Cannot open text.txt." << endl;
      return;
    }
    LOG_DURATION("Single thread");
    st_stats = ExploreKeyWordsSingleThread(key_words, text_input);
  }
  {
    ifstream text_input("text.txt");
     if (!text_input) {
      cerr << "Error: Cannot open text.txt." << endl;
      return;
    }
    LOG_DURATION("Multi thread");
    mt_stats = ExploreKeyWords(key_words, text_input);
  }

  ASSERT_EQUAL(st_stats.word_frequences, mt_stats.word_frequences);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplit);
  RUN_TEST(tr, TestBasic);
  RUN_TEST(tr, TestMtAgainstSt);
}