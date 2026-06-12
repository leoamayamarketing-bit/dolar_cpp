#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);

std::string httpGet(const std::string& url, const std::string& apiKey);

std::string getCurrentDate();

#endif
