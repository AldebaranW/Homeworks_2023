#include "units.h"

#include <cassert>

#include "field.h"
using namespace std;

/* Implementation of Base Class Unit */

// Get the type of the unit
UnitType Unit::getUnitType() { return this->type; }

// Get the side of the unit
bool Unit::getSide() { return this->side; }

// Get the type of the unit
int Unit::getMovePoint() { return this->movept; }

// Restore the move points
void Unit::restore() { this->movept = this->max_movept; }

// Move Function
void Unit::move(Field& field, int moves) {
  int ori = moves - 1;
  int delRow = ori / 3 - 1;
  int delCol = ori % 3 - 1;

  if (this->row + delRow < 0 || this->row + delRow >= field.getHeight() ||
      this->col + delCol < 0 || this->col + delCol >= field.getWidth()) {
    return;
  }

  if (field.getUnit(this->row + delRow, this->col + delCol) != nullptr) {
    return;
  }

  Terrain t = field.getTerrain(this->row + delRow, this->col + delCol);
  int delPt = 0;
  switch (t) {
    case PLAIN:
      delPt = 1;
      break;
    case FOREST:
      delPt = 2;
      break;

    default:
      delPt = 999;
      break;
  }

  if (delPt > this->movept) {
    return;
  }

  this->movept -= delPt;
  field.setUnit(nullptr, this->row, this->col);
  this->row += delRow;
  this->col += delCol;
  field.setUnit(this, this->row, this->col);
}

// The default implementation of attack function
bool Unit::attack(Field& field, int obj) {
  int ori = obj - 1;
  int delRow = ori / 3 - 1;
  int delCol = ori % 3 - 1;

  if (this->row + delRow * attack_dist < 0 ||
      this->row + delRow * attack_dist >= field.getHeight() ||
      this->col + delCol * attack_dist < 0 ||
      this->col + delCol * attack_dist >= field.getWidth()) {
    return 1;
  }

  if (field.getUnit(this->row + delRow * attack_dist,
                    this->col + delCol * attack_dist) == nullptr) {
    return 1;
  }

  for (int i = 1; i < this->attack_dist; i++) {
    int valRow = delRow * i;
    int valCol = delCol * i;
    Terrain t = field.getTerrain(this->row + valRow, this->col + valCol);
    if (t == MOUNTAIN) {
      return 1;
    }
  }

  field.setUnit(nullptr, this->row + delRow * this->attack_dist,
                this->col + delCol * this->attack_dist);
  return 1;
}

Footman::Footman(bool sd, int rw, int cl) : Unit(FOOTMAN, sd, rw, cl) {
  this->movept = 4;
  this->max_movept = 4;
  this->attack_dist = 1;
}
bool Footman::attack(Field& field, int obj) { return Unit::attack(field, obj); }

Knight::Knight(bool sd, int rw, int cl) : Unit(KNIGHT, sd, rw, cl) {
  this->movept = 5;
  this->max_movept = 5;
  this->attack_dist = 1;
}
bool Knight::attack(Field& field, int obj) { return Unit::attack(field, obj); }

Archer::Archer(bool sd, int rw, int cl) : Unit(ARCHER, sd, rw, cl) {
  this->movept = 3;
  this->max_movept = 3;
  this->attack_dist = 2;
}
bool Archer::attack(Field& field, int obj) { return Unit::attack(field, obj); }

Mage::Mage(bool sd, int rw, int cl) : Unit(MAGE, sd, rw, cl) {
  this->movept = 2;
  this->max_movept = 2;
  this->attack_dist = 0;
}
bool Mage::attack(Field& field, int obj) { return 0; }
bool Mage::spell(Field& field, int ori, int type) {
  switch (type) {
    case 1: {
      this->fireball(field, ori);
      break;
    }
    case 2: {
      this->earthquake(field, ori);
      break;
    }

    default:
      break;
  }
  return 1;
}

void Mage::fireball(Field& field, int ori) {
  ori -= 1;
  int delRow = ori / 3 - 1;
  int delCol = ori % 3 - 1;

  int fireball_row = this->row;
  int fireball_col = this->col;
  while (true) {
    fireball_row += delRow;
    fireball_col += delCol;

    if (fireball_row < 0 || fireball_row >= field.getHeight() ||
        fireball_col < 0 || fireball_col >= field.getWidth())
      break;

    Terrain t = field.getTerrain(fireball_row, fireball_col);
    Unit* un = field.getUnit(fireball_row, fireball_col);

    if (t == MOUNTAIN) break;
    if (un != nullptr) {
      field.setUnit(nullptr, fireball_row, fireball_col);
      break;
    }

    if (t == FOREST) {
      this->burn(field, fireball_row, fireball_col);
      break;
    }
  }
}

void Mage::earthquake(Field& field, int ori) {
  ori -= 1;
  int delRow = ori / 3 - 1;
  int delCol = ori % 3 - 1;
  delRow *= 3;
  delCol *= 3;

  for (int i = 0; i < 5; i++) {
    int delrow = (i / 2 == 0) ? ((i == 0) ? -1 : 1) : 0;
    int delcol = (i / 2 == 1) ? ((i == 2) ? -1 : 1) : 0;
    pair<int, int> tmp =
        make_pair(this->row + delRow + delrow, this->col + delCol + delcol);

    if (tmp.first < 0 || tmp.first >= field.getHeight() || tmp.second < 0 ||
        tmp.second >= field.getWidth())
      continue;

    Terrain ts = field.getTerrain(tmp.first, tmp.second);
    switch (ts) {
      case PLAIN ... FOREST:
        field.setTerrain(ABYSS, tmp.first, tmp.second);
        break;
      case MOUNTAIN:
        field.setTerrain(PLAIN, tmp.first, tmp.second);
        break;
    }

    field.setUnit(nullptr, tmp.first, tmp.second);
  }

  field.flood();
}

void Mage::burn(Field& field, int row, int col) {
  Queue<pair<int, int>> burned;
  burned.enqueue(make_pair(row, col));

  while (!burned.isEmpty()) {
    pair<int, int> burn = burned.dequeue();
    field.setTerrain(PLAIN, burn.first, burn.second);
    Unit* tmp_un = field.getUnit(burn.first, burn.second);
    if (tmp_un != nullptr) field.setUnit(nullptr, burn.first, burn.second);

    for (int i = 0; i < 9; i++) {
      int delrow = i / 3 - 1;
      int delcol = i % 3 - 1;
      pair<int, int> tmp = make_pair(burn.first + delrow, burn.second + delcol);
      if (tmp.first < 0 || tmp.first >= field.getHeight() || tmp.second < 0 ||
          tmp.second >= field.getWidth())
        continue;

      Terrain ts = field.getTerrain(tmp.first, tmp.second);
      if (ts != FOREST) continue;

      burned.enqueue(tmp);
    }
  }
}
