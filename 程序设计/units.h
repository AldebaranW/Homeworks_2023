#ifndef UNITS_H_INCLUDED
#define UNITS_H_INCLUDED

#include <queue.h>

#include <string>

#include "field.h"

/* Type of Units */
enum UnitType { FOOTMAN, KNIGHT, ARCHER, MAGE };

/* Class for units */
class Unit {
 public:
  Unit(UnitType u, bool sd, int rw, int cl)
      : type(u), side(sd), row(rw), col(cl) {}

  UnitType getUnitType();
  bool getSide();
  int getMovePoint();

  void restore();

  void move(Field& field, int move);
  virtual bool attack(Field& field, int obj) = 0;
  virtual bool spell(Field& field, int ori, int type) { return 0; };

 protected:
  UnitType type;
  bool side;
  int movept = 0;
  int max_movept = 0;
  int attack_dist = 0;

  int row;
  int col;
};

class Footman : public Unit {
 public:
  Footman(bool sd, int rw, int cl);

  virtual bool attack(Field& field, int obj);
};

class Knight : public Unit {
 public:
  Knight(bool sd, int rw, int cl);

  virtual bool attack(Field& field, int obj);
};

class Archer : public Unit {
 public:
  Archer(bool sd, int rw, int cl);

  virtual bool attack(Field& field, int obj);
};

class Mage : public Unit {
 public:
  Mage(bool sd, int rw, int cl);

  virtual bool attack(Field& field, int obj);
  bool spell(Field& field, int ori, int type);

 protected:
  void fireball(Field& field, int ori);
  void earthquake(Field& field, int ori);
  void burn(Field& field, int row, int col);
};

#endif  // UNITS_H_INCLUDED
