//
// Created by jora on 3/13/21.
//

#include "Parser.hpp"

Parser::Parser(std::string html, std::string startingUrl)
		: html{ std::move(html) }, startingUrl{ std::move(startingUrl) }, error{ 0 }
{
	this->parse();
}

void Parser::parse()
{
	GumboOutput* output = gumbo_parse(html.c_str());
	if (output == nullptr) {
		this->error = errno;
		return;
	}
	const auto homeUrl = Parser::getHomeUrl(this->startingUrl);
	if (!homeUrl.first) {
		std::cerr << "Parser: effective url was invalid ... can't find domain name" << std::endl;
		this->error = -1;
		return;
	}
	this->error = this->extractUrls(output->root, homeUrl.second);
	if (this->error == 0) {
		this->error = this->extractTitle(output->root);
	}
	if (this->error == 0) {
		this->error = this->extractDescription(output->root);
	}
	if (this->error == 0) {
		this->error = this->extractContent(output->root);
	}
	// clean up
	gumbo_destroy_output(&kGumboDefaultOptions, output);
}

int Parser::extractUrls(GumboNode* node, const std::string& homeUrl)
{
	if (node->type != GUMBO_NODE_ELEMENT) {
		return 0;
	}

	if (node->v.element.tag != GUMBO_TAG_A) {
		GumboVector* children = &node->v.element.children;
		for (size_t i = 0; i < children->length; ++i) {
			int err = this->extractUrls(static_cast<GumboNode*>(children->data[i]), homeUrl);
			if (err != 0) {
				return err;
			}
		}
		return 0;
	}

	GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
	if (href == nullptr || href->value == nullptr) {
		std::cerr << "There's an invalid href in html!" << std::endl;
		return -1;
	}
	std::string curUrl = std::string(href->value);
	const auto curHomeUrl = Parser::getHomeUrl(curUrl);
	if (curUrl.empty() || !curHomeUrl.first) {
		std::cout << "There's an empty url!" << std::endl;
		return 0;
	}
	// skip if it's out of current website or started at '#'
	const bool equals = curHomeUrl.second != homeUrl;
	if (equals || curUrl.front() == '#') {
		return 0;
	}
	if (!equals) {
		const auto toAdd = this->addPath(homeUrl, curUrl);
		if (!toAdd.first) {
			return -1;
		}
		this->urls.push_back(toAdd.second);
	}
	else {
		this->urls.push_back(curUrl);
	}
	return 0;
}

int Parser::extractTitle(GumboNode* node)
{
	if (node->type != GUMBO_NODE_ELEMENT) {
		return 0;
	}
	GumboVector* children = &node->v.element.children;

	if (node->v.element.tag == GUMBO_TAG_TITLE && children->length != 0) {
		this->title = std::string(static_cast<GumboNode*>(children->data[0])->v.text.text);
		return 0;
	}

	for (size_t i = 0; i < children->length; ++i) {
		int err = this->extractTitle(static_cast<GumboNode*>(children->data[i]));
		if (err != 0) {
			return err;
		}
	}
	return 0;
}

std::pair<bool, std::string> Parser::getHomeUrl(const std::string& url)
{
	size_t breakIndex = 1;
	for (size_t i = 1; i < url.size(); ++i, ++breakIndex) {
		if (url[i] == '/' && url[i - 1] == '/') {
			break;
		}
	}
	if (breakIndex == 1) {
		return std::make_pair(false, "");
	}
	++breakIndex;
	while (breakIndex < url.size() && url[breakIndex] != '/') {
		++breakIndex;
	}
	return std::make_pair(true, std::string(url, 0, breakIndex));
}

std::pair<bool, std::string> Parser::addPath(const std::string& homeUrl, const std::string& path) const
{
	if (path.empty()) {
		return std::make_pair(false, "");
	}
	if (path.front() == '/') {
		return std::make_pair(true, homeUrl + path);
	}
	// erase last part from starting url for getting current page url and add path on it
	unsigned index = 0;
	for (index = this->startingUrl.size() - 1; index != 0; --index) {
		if (this->startingUrl[index] == '/') {
			break;
		}
	}
	// starting url was invalid
	if (index == 0) {
		std::cerr << "Parser: effective url was invalid ... can't find domain name" << std::endl;
		return std::make_pair(false, "");
	}
	auto it = this->startingUrl.begin();
	std::string currentPage(it, it + index + 1);
	return std::make_pair(true, currentPage + path);
}

int Parser::extractDescription(GumboNode* node)
{
	if (node->type != GUMBO_NODE_ELEMENT) {
		return 0;
	}
	// if is not a meta tag, than search it in others
	if (node->v.element.tag != GUMBO_TAG_META) {
		GumboVector* children = &node->v.element.children;
		for (size_t i = 0; i < children->length; ++i) {
			int err = this->extractDescription(static_cast<GumboNode*>(children->data[i]));
			if (err != 0) {
				return err;
			}
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
