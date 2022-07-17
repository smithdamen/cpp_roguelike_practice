#pragma once

#include <SDL.h>
#include <fmt/core.h>

#include "constants.hpp"
#include "globals.hpp"

inline void render_map(tcod::Console& console, const Map& map, bool show_all = false) {
  for (int y{0}; y < map.get_height(); ++y) {
    for (int x{0}; x < map.get_width(); ++x) {
      if (!console.in_bounds({x, y})) continue;
      if (!show_all && !map.explored.at({x, y})) continue;
      console.at({x, y}) = map.tiles.at({x, y}) == Tiles::floor
                               ? TCOD_ConsoleTile{'.', tcod::ColorRGB{128, 128, 128}, tcod::ColorRGB{0, 0, 0}}
                               : TCOD_ConsoleTile{'#', tcod::ColorRGB{128, 128, 128}, tcod::ColorRGB{0, 0, 0}};
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
  for (const auto& [actor_id, actor] : world.actors) {
    if (!map.visible.in_bounds(actor.pos)) continue;
    if (!map.visible.at(actor.pos)) continue;
    if (console.in_bounds(actor.pos)) {
      console.at(actor.pos) = {actor.ch, actor.fg, tcod::ColorRGB{0, 0, 0}};
    }
  }
}
inline void render_map() { render_map(g_console, *g_world); }

inline void render_log(tcod::Console& console, World& world) {
  tcod::Console log_console{console.get_width(), console.get_height() - constants::MAP_HEIGHT};
  int y = log_console.get_height();
  for (auto it = world.log.messages.crbegin(); it != world.log.messages.crend(); ++it) {
    const auto& msg = *it;
    const auto last_y = y;
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
  tcod::blit(console, log_console, {0, 45});
}

inline void render_all(tcod::Console& console, World& world) {
  render_map(console, world);
  render_log(console, world);
}

inline void main_redraw() {
  g_console.clear();
  if (g_state) g_state->on_draw();
  g_context.present(g_console);
}

inline auto debug_show_map(const Map& map) {
  static int n = 0;
#ifndef NDEBUG
  render_map(g_console, map, true);
  g_context.present(g_console);
  SDL_Delay(100);
#endif
}
