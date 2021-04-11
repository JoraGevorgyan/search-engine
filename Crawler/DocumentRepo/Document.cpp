//
// Created by jora on 4/11/21.
//

#include "Document.hpp"

Document::Document(std::string url, std::string title, std::string description, std::string content, time_t updated)
		:url{ std::move(url) },
		 title{ std::move(title) },
		 description{ std::move(description) },
		 content{ std::move(content) },
		 updated{ updated }
{

}