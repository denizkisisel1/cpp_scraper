#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include <chrono>
#include <thread>

const std::string url = "https://example.com";
const std::string textToSearch = "TextToSearchFor";
const std::string outputFileName = "findings.txt";

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

void fetchAndWriteResults() {
    CURL* curl;
    CURLcode res;

    std::string response_data;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            std::ofstream outfile(outputFileName, std::ios::app);
            if (outfile.is_open()) {
                if (response_data.find(textToSearch) != std::string::npos) {
                    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                    outfile << "Text found at " << std::ctime(&now);
                }
                outfile.close();
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

int main() {
    while (true) {
        fetchAndWriteResults();
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
