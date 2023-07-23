#include "field.h"

#include <cassert>
#include <iomanip>
#include <string>

#include "units.h"
using namespace std;

/* Battle field */

// Constructor
Field::Field(int h, int w) : units(h, w), terrains(h, w) {
  assert(h > 0 && h <= 20 && w > 0 && w <= 20);
}

// Get the height of the field
int Field::getHeight() const { return units.numRows(); }

// Get the width of the field
int Field::getWidth() const { return units.numCols(); }

// Get the terrain of a square
Terrain Field::getTerrain(int row, int col) const {
  assert(terrains.inBounds(row, col));
  return terrains[row][col];
}

Unit* Field::getUnit(int row, int col) const {
  assert(units.inBounds(row, col));
  return units[row][col];
}

// Set the terrain when initializing
void Field::setTerrain(Terrain t, int row, int col) {
  this->terrains[row][col] = t;
  if (!this->to_flood && t == ABYSS) this->to_flood = 1;
}

// Handle the flood
void Field::flood() {
  for (int i = 0; i < this->getHeight(); i++) {
    for (int j = 0; j < this->getWidth(); j++) {
      if (this->getTerrain(i, j) == WATER) {
        this->Water.enqueue(make_pair(i, j));
      }
    }
  }

  while (!Water.isEmpty()) {
    pair<int, int> water = Water.dequeue();
    this->terrains[water.first][water.second] = WATER;

    for (int i = 0; i < 9; i++) {
      int delrow = i / 3 - 1;
      int delcol = i % 3 - 1;
      pair<int, int> tmp =
          make_pair(water.first + delrow, water.second + delcol);
      if (tmp.first < 0 || tmp.first >= this->getHeight() || tmp.second < 0 ||
          tmp.second >= this->getWidth())
        continue;

      Terrain ts = this->getTerrain(tmp.first, tmp.second);
      if (ts != ABYSS) {
        continue;
      }
      Water.enqueue(tmp);
    }
  }
}

// Set the terrain when initializing
void Field::setUnit(Unit* u, int row, int col) { this->units[row][col] = u; }

int Field::checkWinner() {
  int A = 0;
  int B = 0;
  for (int i = 0; i < this->getHeight(); i++) {
    for (int j = 0; j < this->getWidth(); j++) {
      if (this->getUnit(i, j) != nullptr) {
        A += (this->getUnit(i, j)->getSide() == 1);
        B += (this->getUnit(i, j)->getSide() == 0);
      }
    }
  }

  if (A != 0 && B == 0) {
    return 1;
  } else if (A == 0 && B != 0) {
    return 0;
  } else if (A == 0 && B == 0) {
    return 2;
  }

  return -1;
};

void Field::restoreMovePts() {
  for (int i = 0; i < this->getHeight(); i++) {
    for (int j = 0; j < this->getWidth(); j++) {
      if (this->getUnit(i, j) != nullptr) {
        this->getUnit(i, j)->restore();
      }
    }
  }
}

// Handle the command line
int Field::operator()(std::vector<std::string> cmd, bool side) {
  if (cmd.size() == 0) return -1;

  int index = 2;
  Unit* un = this->getUnit(stoi(cmd[0]), stoi(cmd[1]));
  if (un == nullptr || un->getSide() != side) {
    return -1;
  }

  while (index < cmd.size()) {
    int input = stoi(cmd[index]);
    if (input > 0 && input <= 9) {
      un->move(*this, stoi(cmd[index]));  // Move func
    } else if (input == 0) {
      if ((index + 1) >= cmd.size()) break;
      int res = un->attack(*this, stoi(cmd[++index]));  // Attack func
      if (!res) break;
      if (this->checkWinner() >= 0) {
        return this->checkWinner();
      }
    } else if (input == 10) {
      if ((index + 2) >= cmd.size()) break;
      int res = un->spell(*this, stoi(cmd[index + 1]), stoi(cmd[index + 2]));
      if (!res) break;
      index += 2;
      if (this->checkWinner() >= 0) {
        return this->checkWinner();
      }
    }

    index++;
  }

  this->restoreMovePts();

  return -1;
}

// Reclaim all the units
Field::~Field() {
  for (int i = 0; i < units.numRows(); i++)
    for (int j = 0; j < units.numCols(); j++)
      if (units[i][j] != nullptr) delete units[i][j];
}

// Display the symbol for terrains
string getTerrainSymbol(Terrain t) {
  switch (t) {
    case PLAIN:
      return "  ";
    case WATER:
      return "~~";
    case MOUNTAIN:
      return "/\\";
    case FOREST:
      return "$ ";
    case ABYSS:
      return "\\/";
  }

  assert(false);
}

// Display the symbol for units
string getUnitSymbol(Unit* u) {
  switch (u->getUnitType()) {
    case FOOTMAN:
      return u->getSide() ? "FT" : "ft";
    case KNIGHT:
      return u->getSide() ? "KN" : "kn";
    case ARCHER:
      return u->getSide() ? "AR" : "ar";
    case MAGE:
      return u->getSide() ? "MG" : "mg";
  }
  assert(false);
}

// Print the horizontal line
void printHLine(ostream& os, int n) {
  os << "  ";
  for (int i = 0; i < n; i++) os << "+--";
  os << "+" << endl;
}

// Display field
ostream& operator<<(ostream& os, const Field& field) {
  int height = field.getHeight();
  int width = field.getWidth();

  // Print the x coordinates
  os << "  ";
  for (int i = 0; i < width; i++) os << ' ' << setw(2) << i;
  os << endl;

  printHLine(os, width);
  for (int i = 0; i < height; i++) {
    os << setw(2) << i;
    for (int j = 0; j < width; j++) {
      os << '|';
      if (field.getUnit(i, j) != nullptr) {
        string un = getUnitSymbol(field.getUnit(i, j));
        os << un;
        continue;
      }

      string ts = getTerrainSymbol(field.getTerrain(i, j));
      os << ts;
    }
    os << '|' << endl;
    printHLine(os, width);
  }
  os << endl;
  return os;
}
