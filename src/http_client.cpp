#include <iostream>
#include <string>
#include <ctime>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    s->append((char*)contents, newLength);
    return newLength;
}

std::string httpGet(const std::string& url, const std::string& apiKey) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    long http_code = 0;

    curl = curl_easy_init();
    if(curl) {
        struct curl_slist* headers = nullptr;
        std::string authHeader = "Authorization: Bearer " + apiKey;

        headers = curl_slist_append(headers, authHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return "";
        }

        if (http_code != 200) {
            std::cerr << "HTTP request failed with status code: " << http_code << std::endl;
            return "";
        }
    }
    return readBuffer;
}

std::string getCurrentDate() {
    time_t t = time(nullptr);
    tm* timePtr = localtime(&t);

    char date[11];
    snprintf(date, sizeof(date), "%04d-%02d-%02d",
             timePtr->tm_year + 1900,
             timePtr->tm_mon + 1,
             timePtr->tm_mday);

    return std::string(date);
}
