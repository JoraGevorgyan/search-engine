//
// Created by jora on 6/24/21.
//

#ifndef UI_UI_HPP
#define UI_UI_HPP

#include <string>
#include <cpprest/json.h>

namespace ui {

class UI {
public:
    virtual ~UI() = default;
    virtual void showMsg(const std::string& msg, bool err = false) const = 0;
    virtual void showSearchResult(const web::json::value& result) const = 0;
    virtual std::string ask(const std::string& question) const = 0;
    virtual std::string askForSearch() const = 0;
};
} // namespace ui

#endif //UI_UI_HPP
