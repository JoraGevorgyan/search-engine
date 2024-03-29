//
// Created by jora on 6/24/21.
//

#ifndef UI_CONSOLEUI_HPP
#define UI_CONSOLEUI_HPP

#include "UI.hpp"

namespace ui {

class ConsoleUI : public UI {
public:
    void showMsg(const std::string& msg, bool err = false) const override;
    void showSearchResult(const web::json::value& result) const override;
    [[nodiscard]] std::string ask(const std::string& question) const override;
    [[nodiscard]] std::string askForSearch() const override;
};
} // namespace ui

#endif //UI_CONSOLEUI_HPP
