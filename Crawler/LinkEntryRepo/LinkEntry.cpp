//
// Created by jora on 3/16/21.
//

#include "LinkEntry.hpp"

LinkEntry::LinkEntry(std::string url, std::string domain, LinkStatus status, time_t updated)
		:url{ std::move(url) },
		 domain{ std::move(domain) },
		 status{ status },
		 updated{ updated }
{
}