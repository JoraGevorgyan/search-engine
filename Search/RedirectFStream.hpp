//
// Created by jora on 5/15/21.
//

#ifndef CRAWLER_REDIRECTFSTREAM_HPP
#define CRAWLER_REDIRECTFSTREAM_HPP

#include <iostream>
#include <fstream>

class RedirectFStream {
private:
	std::FILE* stream;

public:
	RedirectFStream(const std::string& newFilePath, std::FILE* stream);

	~RedirectFStream();
};

RedirectFStream::RedirectFStream(const std::string& newFilePath, std::FILE* stream)
		: stream(stream)
{
	bool success = std::freopen(newFilePath.c_str(), "w", stream);
	if (!success) {
		std::cerr << "Permission denied to create log files!\n";
		exit(1);
	}
}

RedirectFStream::~RedirectFStream()
{
	std::fclose(this->stream);
}

#endif //CRAWLER_REDIRECTFSTREAM_HPP
