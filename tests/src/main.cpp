#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include <ftxui/dom/elements.hpp>
#include <memory>
#include <string>
#include <vector>

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::Fullscreen();

  // Variables de estado
  int selected_tab = 0;
  std::vector<std::string> tab_entries = {"Crypto", "Fiat", "Favorites"};
  bool show_settings = false;

  std::vector<std::string> settings_entries = {"Menu", "API Configuration",
                                               "Themes"};
  // Componente: menú de pestañas
  auto tab_menu = Menu(&tab_entries, &selected_tab, MenuOption::Horizontal());

  auto settings_menu =
      Menu(&tab_entries, &selected_tab, MenuOption::Vertical());
  // Componente: settings
  auto settings_component = Renderer(settings_menu, [&] {
    std::string content;
    switch (selected_tab) {
    case 0:
      content = "mfkdasdjf";
      break;
    case 1:
      content = "79";
      break;
    case 2:
      content = "★ BTC";
      break;
    }

    return vbox({settings_menu->Render()}) | border | clear_under | center;
  });

  // Componente: contenido principal
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

    return vbox({// Cabecera: menú y aviso de settings
                 hbox({
                     tab_menu->Render() | flex,
                     separator(),
                     text("settings(ESC)") | align_right,
                 }) | border,

                 // Contenido central
                 vbox({
                     text(content) | center | flex,
                 }) | flex}) |
           flex;
  });

  // Variable para indicar qué componente (pestaña) está activo:
  int active_tab_index = 0;

  // Se combinan los componentes en un contenedor de pestañas.
  // La posición 0 es main_component y la 1 es settings_component.
  auto main_container =
      Container::Tab({main_component, settings_component}, &active_tab_index);

  // Aseguramos que el contenedor principal tenga el foco.
  main_container->TakeFocus();

  // Manejador global de eventos: alterna entre el contenido principal y
  // settings al presionar ESC.
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
