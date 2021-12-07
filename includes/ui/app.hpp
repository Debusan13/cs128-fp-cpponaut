#ifndef APP_HPP_
#define APP_HPP_

#include <termox/termox.hpp>

#include "FileSystem.hpp"
#include "ui/signal.hpp"
#include "ui/block.hpp"

using namespace ox;
using namespace ox::pipe;

struct DisplayPanel : layout::Vertical<> {
  DisplayPanel(const std::filesystem::path& str) {
    SetContent(str);
    
    // update content when location chnages
    location_change.connect([](auto str) {
        str.generic_string();
        // SetContent(str);
      });
  }

  void SetContent(const std::filesystem::path& str) {
    auto node = FileSystem::GetInstance().GetNode(str);
    this->delete_all_children();
    for (const auto& child : node->children) {
      this->append_child(std::make_unique<Block>(Glyph_string(child->name)));
    }
  }
};

class PathLabel : public Textbox {
  public:
    PathLabel(const std::filesystem::path& str) : Textbox(ox::Glyph_string(str)) {
      // update label text when location changes
      location_change.connect([this](auto str) {
        this->set_text(Glyph_string(str));
      });

      *this | no_focus();
    }
};

struct App : layout::Vertical<> {
  DisplayPanel& display_panel = this->make_child<DisplayPanel>("/"); 
  PathLabel& path_label = this->make_child<PathLabel>("/"); 
};

#endif
