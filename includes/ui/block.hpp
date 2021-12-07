#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include <memory>

#include <termox/termox.hpp>

#include "ui/signal.hpp"

using namespace ox;

class Block : public ox::Button {
  public:
    Block(ox::Glyph_string filename) : ox::Button{std::move(filename)} { 
      // focus when the right signal is received
      // block_focus.connect([&](const std::filesystem::path& path) {
      //   if (this->text() == filename) {
      //     *this | ox::bg(focus_color_);
      //   } else {
      //     *this | ox::bg(unfocus_color_);
      //   }
      // });

      *this | ox::bg(unfocus_color_);
    }

   protected:
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
    ox::Glyph_string filename_;
    constexpr static auto focus_color_   = ox::Color::Red;
    constexpr static auto unfocus_color_ = ox::Color::Blue;
};

#endif
