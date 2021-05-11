//
// Created by jora on 3/13/21.
//

#include "Parser.hpp"

Parser::Parser(std::string html, std::string startingUrl)
		:html{ std::move(html) }, startingUrl{ std::move(startingUrl) }
{
	this->error = this->parse();

}

int Parser::parse()
{
	GumboOutput* output = gumbo_parse(html.c_str());
	if (output == nullptr) {
		return errno;
	}

	std::string homeUrl = Parser::getHomeUrl(this->startingUrl);
	int err = this->extractUrls(output->root, homeUrl);
	if (err != 0) {
		return err;
	}

	err = this->extractTitle(output->root);
	if (err != 0) {
		return err;
	}

	err = this->extractDescription(output->root);
	if (err != 0) {
		return err;
	}

	err = this->extractContent(output->root);
	if (err != 0) {
		return err;
	}

	// clean up
	gumbo_destroy_output(&kGumboDefaultOptions, output);
	return 0;
}

int Parser::extractUrls(GumboNode* node, const std::string& homeUrl)
{
	if (node->type != GUMBO_NODE_ELEMENT) {
		return -1;
	}

	if (node->v.element.tag != GUMBO_TAG_A) {
		GumboVector* children = &node->v.element.children;
		for (size_t i = 0; i < children->length; ++i) {
			this->extractUrls(static_cast<GumboNode*>(children->data[i]), homeUrl);
		}
		return 0;
	}

	GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
	if (href == nullptr || href->value == nullptr) {
		return -1;
	}
	std::string curUrl = std::string(href->value);
	std::string curHomeUrl = Parser::getHomeUrl(curUrl);

	// skip if is out of current webiste or started at '#'
	if (!curHomeUrl.empty() && curHomeUrl != homeUrl || curUrl.front() == '#' || curUrl.empty()) {
		return 0;
	}

	if (curHomeUrl == homeUrl) {
		this->urls.push_back(curUrl);
	}
	else {
		this->urls.push_back(this->addPath(homeUrl, curUrl));
	}
	return 0;
}

int Parser::extractTitle(GumboNode* node)
{
	if (node->type != GUMBO_NODE_ELEMENT) {
		return -1;
	}
	GumboVector* children = &node->v.element.children;

	if (node->v.element.tag == GUMBO_TAG_TITLE && children->length != 0) {
		this->title = std::string(static_cast<GumboNode*>(children->data[0])->v.text.text);
		return 0;
	}

	for (size_t i = 0; i < children->length; ++i) {
		this->extractTitle(static_cast<GumboNode*>(children->data[i]));
	}
	return 0;
}

std::string Parser::getHomeUrl(const std::string& url)
{
	size_t breakIndex = 1;
	for (size_t i = 1; i < url.size(); ++i, ++breakIndex) {
		if (url[i] == '/' && url[i - 1] == '/') {
			break;
		}
	}
	if (breakIndex == 1) {
		return std::string("");
	}
	++breakIndex;
	while (breakIndex < url.size() && url[breakIndex] != '/') {
		++breakIndex;
	}

	return std::string(url, 0, breakIndex);
}

std::string Parser::addPath(const std::string& homeUrl, const std::string& path) const
{
	if (path.empty()) {
		return std::string("");
	}
	if (path.front() == '/') {
		return homeUrl + path;
	}
	// erase last part from starting url for getting current page url and add path on it
	unsigned index = 0;
	for (index = this->startingUrl.size() - 1; index != 0; --index) {
		if (this->startingUrl[index] == '/') {
			break;
		}
	}
	// starting url was error
	if (index == 0) {
		std::cerr << "Parser: effective url was error ... can't find domain name" << std::endl;
	}
	auto it = this->startingUrl.begin();
	std::string currentPage(it, it + index + 1);
	return currentPage + path;
}

int Parser::extractDescription(GumboNode* node)
{
	if (node->type != GUMBO_NODE_ELEMENT) {
		return -1;
	}
	// if is not a meta tag, than search it in others
	if (node->v.element.tag != GUMBO_TAG_META) {
		GumboVector* children = &node->v.element.children;
		for (size_t i = 0; i < children->length; ++i) {
			this->extractDescription(static_cast<GumboNode*>(children->data[i]));
		}
	}
	// if the tag type is meta, than take from it description  and return
	GumboAttribute* name = gumbo_get_attribute(&node->v.element.attributes, "name");
	if (name == nullptr || name->value == nullptr || std::string(name->value) != "description") {
		return 0;
	}

	GumboAttribute* cont = gumbo_get_attribute(&node->v.element.attributes, "content");
	if (cont == nullptr || cont->value == nullptr) {
		return -1;
	}
	this->description = std::string(cont->value);
	return 0;
}

int Parser::extractContent(GumboNode* node)
{
	if (this->content.size() > Parser::maxContentSize) {
		return 0;
	}
	if (node->type == GUMBO_NODE_TEXT) {
		this->content += std::string(node->v.text.text);
		this->content += '\n';
		return 0;
	}
	// nothing to do
	if (node->type != GUMBO_NODE_ELEMENT ||
			node->v.element.tag == GUMBO_TAG_STYLE ||
			node->v.element.tag == GUMBO_TAG_SCRIPT) {
		return 0;
	}

	GumboVector* children = &node->v.element.children;
	for (size_t i = 0; i < children->length; ++i) {
		this->content += ' ';
		int err = this->extractContent(static_cast<GumboNode*>(children->data[i]));
		if (err != 0) {
			return err;
		}
	}
	return 0;
}
