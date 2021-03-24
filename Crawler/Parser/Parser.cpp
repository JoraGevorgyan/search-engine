//
// Created by jora on 3/13/21.
//

#include "Parser.hpp"

Parser::Parser(std::string html, std::string startingUrl)
    : html{std::move(html)}
    , startingUrl{std::move(startingUrl)} {
}

int Parser::parse() {
    GumboOutput *output = gumbo_parse(html.c_str());
    if (output == nullptr) {
        return errno;
    }

    // extracting urls
    std::string homeUrl = this->getHomeUrl(this->startingUrl);
    int err = this->extractUrls(output->root, homeUrl);
    if (err != 0) {
        return err;
    }

    // extracting a title
    err = this->extractTitle(output->root);
    if(err != 0) {
        return err;
    }
    // extracting description


    // clean up
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    return 0;
}


int Parser::extractTitle(GumboNode* node) {
    if(node->type != GUMBO_NODE_ELEMENT) {
        return -1;
    }

    GumboVector* children = &node->v.element.children;

    if(node->v.element.tag == GUMBO_TAG_TITLE && children->length != 0) {
        this->title = std::string(static_cast<GumboNode*>(children->data[0])->v.text.text);
        return 0;
    }

    for(size_t i = 0; i < children->length; ++i) {
        this->extractTitle(static_cast<GumboNode*>(children->data[i]));
    }
    return 0;
}

int Parser::extractUrls(GumboNode* node, const std::string& homeUrl) {
    if(node->type != GUMBO_NODE_ELEMENT) {
        return -1;
    }
    if(node->v.element.tag != GUMBO_TAG_A) {
        GumboVector* children = &node->v.element.children;
        for(size_t i = 0; i < children->length; ++i) {
            this->extractUrls(static_cast<GumboNode*>(children->data[i]), homeUrl);
        }
        return 0;
    }

    GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
    if(href == nullptr || href->value == nullptr) {
        return -1;
    }
    std::string curUrl = std::string(href->value);
    std::string curHomeUrl = this->getHomeUrl(curUrl);

    // skip if out of current webiste or started at '#'
    if(!curHomeUrl.empty() && curHomeUrl != homeUrl || curUrl.front() == '#' || curUrl.empty()) {
        return 0;
    }

    if(curHomeUrl == homeUrl) {
        this->urls.push_back(curUrl);
    }
    else {
        this->urls.push_back(this->addPath(homeUrl, curUrl));
    }
    return 0;
}

std::string Parser::getHomeUrl(const std::string& url) const {
    size_t breakIndex = 1;
    for(size_t i = 1; i < url.size(); ++i, ++breakIndex) {
        if(url[i] == '/' && url[i - 1] == '/') {
            break;
        }
    }
    if(breakIndex == 1) {
        return std::string("");
    }
    while(breakIndex < url.size() && url[++breakIndex] != '/');

    return std::string(url, 0, breakIndex);
}

std::string Parser::addPath(const std::string& homeUrl, const std::string& path) const {
   if(path.empty()) {
       exit(1);
   }
   if(path.front() == '/') {
       return homeUrl + path;
   }
   // erase last part from starting url for getting current page url and add path on it
    size_t index = 0;
   for(index = this->startingUrl.size() - 1; index != 0 && this->startingUrl[index] != '/'; --index);
   // starting url was invalid
   if(index == 0) {
       exit(1);
   }
   auto it = this->startingUrl.begin();
   std::string currentPage(it, it + index + 1);
   return currentPage + path;
}

const std::vector<std::string>& Parser::getUrls() const {
    return this->urls;
}

const std::string& Parser::getTitle() const {
    return this->title;
}

const std::string& Parser::getDescription() const {
    return this->description;
}

const std::string& Parser::getContent() const {
    return this->content;
}
