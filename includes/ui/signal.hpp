#ifndef SIGNAL_HPP_
#define SIGNAL_HPP_

#include <filesystem>
#include <signals_light/signal.hpp>

static auto block_focus = sl::Signal<void(const std::filesystem::path&)>{};

static auto location_change = sl::Signal<void(const std::filesystem::path&)>{};

class Dispatcher {
private:
  std::filesystem::path path_;

  Dispatcher() {
    path_ = "/";
    location_change.connect([&](auto path) {
          path_ = path;
        });
  }

public:
  static Dispatcher& GetInstance() {
    static Dispatcher instance{};
    return instance;
  }

  void GoDown(const std::filesystem::path& path) {
    path_ /= path;
    location_change.emit(path_);
  }

  void GoUp() {
    location_change.emit(path_.parent_path());
  }
};

#endif
