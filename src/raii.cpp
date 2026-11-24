#include <curl/curl.h>
#include <iostream>
#include <string>

// Convert this curl example to RAII. It retrieves a small amount of html from example.com

// // libcurl calls this for each chunk of data received.
// static size_t write_cb(char* ptr, size_t size, size_t nmemb, void* userdata) {
//     auto* out = static_cast<std::string*>(userdata);
//     out->append(ptr, size * nmemb);
//     return size * nmemb;  // tell curl we consumed everything
// }

// int main() {
//     const char* url = "https://example.com";

//     curl_global_init(CURL_GLOBAL_DEFAULT);
//     CURL* curl = curl_easy_init();
//     if (!curl) {
//         std::cerr << "curl_easy_init failed\n";
//         return 1;
//     }

//     std::string body;
//     curl_easy_setopt(curl, CURLOPT_URL, url);
//     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
//     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
//     curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);   // follow redirects
//     curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);         // seconds
//     curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-example/1.0");

//     CURLcode res = curl_easy_perform(curl);
//     if (res != CURLE_OK) {
//         std::cerr << "Request failed: " << curl_easy_strerror(res) << '\n';
//     } else {
//         long status = 0;
//         curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
//         std::cout << "HTTP " << status << ", " << body.size() << " bytes\n\n"
//                   << body << '\n';
//     }

//     curl_easy_cleanup(curl);
//     curl_global_cleanup();
//     return res == CURLE_OK ? 0 : 1;
// }

int main()
{
  return 0;
}