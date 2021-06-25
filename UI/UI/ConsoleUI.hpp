//
// Created by jora on 6/24/21.
//

#ifndef UI_CONSOLEUI_HPP
#define UI_CONSOLEUI_HPP

#include "UI.hpp"

namespace ui {

class ConsoleUI : public UI {
    void showMsg(const std::string& msg, bool err = false) override;
    void showSearchResult(const web::json::value& result) override;
    std::string ask(const std::string& question) override;
    std::string askForSearch() override;
};
} // namespace ui

#endif //UI_CONSOLEUI_HPP
