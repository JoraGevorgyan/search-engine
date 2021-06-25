#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include "ConsoleUI.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::client;

json::value ask(http_client& client, const json::value& content, const method& m = methods::GET)
{
    client.request(m, "", content)
            .then([](const http_response& response) {
                if (response.status_code() == status_codes::OK) {
                    response.extract_json();
                }
                return pplx::task_from_result(json::value());
            })
            .then([](const pplx::task<json::value>& prevTask) {
                return prevTask.get();
            }).wait();
    ui::ConsoleUI u{};
    u.showMsg("Something went wrong, there's no answer from server :(", true);
    return json::value::string("");
}

int main()
{
    utility::string_t address = U("http://localhost");
    uri_builder uri(address);
    address = uri.to_uri().to_string();
    http_client client(address, http_client_config());

    ui::ConsoleUI ui{};
    ui.showMsg("We are ready for You.");
    while (true) {
        const auto results = ask(client, json::value::string(ui.askForSearch()));
        ui.showSearchResult(results);
    }
}
