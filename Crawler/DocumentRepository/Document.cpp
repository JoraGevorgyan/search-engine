//
// Created by jora on 4/6/21.
//

#include "Index.hpp"

Index::Index(int id, std::string url, std::string title, std::string description, std::string content)
    : id{id},
      url{std::move(url)},
      title{std::move(title)},
      description{std::move(description)},
      content{std::move(content)} {

}

inline int Index::getId() const {
  return this->id;
}

inline time_t Index::getUpdatedTime() const {
  return this->updated;
}

inline const std::string& Index::getUrl() const {
  return this->url;
}

inline const std::string& Index::getTitle() const {
  return this->title;
}

inline const std::string& Index::getDescription() const {
  return this->description;
}

inline const std::string& Index::getContent() const {
  return this->content;
}