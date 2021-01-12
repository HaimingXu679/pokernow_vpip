#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <deque>
#include <utility>
#include <set>
using namespace std;

string name(string line, int start) {
  string t = "";
  for (int i = start; i < line.size() && line[i] != '@'; i++) t += line[i];
  return t.substr(0, t.size() - 1);
}

int main() {
  ifstream infile("your log here");
  map<string, pair<pair<int, int>, bool> > p;
  deque<string> l;
  bool start = false;
  string line;
  while (getline(infile, line)) l.push_front(line);
  while (!l.empty()) {
    if (l.front().find("joined") != string::npos) {
      if (p.find(name(l.front(), 14)) == p.end()) p[name(l.front(), 14)] = make_pair(make_pair(0, 0), true);
      p[name(l.front(), 14)].second = true;
    } else if (l.front().find("quit") != string::npos) p[name(l.front(), 14)].second = false;
    else if (l.front().find("Player stacks") != string::npos) {
      set<string> orbit;
      for (auto a : p) if (p[a.first].second) p[a.first].first.second++;
      while (l.front().find("Flop") == string::npos && !l.empty()) {
        if (l.front().find("calls") != string::npos || l.front().find("raises") != string::npos) {
          if (orbit.find(name(l.front(), 3)) == orbit.end()) p[name(l.front(), 3)].first.first++;
          orbit.insert(name(l.front(), 3));
        }
        l.pop_front();
      }
    }
    l.pop_front();
  }
  for (auto a : p) cout << a.first << " " << a.second.first.first << " " << a.second.first.second << " " << double(a.second.first.first) / a.second.first.second << endl;
  return 0;
}
