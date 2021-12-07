#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include <memory>
#include <iostream>

#include <termox/termox.hpp>

#include "Node.hpp"
#include "termox/system/system.hpp"
#include "termox/system/detail/focus.hpp"
#include "ui/signal.hpp"

using namespace esc;

class Block : public ox::Text_view {
  public:
    Block(Node* node) : ox::Text_view{U""}, node_{node} { 
      auto str = node->name.generic_string() 
              + " " 
              + std::to_string(node->inherit_size);
      this->set_text(ox::Glyph_string(str));

      if (node->node_type == NodeType::Directory) {
        this->mouse_pressed.connect([&](auto) {
              Dispatcher::GetInstance().GoDown(node_->name);
            });
      }

      using namespace ox::pipe;
      *this | ox::bg(unfocus_color_) | strong_focus() | fixed_height(1);
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
        case Key::q:
          ox::System::quit();
        case Key::j:
        case Key::Arrow_down:
          ox::detail::Focus::tab_press();
          break;
        case Key::k:
        case Key::Arrow_up:
          ox::detail::Focus::shift_tab_press();
          break;
        default: ;
      };
      return Widget::key_press_event(key);
    }

    auto focus_in_event() -> bool override
    {
        *this | ox::bg(focus_color_);
        return Widget::focus_in_event();
    }

    auto focus_out_event() -> bool override
    {
        *this | ox::bg(unfocus_color_);
        return Widget::focus_out_event();
    } 

  private:
    Node* node_;
    constexpr static auto focus_color_   = ox::macintosh_ii::Silver;
    constexpr static auto unfocus_color_ = ox::macintosh_ii::Dark_gray;
};

#endif
