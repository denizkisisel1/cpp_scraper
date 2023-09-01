#include <iostream>
#include <string>
#include <curl/curl.h>

// Callback function to write the received data into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

int main() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        const char* url = "https://example.com/login";

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POST, 1);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "username=your_username&password=your_password");

        std::string response_data;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Error performing request: " << curl_easy_strerror(res) << std::endl;
        } else {
            if (response_data.find("TextToSearchFor") != std::string::npos) {
                std::cout << "Text found!" << std::endl;
            } else {
                std::cout << "Text not found." << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Error initializing libcurl." << std::endl;
    }

    curl_global_cleanup();

    return 0;
}
