#pragma once
#include <vector>

#include "item.hpp"

struct Stats {
  int max_hp;
  int hp;
  int max_mp;
  int mp;
  int attack;
  int defense;
  int level = 1;
  int xp = 0;
  std::vector<std::unique_ptr<Item>> inventory;
  int confused_turns = 0; // move this to some kind of status effects class
};
