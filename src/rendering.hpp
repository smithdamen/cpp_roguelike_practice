#pragma once

#include <SDL.h>
#include <fmt/core.h>
#include <fmt/format.h>

#include "constants.hpp"
#include "globals.hpp"
#include "world_logic.hpp"
#include "xp.hpp"

inline void render_map(tcod::Console& console, const Map& map, bool show_all = false) {
  for (int y{0}; y < map.get_height(); ++y) {
    for (int x{0}; x < map.get_width(); ++x) {
      if (!console.in_bounds({x, y})) continue;
      if (!show_all && !map.explored.at({x, y})) continue;
      console.at({x, y}) = map.tiles.at({x, y}) == Tiles::floor
                               ? TCOD_ConsoleTile{'.', constants::FLOOR_FG, constants::FLOOR_BG}
                               : TCOD_ConsoleTile{'#', constants::WALL_FG, constants::WALL_BG};
      if (!map.visible.at({x, y})) {
        console.at({x, y}).fg.r /= 2;
        console.at({x, y}).fg.g /= 2;
        console.at({x, y}).fg.b /= 2;
        console.at({x, y}).bg.r /= 2;
        console.at({x, y}).bg.g /= 2;
        console.at({x, y}).bg.b /= 2;
      }
    }
  }
}
inline void render_map(tcod::Console& console, const World& world) {
  const auto& map = world.active_map();
  render_map(console, map);
  const auto can_draw = [&](Position map_pos) -> bool {
    if (!map.visible.in_bounds(map_pos)) return false;
    if (!map.visible.at(map_pos)) return false;
    if (!console.in_bounds(map_pos)) return false;
    return true;
  };
  for (const auto& [fixture_pos, fixture] : map.fixtures) {
    if (!can_draw(fixture_pos)) continue;
    console.at(fixture_pos).ch = fixture.ch;
    console.at(fixture_pos).fg = fixture.fg;
  }
  for (const auto& [item_pos, item] : map.items) {
    if (!can_draw(item_pos)) continue;
    const auto& [item_ch, item_fg] = item->get_graphic();
    console.at(item_pos).ch = item_ch;
    console.at(item_pos).fg = item_fg;
  }
  with_active_actors(world, [&](const Actor& actor) {
    if (!can_draw(actor.pos)) return;
    console.at(actor.pos).ch = actor.ch;
    console.at(actor.pos).fg = actor.fg;
  });
  if (g_controller.cursor) {
    auto& cursor = *g_controller.cursor;
    if (console.in_bounds(cursor) && map.visible.in_bounds(cursor)) {
      auto& cursor_tile = console.at(cursor);
      cursor_tile = {cursor_tile.ch, constants::BLACK, constants::WHITE};
    }
  }
}
inline void render_map() { render_map(g_console, *g_world); }

inline void render_log(tcod::Console& console, const World& world) {
  // x and y coordinates of the log console
  const int log_x = constants::LOG_X;
  const int log_y = constants::LOG_Y;
  // width and height of the console log
  const int log_width = constants::LOG_WIDTH;
  // const int log_width = console.get_width() - log_x;
  const int log_height = constants::LOG_HEIGHT;
  // const int log_height = console.get_height() - constants::MAP_HEIGHT;

  // creates the log console
  tcod::Console log_console{log_width, log_height};
  int y = log_console.get_height();
  for (auto it = world.log.messages.crbegin(); it != world.log.messages.crend(); ++it) {
    const auto& msg = *it;
    auto print_msg = [&](std::string_view text, const tcod::ColorRGB& fg) {
      y -= tcod::get_height_rect(log_console.get_width(), text);
      tcod::print_rect(log_console, {0, y, 0, log_console.get_width()}, text, fg, {});
    };
    if (msg.count > 1) {
      print_msg(fmt::format("{} (x{})", msg.text, msg.count), msg.fg);
    } else {
      print_msg(msg.text, msg.fg);
    }
    if (y < 0) break;
  }
  // this tells the renderer where to put the log console
  tcod::blit(console, log_console, {log_x, log_y});
}

