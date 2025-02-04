#include <memory>
#include <string>
#include <vector>
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::Fullscreen();
  int selected_tab = 0;
  std::vector<std::string> tab_entries = {"Crypto", "Fiat", "Favorites"};

  auto tab_menu = Menu(&tab_entries, &selected_tab, MenuOption::Horizontal());

  auto main_component = Renderer(tab_menu, [&] {
    std::string content;
    switch (selected_tab) {
      case 0: content = "Crypto Content"; break;
      case 1: content = "Fiat Content"; break;
      case 2: content = "Favorites Content"; break;
    }

    return vbox({
      tab_menu->Render() | border | flex_shrink, 
      separator(),
      text(content) | center | flex,
      }) | flex;   });


  screen.Loop(main_component);
  return EXIT_SUCCESS;
}

