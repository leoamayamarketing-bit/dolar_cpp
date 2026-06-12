#include <iostream>
#include <string>
#include "json.hpp"
#include "http_client.h"

using json = nlohmann::json;

int main() {
    std::string api_key = "eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE3NDgxNDAxNDMsInR5cGUiOiJleHRlcm5hbCIsInVzZXIiOiJjdWFAeWFob28uY29tIn0.hDq50dmAKU9BUkvHOie_xLg4VO6t8b3il2NavFk0X6yPvOr_fqJ32RXlCV70nf6pTcPUPumma5wVeARooID51g";
    std::string api_url = "https://api.estadisticasbcra.com/usd_of?";
    std::string date = "2024-05-04";

    std::cout << "date : " << date << std::endl;

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
