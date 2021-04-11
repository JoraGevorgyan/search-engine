//
// Created by jora on 4/11/21.
//

#ifndef CRAWLER_DOCUMENT_HPP
#define CRAWLER_DOCUMENT_HPP
#include <ctime>
#include <string>

class Document {
private:
	std::string url;
	std::string title;
	std::string description;
	std::string content;
	time_t updated;

public:
	Document(std::string url, std::string title, std::string description, std::string content, time_t updated);

	[[nodiscard]] inline const std::string& getUrl() const
	{
		return this->url;
	}
	[[nodiscard]] inline const std::string& getTitle() const
	{
		return this->title;
	}
	[[nodiscard]] inline const std::string& getDescription() const
	{
		return this->description;
	}
	[[nodiscard]] inline const std::string& getContent() const
	{
		return this->content;
	}
	[[nodiscard]] inline time_t getUpdatedTime() const
	{
		return this->updated;
	}
};

#endif //CRAWLER_DOCUMENT_HPP
