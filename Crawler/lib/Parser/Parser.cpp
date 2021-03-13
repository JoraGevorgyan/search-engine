//
// Created by jora on 3/13/21.
//

#include "Parser.hpp"

Parser::Parser(const std::string& html, const std::string& rootUrl) : html(html), rootUrl(rootUrl) {

}

void Parser::parse() {
    // extracting urls
    this->domain = this->getDomain(this->rootUrl);
    GumboOutput* output = gumbo_parse(html.c_str());
    if(output == nullptr) {
        return;
    }
    this->extractUrls(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    //
}


void Parser::extractUrls(GumboNode* node) {
    if(node->type != GUMBO_NODE_ELEMENT) {
        return;
    }

    if(node->v.element.tag != GUMBO_TAG_A) {
        GumboVector* children = &node->v.element.children;
        for(size_t i = 0; i < children->length; ++i) {
            this->extractUrls(static_cast<GumboNode*>(children->data[i]));
        }
        return;
    }
    GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
    if(href->value == nullptr) {
        return;
    }
    std::string curUrl = std::string(href->value);

    if(this->isAbsUrl(curUrl)) { // is outside from our page or contains our domain
        std::string curDomain = this->getDomain(curUrl);
        if(curDomain != this->domain) {
            return;
        }
        this->urls.push_back(curUrl);
        return;
    }

    this->urls.push_back(this->domain + curUrl);
}

std::string Parser::getDomain(const std::string& url) {
    size_t breakIndex = 1;
    for(size_t i = 1; i < url.size(); ++i, ++breakIndex) {
        if(url[i] == '/' && url[i - 1] == '/') {
            break;
        }
    }
    while(url[++breakIndex] != '/');

    return std::string(url, 0, breakIndex);
}

bool Parser::isAbsUrl(const std::string& url) const {
    if(url.size() == 1) {
        return false;
    }

    if(url[0] == '/' && url[1] == '/'
            || std::string(url, 0, 7) == "http://"
            || std::string(url, 0, 8) == "https://") {
        return true;
    }

    return false;
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
