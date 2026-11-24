#include <curl/curl.h>
#include <iostream>
#include <stdexcept>
#include <string>

// Convert this curl example to RAII. It retrieves a small amount of html from example.com
// It's a bit trivial here because `main` exits right away, but pretend it's a larger program with
// multiple exit paths that would all need to call curl_global_cleanup()

// libcurl calls this for each chunk of data received.
static size_t write_cb(char* ptr, size_t size, size_t nmemb, void* userdata) {
    auto* out = static_cast<std::string*>(userdata);
    out->append(ptr, size * nmemb);
    return size * nmemb;  // tell curl we consumed everything
}

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

class CurlReader
{
public:
  CurlReader()
  {
    const char* url = "https://example.com";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_ = curl_easy_init();
    if (!curl_) {
      // the destructor won't run, so undo curl_global_init here
      curl_global_cleanup();
      throw std::runtime_error("curl_easy_init failed");
    }

    curl_easy_setopt(curl_, CURLOPT_URL, url);
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &data_);
    curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);   // follow redirects
    curl_easy_setopt(curl_, CURLOPT_TIMEOUT, 10L);         // seconds
    curl_easy_setopt(curl_, CURLOPT_USERAGENT, "libcurl-example/1.0");
  }

  std::string readUrl()
  {
    CURLcode res = curl_easy_perform(curl_);
    if (res != CURLE_OK) {
        std::cerr << "Request failed: " << curl_easy_strerror(res) << '\n';
        return "";
    } else {
        long status = 0;
        curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &status);
    }
    return data_;
  }

  ~CurlReader()
  {
    curl_easy_cleanup(curl_);
    curl_global_cleanup();
  }

  // Delete the copy constructor so we don't copy CURL* to another object
  CurlReader(const CurlReader&) = delete;

  // Delete the copy assignment operator so we don't copy CURL* to another object
  CurlReader& operator=(const CurlReader&) = delete;

private:
  CURL* curl_;
  std::string data_;
};

int main()
{
  try {
    CurlReader curl_reader;
    std::cout << curl_reader.readUrl() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::cout << "It's expected now to get a libcurl memory leak warning. That's libcurl, not this program." << std::endl;
  return 0;
}