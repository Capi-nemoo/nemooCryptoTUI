#include <memory>
#include <string>
#include <vector>
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;

int main() {
  // Create a full-screen interactive FTXUI screen.
  auto screen = ScreenInteractive::Fullscreen();

  // -------------------------------
  // State Variables
  // -------------------------------
  // 'selected_tab' tracks which tab is currently selected in the menu.
  int selected_tab = 0;
  // 'tab_entries' is a list of the names for the tabs.
  std::vector<std::string> tab_entries = {"|   Crypto   |", "|   Fiat   |" , "|   Favorites   |"};
  // 'show_settings' determines whether the settings view is displayed.
  bool show_settings = false;

  // -------------------------------
  // Components
  // -------------------------------
  // Create a horizontal menu for selecting tabs.
  auto tab_menu = Menu(&tab_entries, &selected_tab, MenuOption::Horizontal());

  // Create the settings component.
  // This view displays various settings options.
  auto settings_component = Renderer([&] {
    return vbox({
      text("Settings Menu") | bold | center,
      separator(),
      text("- Refresh Interval"),
      text("- Currency Preferences"),
      text("- API Configuration"),
      text("Press ESC to return") | color(Color::GrayDark) | center,
    }) | border | clear_under | center;
  });

  // Create the main content component.
  // It uses the current tab (selected_tab) to display different content.
  // The tab_menu is also rendered here in the header.
  auto main_component = Renderer(tab_menu, [&] {
    std::string content;
    switch(selected_tab) {
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

    return vbox({
      // Header: contains the tab menu and a prompt to access settings.
      hbox({
        tab_menu->Render() | flex,
        separator(),
        text("Press ESC for settings") | align_right,
      }) | border,
      
      // Main content area: displays tab-specific information.
      vbox({
        text(content) | center | flex,
      }) | flex
    }) | flex;
  });

  // -------------------------------
  // Container for Views
  // -------------------------------
  // 'active_tab_index' indicates which component (tab) is active:
  // 0 for the main content, 1 for the settings view.
  int active_tab_index = 0;

  // Combine the main content and settings components into a tab container.
  // This container will show the component at 'active_tab_index'.
  auto main_container = Container::Tab({ main_component, settings_component }, &active_tab_index);

  // Make sure the container has keyboard focus so it can receive events.
  main_container->TakeFocus();

  // -------------------------------
  // Global Event Handler
  // -------------------------------
  // This handler listens for key events. When ESC is pressed,
  // it toggles between the main view and the settings view.
  auto global_handler = CatchEvent(main_container, [&](Event event) {
    if (event == Event::Escape) {
      // Toggle the 'show_settings' flag.
      show_settings = !show_settings;
      // Update the active tab: 1 for settings, 0 for main content.
      active_tab_index = show_settings ? 1 : 0;
      return true;  // Event has been handled.
    }
    return false;  // Let other events propagate if not handled.
  });

  // Start the main event loop.
  screen.Loop(global_handler);
  return EXIT_SUCCESS;
}

