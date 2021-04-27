//
// Created by jora on 3/16/21.
//

#include "Website.hpp"

Website::Website(int id, std::string domain, std::string homepage, WebsiteStatus status, time_t crawled)
		:id{ id }, domain{ std::move(domain) }, homepage{ std::move(homepage) }, status{ status }, crawled{ crawled }
{

}