//
// Created by jora on 6/24/21.
//

#include "ConsoleUI.hpp"

namespace ui {

void ConsoleUI::showMsg(const std::string& msg, bool err) const
{
    std::ostream& out = err ? std::cerr : std::cout;
    out << msg << std::endl;
}

void ConsoleUI::showSearchResult(const web::json::value& result) const
{
    if (result.size() == 0) {
        std::cout << "There's no found links for You :_(" << std::endl;
        return;
    }
    std::cout << "Found following results." << std::endl;

    const auto& arr = result.as_array();
    for (const auto& tmp : arr) {
        std::cout << tmp.at("url").serialize() << "\n\n";
        std::cout << tmp.at("title").serialize() << "\n";
        std::cout << tmp.at("description").serialize() << "\n\n\n" << std::endl;
    }
}

std::string ConsoleUI::ask(const std::string& question) const
{
    std::cout << question << std::endl;
    std::cout << "... waiting for answer ..." << std::endl;
    std::string answer{};
    std::cin >> answer;
    return answer;
}

std::string ConsoleUI::askForSearch() const
{
    std::cout << "Please enter the string - what you want to search: " << std::endl;
    std::string str{};
    std::cin >> str;
    return str;
}
} // namespace ui