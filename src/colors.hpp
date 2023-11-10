#pragma once

#include <libtcod/color.hpp>

namespace colors {
  // color theme
  constexpr auto BLACK = tcod::ColorRGB{46, 52, 64};
  constexpr auto GRAY = tcod::ColorRGB{59, 66, 82};
  constexpr auto RED = tcod::ColorRGB{191, 97, 106};
  constexpr auto LIGHT_RED = tcod::ColorRGB{208, 135, 112};
  constexpr auto GREEN = tcod::ColorRGB{163, 190, 140};
  constexpr auto LIGHT_GREEN = tcod::ColorRGB{120, 200, 60};
  constexpr auto YELLOW = tcod::ColorRGB{235, 203, 139};
  constexpr auto LIGHT_YELLOW = tcod::ColorRGB{230, 190, 80};
  constexpr auto BLUE = tcod::ColorRGB{94, 129, 172};
  constexpr auto LIGHT_BLUE = tcod::ColorRGB{129, 161, 193};
  constexpr auto MAGENTA = tcod::ColorRGB{160, 100, 170};
  constexpr auto LIGHT_MAGENTA = tcod::ColorRGB{180, 142, 173};
  constexpr auto CYAN = tcod::ColorRGB{143, 188, 187};
  constexpr auto LIGHT_CYAN = tcod::ColorRGB{136, 192, 208};
  constexpr auto LIGHT_GRAY = tcod::ColorRGB{216, 222, 233};
  constexpr auto WHITE = tcod::ColorRGB{236, 239, 244};

  // console colors
  constexpr auto CONSOLE_FOREGROUND = WHITE;
  constexpr auto CONSOLE_BACKGROUND = BLACK;

  // interface colors
  constexpr auto TEXT_COLOR_DEFAULT = WHITE;
  constexpr auto MENU_COLOR_DEFAULT = WHITE;
  constexpr auto MENU_COLOR_HIGHLIGHT = YELLOW;
  constexpr auto CURSOR_FG = WHITE;
  constexpr auto CURSOR_BG = BLACK;
  constexpr auto HP_BAR_BACK = RED;
  constexpr auto HP_BAR_FILL = LIGHT_RED;
  constexpr auto MP_BAR_BACK = BLUE;
  constexpr auto MP_BAR_FILL = LIGHT_BLUE;
  constexpr auto XP_BAR_BACK = MAGENTA;
  constexpr auto XP_BAR_FILL = LIGHT_MAGENTA;

  // map colors
  constexpr auto FLOOR_FG = WHITE;
  constexpr auto FLOOR_BG = BLACK;
  constexpr auto WALL_FG = WHITE;
  constexpr auto WALL_BG = BLACK;

  // actor colors
  constexpr auto PLAYER_FG = WHITE;
  constexpr auto TROLL_FG = LIGHT_GREEN;
  constexpr auto ORC_FG = GREEN;

  // item colors
  constexpr auto HEALING_POTION = GREEN;
  constexpr auto SCROLL_CONFUSION = LIGHT_MAGENTA;
  constexpr auto SCROLL_FIREBALL = RED;
  constexpr auto SCROLL_LIGHTNING = BLUE;
}
