//
// Created by jora on 3/12/21.
//

#ifndef SEARCH_ENGINE_PAGE_LOADER_HPP
#define SEARCH_ENGINE_PAGE_LOADER_HPP

#include <string>
#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

#include "Page.hpp"

class PageLoader {
public:
    Page load(const std::string& url);
};

#endif //SEARCH_ENGINE_PAGE_LOADER_HPP
