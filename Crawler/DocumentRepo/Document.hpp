//
// Created by jora on 4/11/21.
//

#ifndef CRAWLER_DOCUMENT_HPP
#define CRAWLER_DOCUMENT_HPP
#include <ctime>
#include <string>

class Document {
private:
	int id;
	time_t updated;
	std::string url;
	std::string title;
	std::string description;
	std::string content;

public:
	Document(int id, std::string url, std::string title, std::string description, std::string content);

	inline int getId() const;
	inline time_t getUpdatedTime() const;
	inline const std::string& getUrl() const;
	inline const std::string& getTitle() const;
	inline const std::string& getDescription() const;
	inline const std::string& getContent() const;

};

#endif //CRAWLER_DOCUMENT_HPP
