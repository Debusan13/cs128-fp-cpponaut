#ifndef SIGNAL_HPP_
#define SIGNAL_HPP_

#include <filesystem>
#include <signals_light/signal.hpp>

static auto block_focus = sl::Signal<void(const std::filesystem::path&)>{};

static auto location_change = sl::Signal<void(const std::filesystem::path&)>{};

#endif
