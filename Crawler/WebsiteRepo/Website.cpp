//
// Created by jora on 3/16/21.
//

#include "Website.hpp"

Website::Website(int id, std::string domain, std::string homepage)
		:id{ id }, domain{ std::move(domain) }, homepage{ std::move(homepage) }, crawled{ 0 }
{

}
