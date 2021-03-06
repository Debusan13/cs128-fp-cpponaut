#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include <memory>
#include <iostream>

#include <termox/termox.hpp>

#include "Node.hpp"
#include "FileSystem.hpp"
#include "termox/system/system.hpp"
#include "termox/system/detail/focus.hpp"
#include "ui/signal.hpp"

using namespace esc;

std::string SizeToHum(unsigned long size) {
  std::string suffix[3] = {"KB", "MB", "GB"};

  int i = 0;

  constexpr unsigned long block_size = 1024;
  
  if (size > block_size) {
    for (i = 0; (size / block_size) > 0 && i<3; i++)
      size /= block_size;
  }

  return (std::to_string(size) + " " + suffix[i]);
}

class Block : public ox::Text_view {
  public:
    Block(Node* node) : ox::Text_view{U""}, node_{node} { 
      std::string human_readable_size = SizeToHum(node_->inherit_size);
      auto str = node->name.generic_string() 
              + " " 
              + human_readable_size;
      this->set_text(ox::Glyph_string(str));

      // if (node->node_type == NodeType::Directory) {
      //   this->mouse_pressed.connect([&](auto) {
      //         Dispatcher::GetInstance().GoDown(node_->name);
      //       });
      // }

      auto parent = FileSystem::GetInstance().GetNode(node->name.parent_path());
      auto term_w = Terminal::area().width;
      int width = ((double) (node->inherit_size / parent->inherit_size)) * term_w;
      using namespace ox::pipe;
      *this | ox::bg((node->node_type == NodeType::Directory) ? unfocus_color_dir_ : unfocus_color_file_) | strong_focus() | fixed_height(1) | preferred_width(width);
    }

   protected:
    auto key_press_event(Key key) -> bool override {
      switch (key) {
        case Key::Enter:
        case Key::Space:
          if (node_->node_type == NodeType::Directory)
            Dispatcher::GetInstance().GoDown(node_->name);
          break;
        case Key::u:
        case Key::Backspace:
        case Key::Escape:
          Dispatcher::GetInstance().GoUp();
          break;
        case Key::j:
        case Key::Arrow_down:
          ox::detail::Focus::tab_press();
          break;
        case Key::k:
        case Key::Arrow_up:
          ox::detail::Focus::shift_tab_press();
          break;
        case Key::q:
          ox::System::quit();
        default: ;
      };
      return Widget::key_press_event(key);
    }

    auto mouse_press_event(Mouse const& m) -> bool override 
    {
      if (node_->node_type == NodeType::Directory)
        Dispatcher::GetInstance().GoDown(node_->name);
      return Widget::mouse_press_event(m);
    }

    auto focus_in_event() -> bool override
    {
        *this | ox::bg(focus_color_);
        return Widget::focus_in_event();
    }

    auto focus_out_event() -> bool override
    {
        *this | ox::bg((node_->node_type == NodeType::Directory) ? unfocus_color_dir_ : unfocus_color_file_);
        return Widget::focus_out_event();
    } 

  private:
    Node* node_;
    constexpr static auto focus_color_   = ox::macintosh_ii::Silver;
    constexpr static auto unfocus_color_dir_  = ox::macintosh_ii::Gray;
    constexpr static auto unfocus_color_file_ = ox::macintosh_ii::Dark_gray;
};

#endif
