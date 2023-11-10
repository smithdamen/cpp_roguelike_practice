#pragma once

#include <libtcod/color.hpp>

namespace symbols {
  // tiles
  constexpr auto FLOOR = '.';
  constexpr auto WALL = '#';
  constexpr auto UP_STAIR = '<';
  constexpr auto DOWN_STAIR = '>';

  // actors
  constexpr auto PLAYER = '@';
  constexpr auto TROLL = 'T';
  constexpr auto ORC = 'o';

  // items
  constexpr auto POTION = '!';
  constexpr auto SCROLL = '?';
}
