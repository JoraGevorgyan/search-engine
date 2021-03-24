//
// Created by jora on 3/13/21.
//

#include "Parser.hpp"

Parser::Parser(const std::string& html, const std::string& rootUrl) : html(html), rootUrl(rootUrl) {

}

void Parser::parse() {
    // extracting urls
    auto domain = this->getDomain(this->rootUrl);
    GumboOutput* output = gumbo_parse(html.c_str());
    if(output == nullptr) {
        return;
    }
    this->extractUrls(output->root, domain);

    // extracting a title
    this->extractTitle(output->root);

    // extracting description


    gumbo_destroy_output(&kGumboDefaultOptions, output);
}


void Parser::extractTitle(GumboNode* node) {
    if(node->type != GUMBO_NODE_ELEMENT) {
        return;
    }

    GumboVector* children = &node->v.element.children;

    if(node->v.element.tag == GUMBO_TAG_TITLE && children->length != 0) {
        this->title = std::string(static_cast<GumboNode*>(children->data[0])->v.text.text);
        // this->title = std::string(node->v.element.original_tag.data);
        return;
    }

    for(size_t i = 0; i < children->length; ++i) {
        this->extractTitle(static_cast<GumboNode*>(children->data[i]));
    }
}

void Parser::extractUrls(GumboNode* node, const std::string& domain) {
    if(node->type != GUMBO_NODE_ELEMENT) {
        return;
    }

    if(node->v.element.tag != GUMBO_TAG_A) {
        GumboVector* children = &node->v.element.children;
        for(size_t i = 0; i < children->length; ++i) {
            this->extractUrls(static_cast<GumboNode*>(children->data[i]), domain);
        }
        return;
    }
    GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
    if(href == nullptr || href->value == nullptr) {
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

    // https://domain/
    // rau.am/a/b/x + y = rau.am/a/b/y
    // rau.am/a/b/x/ + y = rau.am/a/b/x/y
    // rau.am/a/b/c/x + /z = rau.am/z
    // if started at '#' => skip



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
