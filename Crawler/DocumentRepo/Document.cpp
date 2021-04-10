//
// Created by jora on 4/11/21.
//

#include "Document.hpp"

Document::Document(int id, std::string url, std::string title, std::string description, std::string content)
		:id{ id },
		 url{ std::move(url) },
		 title{ std::move(title) },
		 description{ std::move(description) },
		 content{ std::move(content) }
{

}

inline int Document::getId() const
{
	return this->id;
}

inline time_t Document::getUpdatedTime() const
{
	return this->updated;
}

inline const std::string& Document::getUrl() const
{
	return this->url;
}

inline const std::string& Document::getTitle() const
{
	return this->title;
}

inline const std::string& Document::getDescription() const
{
	return this->description;
}

inline const std::string& Document::getContent() const
{
	return this->content;
}