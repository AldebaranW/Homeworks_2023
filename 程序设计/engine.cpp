#include "engine.h"

#include <queue.h>

#include <cassert>
#include <iomanip>
#include <sstream>

#include "units.h"
using namespace std;

void split(string str, vector<string>& v) {
  string tmp;
  str.push_back(' ');
  for (char c : str) {
    if (c <= 32) {
      if (tmp.size() != 0) {
        v.push_back(tmp);
      }
      tmp.clear();
      continue;
    }
    tmp.push_back(c);
  }
}

Field* loadMap(std::istream& is) {
  int M, N, NT, NU;
  string tmp_line;
  vector<string> tmp_cmd;
  getline(is, tmp_line);
  split(tmp_line, tmp_cmd);
  M = stoi(tmp_cmd[0]);
  N = stoi(tmp_cmd[1]);
  NT = stoi(tmp_cmd[2]);
  NU = stoi(tmp_cmd[3]);

  Field* f = new Field(M, N);
  for (int i = 0; i < NT; i++) {
    string str;
    vector<string> cmd;
    getline(is, str);
    split(str, cmd);
    if (cmd.size() != 3) return nullptr;

    Terrain t;
    switch (cmd[2][0]) {
      case 'W':
        t = WATER;
        break;
      case 'M':
        t = MOUNTAIN;
        break;
      case 'F':
        t = FOREST;
        break;
      case 'A':
        t = ABYSS;
        break;
    }

    f->setTerrain(t, stoi(cmd[0]), stoi(cmd[1]));
  }

  for (int i = 0; i < NU; i++) {
    string str;
    vector<string> cmd;
    getline(is, str);
    split(str, cmd);
    if (cmd.size() != 4) return nullptr;

    if (f->getTerrain(stoi(cmd[0]), stoi(cmd[1])) == MOUNTAIN |
        f->getTerrain(stoi(cmd[0]), stoi(cmd[1])) == WATER |
        f->getTerrain(stoi(cmd[0]), stoi(cmd[1])) == ABYSS) {
      continue;
    }

    if (cmd[3] == "FT") {
      Unit* u = new Footman(cmd[2] == "A", stoi(cmd[0]), stoi(cmd[1]));
      f->setUnit(u, stoi(cmd[0]), stoi(cmd[1]));
    } else if (cmd[3] == "KN") {
      Unit* u = new Knight(cmd[2] == "A", stoi(cmd[0]), stoi(cmd[1]));
      f->setUnit(u, stoi(cmd[0]), stoi(cmd[1]));
    } else if (cmd[3] == "AR") {
      Unit* u = new Archer(cmd[2] == "A", stoi(cmd[0]), stoi(cmd[1]));
      f->setUnit(u, stoi(cmd[0]), stoi(cmd[1]));
    } else if (cmd[3] == "MG") {
      Unit* u = new Mage(cmd[2] == "A", stoi(cmd[0]), stoi(cmd[1]));
      f->setUnit(u, stoi(cmd[0]), stoi(cmd[1]));
    }
  }

  if (f->to_flood) f->flood();

  return f;
}

// Main loop for playing the game
void play(Field& field, istream& is, ostream& os) {
  bool side = true;
  int numTurns = 1;
  int res = field.checkWinner();
  while (is) {
    // Print the new map
    os << field << endl;

    // Check if the game ends
    if (res == 1) {
      cout << "Winner is Player A!" << endl;
      break;
    } else if (res == 0) {
      cout << "Winner is Player B!" << endl;
      break;
    } else if (res == 2) {
      cout << "A Draw!" << endl;
      break;
    }

    string player;
    if (side)
      player = "Player A";
    else
      player = "Player B";

    os << "Turn " << numTurns << " (" << player << ")" << endl;

    string line;
    if (!getline(is, line)) break;
    stringstream ss(line);

    vector<string> cmd;
    split(line, cmd);
    res = field(cmd, side);

    side = !side;
    numTurns++;
  }
}
