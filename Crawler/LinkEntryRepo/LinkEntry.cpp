//
// Created by jora on 3/16/21.
//

#include "LinkEntry.hpp"

LinkEntry::LinkEntry(int id, int websiteId, std::string url, LinkStatus status, time_t updated)
		:id{ id },
		 websiteId{ websiteId },
		 url{ std::move(url) },
		 status{ status },
		 updated{ updated }
{
}