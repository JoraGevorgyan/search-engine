//
// Created by jora on 3/12/21.
//

#include "PageLoader.hpp"

Page PageLoader::load(const std::string &url) {
    curlpp::Easy request; // for sending a request into given url
    curlpp::Cleanup cleaner; // will clean up when destructor has been called

    request.setOpt(curlpp::Options::Url(url));
    request.setOpt(curlpp::Options::FollowLocation(true)); // trying to find correct location

    std::ostringstream os; // for saving info in this stream
    curlpp::options::WriteStream ws(&os); // make option for writing into 'os' stream
    request.setOpt(ws); // change default write stream as 'os'
    request.perform();

    std::string effUrl;
    curlpp::infos::EffectiveUrl::get(request, effUrl); // write found effective url into effectiveurl

    return Page(effUrl, os.str(), curlpp::infos::ResponseCode::get(request));
}