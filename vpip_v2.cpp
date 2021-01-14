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
  ifstream infile("log.txt");
  map<string, pair<pair<int, int>, bool> > p;
  deque<string> l;
  bool start = false;
  string line;
  while (getline(infile, line)) l.push_front(line);
  map<string, pair<pair<int, int>, bool> >::iterator it;
  while (!l.empty()) {
    if (l.front().find("joined") != string::npos || l.front().find("sit") != string::npos) {
      if (p.find(name(l.front(), 14)) == p.end()) p[name(l.front(), 14)] = make_pair(make_pair(0, 0), true);
      p[name(l.front(), 14)].second = true;
    } else if (l.front().find("quit") != string::npos || l.front().find("stand") != string::npos) p[name(l.front(), 14)].second = false;
    else if (l.front().find("approved") != string::npos) {
      if (p.find(name(l.front(), 33)) == p.end()) p[name(l.front(), 33)] = make_pair(make_pair(0, 0), true);
      p[name(l.front(), 33)].second = true;
    } else if (l.front().find("Player stacks") != string::npos) {
      set<string> orbit;
      for (it = p.begin(); it != p.end(); it++) if ((*it).second.second) (*it).second.first.second++;
      while (l.front().find("Flop") == string::npos && !l.empty()) {
        if (l.front().find("calls") != string::npos || l.front().find("raises") != string::npos) {
          if (orbit.find(name(l.front(), 3)) == orbit.end()) p[name(l.front(), 3)].first.first++;
          orbit.insert(name(l.front(), 3));
        } else if (l.front().find("approved") != string::npos) {
          if (p.find(name(l.front(), 33)) == p.end()) p[name(l.front(), 33)] = make_pair(make_pair(0, 0), true);
          p[name(l.front(), 33)].second = true;
        }
        l.pop_front();
      }
    }
    l.pop_front();
  }
  for (it = p.begin(); it != p.end(); it++) cout << (*it).first << " " << (*it).second.first.first << " " << (*it).second.first.second << " " << double((*it).second.first.first) / (*it).second.first.second << endl;
  return 0;
}
