//
// Created by jora on 5/11/21.
//

#include "Connector.hpp"
#include "Search.hpp"

#define MAX_RESULT_COUNT 14

int main()
{
	auto connection = Connector();
	while (true) {
		if (connection.gotRequest()) {
			auto result = Search::find(cone)
		}
	}
	return 0;
}