#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <grid.h>
#include <queue.h>

#include <ostream>

/* Terrains */
enum Terrain { PLAIN, FOREST, WATER, MOUNTAIN, ABYSS };

// Forward declaration of the class of units
class Unit;

/* Battle field */
class Field {
 public:
  // Constructor
  Field(int h, int w);

  // Get the height and width of the field
  int getHeight() const;
  int getWidth() const;

  // Get the terrain
  Terrain getTerrain(int row, int col) const;
  Unit* getUnit(int row, int col) const;

  // Set the terrain
  void setTerrain(Terrain t, int row, int col);
  // Set the Unit
  void setUnit(Unit* u, int row, int col);

  // Handle the flood
  void flood();

  // Handle the command
  int operator()(std::vector<std::string> cmd, bool side);

  // Restore the move points of the units
  void restoreMovePts();

  // Check whether the game ends
  int checkWinner();

  bool to_flood = 0;

  // Destructor
  ~Field();

 private:
  // Store the units
  Grid<Unit*> units;
  // Store the terrain
  Grid<Terrain> terrains;

  // Store the water coordinate to flood
  Queue<std::pair<int, int>> Water;
};

// Display the field on the out stream os
std::ostream& operator<<(std::ostream& os, const Field& field);

#endif  // FIELD_H_INCLUDED
