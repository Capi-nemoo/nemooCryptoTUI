#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::Fullscreen();
  int active_tab_index = 0;

  std::vector<std::string> tab_entries = {"  Crypto  ", "  Fiat  ",
                                          "  Favorites  "};
  int selected_tab = 0;
  auto tab_menu = Menu(&tab_entries, &selected_tab, MenuOption::Horizontal());
  auto main_component = Renderer(tab_menu, [&] {
    std::string content;
    switch (selected_tab) {
    case 0:
      content = "BTC: $00,000.00 (+0.00%)\nETH: $0,000.00 (+0.00%)";
      break;
    case 1:
      content = "USD: 1.00\nEUR: 0.92\nGBP: 0.79";
      break;
    case 2:
      content = "★ BTC\n★ ETH\n★ USD/EUR";
      break;
    }
    return vbox({hbox({
                     tab_menu->Render() | flex,
                     separator(),
                     text("settings(ESC)") | align_right,
                 }) | border,
                 vbox({
                     text(content) | center | flex,
                 }) | flex}) |
           flex;
  });

  //-----------------------------------------------------------------------------
  std::vector<std::string> settings_entries = {"Menu", "API Configuration",
                                               "Themes"};
  bool show_settings = false;
  int selected_tab_settings = 0;
  auto settings_menu =
      Menu(&settings_entries, &selected_tab_settings, MenuOption::Vertical());
  auto settings_component = Renderer(settings_menu, [&] {
    std::string content;
    switch (selected_tab_settings) {
    case 0:
      content = " Menu goes here ";
      break;
    case 1:
      content = " API goes here ";
      break;
    case 2:
      content = "Menu options here ";
      break;
    }
    return vbox({settings_menu->Render()}) | border | clear_under | center;
  });

  //------------------------------------------------------------------------------

  auto main_container =
      Container::Tab({main_component, settings_component}, &active_tab_index);
  main_container->TakeFocus();
  auto global_handler = CatchEvent(main_container, [&](Event event) {
    if (event == Event::Escape) {
      show_settings = !show_settings;
      active_tab_index = show_settings ? 1 : 0;
      return true;
    }
    return false;
  });
  screen.Loop(global_handler);
  return EXIT_SUCCESS;
}
