#pragma once
#include <vector>
#include <libtcod.hpp>
#include <memory>
#include <string>

#include "../types/action.hpp"
#include "../types/actor_id.hpp"
#include "../types/actor.hpp"
#include "../types/position.hpp"
#include "../types/stats.hpp"
#include "../colors.hpp"
#include "../types/item.hpp"
#include "../constants.hpp"
#include "../symbols.hpp"

struct Orc {
  ActorID id;
  Actor.name = "orc";
  Actor.ch = symbols::ORC;
  Actor.fg = colors::ORC_FG;
  Actor.stats.max_hp = monster.stats.hp = 10;
  Actor.stats.attack = 3;
  Actor.stats.xp = 35;
  Actor.ai = std::make_unique<action::BasicAI>();
  // std::vector<std::unique_ptr<Item>> inventory;
  // int confused_turns = 0; // move this to some kind of status effects class
};