// TODO: refactor this to fix all the hard coded values for sizes and positions
inline void draw_bar(
    tcod::Console& console,
    int x,
    int y,
    int width,
    int height,
    float filled,
    const tcod::ColorRGB fill_color,
    const tcod::ColorRGB back_color,
    std::string_view text = "",
    const tcod::ColorRGB text_color = constants::TEXT_COLOR_DEFAULT,
    TCOD_alignment_t alignment = TCOD_LEFT) {
  const auto bar_width = std::clamp(static_cast<int>(std::round(width * filled)), 0, width);
  tcod::draw_rect(console, {x, y, width, height}, 0, {}, back_color);
  tcod::draw_rect(console, {x, y, bar_width, height}, 0, {}, fill_color);
  if (text.size()) tcod::print_rect(console, {x, y, width, 1}, text, text_color, {}, alignment);
}

inline void render_mouse_look(tcod::Console& console, const World& world) {
  if (!g_controller.cursor) return;
  const auto& map = world.active_map();
  if (!(map.visible.in_bounds(*g_controller.cursor) && map.visible.at(*g_controller.cursor))) return;
  auto cursor_desc = std::vector<std::string>{};
  if (const auto found_fixture = map.fixtures.find(*g_controller.cursor); found_fixture != map.fixtures.end()) {
    cursor_desc.emplace_back(found_fixture->second.name);
  }
  with_active_actors(world, [&](const Actor& actor) {
    if (actor.pos == *g_controller.cursor) {
      cursor_desc.emplace_back(actor.name);
    }
  });
  /*
  {
    const auto items_range = map.items.equal_range(*g_controller.cursor);
    for (auto it{items_range.first}; it != items_range.second; ++it) {
      const auto& item = it->second;
      cursor_desc.emplace_back(fmt::format("{} ({})", item->get_name(), item->count));
    }
  }*/

  // TODO: figure out if this is the message log and adjust positioning and sizing
  tcod::print_rect(
      console,
      {1, 0, console.get_width() - 1, 1},
      fmt::format("{}", fmt::join(cursor_desc, ", ")),
      constants::TEXT_COLOR_DEFAULT,
      {});
}

inline void render_gui(tcod::Console& console, const World& world) {
  const auto& player = world.active_player();
  const int hp_x = constants::HP_BAR_X;
  const int hp_y = constants::HP_BAR_Y;
  const int xp_x = constants::XP_BAR_X;
  const int xp_y = constants::XP_BAR_Y;
  const int bar_width = constants::BAR_WIDTH;
  const int bar_height = constants::BAR_HEIGHT;

  // hp bar
  draw_bar(
      console,
      hp_x,
      hp_y,
      bar_width,
      bar_height,
      static_cast<float>(player.stats.hp) / player.stats.max_hp,
      constants::HP_BAR_FILL,
      constants::HP_BAR_BACK,
      fmt::format(" HP: {}/{}", player.stats.hp, player.stats.max_hp));

  // experience bar
  draw_bar(
      console,
      xp_x,
      xp_y,
      bar_width,
      bar_height,
      static_cast<float>(player.stats.xp) / next_level_xp(player.stats.level),
      constants::XP_BAR_FILL,
      constants::XP_BAR_BACK,
      fmt::format(" XP: {}", player.stats.xp));
  render_log(console, world);
  render_mouse_look(console, world);
}

inline void render_all(tcod::Console& console, const World& world) {
  render_map(console, world);
  render_gui(console, world);
}

inline void main_redraw() {
  g_console.clear();
  if (g_state) g_state->on_draw();
  g_context.present(g_console);
}

inline auto debug_show_map([[maybe_unused]] const Map& map) -> void {
#ifndef NDEBUG
  static int n = 0;
  render_map(g_console, map, true);
  g_context.present(g_console);
  SDL_Delay(100);
#endif
}
