#pragma once

#include <libtcod/color.hpp>

namespace constants {
// sizes
constexpr auto CONSOLE_WIDTH = 80;
constexpr auto CONSOLE_HEIGHT = 40;
constexpr auto MAP_WIDTH = CONSOLE_WIDTH;
constexpr auto MAP_HEIGHT = (CONSOLE_HEIGHT - 6);
constexpr auto BAR_WIDTH = 20;
constexpr auto BAR_HEIGHT = 1;
constexpr auto LOG_WIDTH = (CONSOLE_WIDTH - BAR_WIDTH);
constexpr auto LOG_HEIGHT = (CONSOLE_HEIGHT - MAP_HEIGHT);

// positions
constexpr auto LOG_X = (0 + BAR_WIDTH);
constexpr auto LOG_Y = (MAP_HEIGHT + 1);
constexpr auto HP_BAR_X = 0;
constexpr auto HP_BAR_Y = (MAP_HEIGHT + 1);
constexpr auto MP_BAR_X = 0;
constexpr auto MP_BAR_Y = (1 + (HP_BAR_Y + BAR_HEIGHT));
constexpr auto XP_BAR_X = 0;
constexpr auto XP_BAR_Y = (1 + (MP_BAR_Y + BAR_HEIGHT));

// colors
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

// menu colors
constexpr auto TEXT_COLOR_DEFAULT = WHITE;
constexpr auto MENU_COLOR_DEFAULT = GRAY;
constexpr auto MENU_COLOR_HIGHLIGHT = YELLOW;

// map colors
constexpr auto FLOOR_FG = WHITE;
constexpr auto FLOOR_BG = BLACK;
constexpr auto WALL_FG = WHITE;
constexpr auto WALL_BG = BLACK;

// item colors
constexpr auto HEALING_POTION = GREEN;
constexpr auto SCROLL_CONFUSION = LIGHT_MAGENTA;
constexpr auto SCROLL_FIREBALL = RED;
constexpr auto SCROLL_LIGHTNING = BLUE;

// actor colors
constexpr auto PLAYER_FG = WHITE;

// https://paletton.com/#uid=1000u0kllllaFw0g0qFqFg0w0aF
constexpr auto HP_BAR_BACK = RED;
constexpr auto HP_BAR_FILL = LIGHT_RED;
constexpr auto MP_BAR_BACK = BLUE;
constexpr auto MP_BAR_FILL = LIGHT_BLUE;
// https://paletton.com/#uid=14H0u0knjpZdTAzj6tnqPlGv4gS
constexpr auto XP_BAR_BACK = MAGENTA;
constexpr auto XP_BAR_FILL = LIGHT_MAGENTA;

// tiles
constexpr auto PLAYER = '@';
}  // namespace constants
