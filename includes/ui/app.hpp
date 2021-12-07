#ifndef APP_HPP_
#define APP_HPP_

#include <termox/termox.hpp>

#include "FileSystem.hpp"
#include "termox/widget/align.hpp"
#include "ui/signal.hpp"
#include "ui/block.hpp"

using namespace ox;
using namespace ox::pipe;

struct DisplayPanel : layout::Vertical<> {
  DisplayPanel(const std::filesystem::path& str) {
    SetContent(str);
    
    // update content when location chnages
    location_change.connect([&](auto str) {
        SetContent(str);
      });
  }

  void SetContent(const std::filesystem::path& str) {
    this->delete_all_children();
    auto node = FileSystem::GetInstance().GetNode(str);
    for (const auto& child : node->children) {
      this->append_child(std::make_unique<Block>(child.get()));
    }
    this->append_child(std::make_unique<Text_view>(U"")) | bg(macintosh_ii::Dark_gray);
    System::set_focus(*this->children_.front().get());
    this->children_.back() | expanding_height(1);
  }
};

class PathLabel : public Textbox {
  public:
    PathLabel(const std::filesystem::path& str) : Textbox(ox::Glyph_string(str)) {
      // update label text when location changes
      location_change.connect([&](auto str) {
        this->set_text(Glyph_string(str));
      });

      *this | no_focus() | fixed_height(1) | bg(ox::macintosh_ii::Dark_gray);
    }
};

struct App : layout::Vertical<> {
  DisplayPanel& display_panel = this->make_child<DisplayPanel>("/"); 
  PathLabel& path_label = this->make_child<PathLabel>("/"); 
};

#endif
