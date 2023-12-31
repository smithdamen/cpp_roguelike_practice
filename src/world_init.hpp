#pragma once
#include <fmt/core.h>

#include "constants.hpp"
#include "items/scroll_confusion.hpp"
#include "items/scroll_fireball.hpp"
#include "items/scroll_lightning.hpp"
#include "procgen/caves.hpp"
#include "types/actor.hpp"
#include "types/world.hpp"

inline auto new_world() -> std::unique_ptr<World> {
  auto world = std::make_unique<World>();
  world->rng = std::mt19937(std::random_device{}());
  world->log.append(
      "Welcome to introsp3ctive's roguelike!\nPrepare to perish in the world of bugs.", constants::RED);

  // create player actor
  // TODO: pull this information out of this file into separate class
  auto& player = world->actors.emplace(ActorID{0}, Actor{}).first->second;
  world->active_actors.emplace(ActorID{0});
  player.name = "player";
  player.ch = constants::PLAYER;
  player.fg = constants::PLAYER_FG;
  player.stats.max_hp = player.stats.hp = 30;
  player.stats.max_mp = player.stats.mp = 10;
  player.stats.attack = 5;
  player.stats.defense = 2;

#ifndef NDEBUG
  player.stats.inventory.emplace_back(std::make_unique<LightningScroll>());
  player.stats.inventory.emplace_back(std::make_unique<FireballScroll>());
  player.stats.inventory.emplace_back(std::make_unique<ConfusionScroll>());
#endif  // NDEBUG

  // player.stats.inventory.emplace_back(Item{"scroll of lightning bolt", '#', tcod::ColorRGB{TCODColor::lightYellow}});
  // player.stats.inventory.emplace_back(Item{"scroll of fireball", '#', tcod::ColorRGB{TCODColor::lightYellow}});
  // player.stats.inventory.emplace_back(Item{"scroll of confusion", '#', tcod::ColorRGB{TCODColor::lightYellow}});

  world->schedule.emplace_back(ActorID{0});

  auto& map = procgen::generate_level(*world);
  activate_map(*world, map);
  player.pos = find_fixture_by_name(map, "up stairs").value();
  return world;
}
