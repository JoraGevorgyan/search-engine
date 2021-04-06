//
// Created by jora on 4/6/21.
//

#ifndef CRAWLER_INDEXREPOSITORY_INDEX_HPP_
#define CRAWLER_INDEXREPOSITORY_INDEX_HPP_

#include <ctime>
#include <string>

class Index {
 private:
  int id;
  time_t updated;
  std::string url;
  std::string title;
  std::string description;
  std::string content;

 public:
  Index(int id, std::string url, std::string title, std::string description, std::string content);

  inline int getId() const;
  inline time_t getUpdatedTime() const;
  inline const std::string& getUrl() const;
  inline const std::string& getTitle() const;
  inline const std::string& getDescription() const;
  inline const std::string& getContent() const;

};

#endif //CRAWLER_INDEXREPOSITORY_INDEX_HPP_
