#include <iostream>
#include <string>
#include <ctime>
#include <curl/curl.h>
#include "json.hpp" // Asegúrate de que la biblioteca nlohmann/json esté disponible

using json = nlohmann::json;

// Callback para escribir la respuesta de curl en un std::string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    s->append((char*)contents, newLength);
    return newLength;
}

// Función para realizar la solicitud HTTP
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

// Función para obtener la fecha actual en formato YYYY-MM-DD
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

int main() {
    //std::string api_key = "eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE3NDgxMzUyNjgsInR5cGUiOiJleHRlcm5hbCIsInVzZXIiOiJ0cmVzQHlhaG9vLmNvbSJ9.W6kvNogai9cF1yOK0DRQkbp1RkEHiqbGAQq3VnG7JRI0bd8YLEZ-gnYclVd2Q3dz9HUEUM_B9Td8W1-2lA_jwA";
 std::string api_key = "eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE3NDgxNDAxNDMsInR5cGUiOiJleHRlcm5hbCIsInVzZXIiOiJjdWFAeWFob28uY29tIn0.hDq50dmAKU9BUkvHOie_xLg4VO6t8b3il2NavFk0X6yPvOr_fqJ32RXlCV70nf6pTcPUPumma5wVeARooID51g"
  ;
  std::string api_url = "https://api.estadisticasbcra.com/usd_of?";

    std::string date = "2024-05-04";//getCurrentDate();

std::cout<<"date : "<< date  <<std::endl;

    std::string response = httpGet(api_url, api_key);

    if (response.empty()) {
        std::cerr << "Empty response for date: " << date << std::endl;
        return 1;
    }

    try {
        auto jsonData = json::parse(response);

        bool found = false;
        for (auto& entry : jsonData) {
            if (entry["d"] == date) {
                std::cout << "Fecha: " << date << ", Valor: " << entry["v"] << std::endl;
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "No hay datos disponibles para la fecha: " << date << std::endl;
        }
    } catch (json::parse_error& e) {
        std::cerr << "Error parsing JSON for date " << date << ": " << e.what() << std::endl;
        std::cerr << "Response was: " << response << std::endl;
        return 1;
    }

    return 0;
}
