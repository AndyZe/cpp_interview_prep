#include <curl/curl.h>
#include <algorithm>
#include <cctype>
#include <charconv>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

// Retrieve the chars from a google doc and print them, in grid format

// libcurl calls this for each chunk of data received.
static size_t write_cb(char* ptr, size_t size, size_t nmemb, void* userdata) {
    auto* out = static_cast<std::string*>(userdata);
    out->append(ptr, size * nmemb);
    // tell curl we consumed everything
    return size * nmemb;
}

class CurlSender
{
public:
  CurlSender()
  {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_ = curl_easy_init();
    if (!curl_) {
      // the destructor won't run, so undo curl_global_init here
      curl_global_cleanup();
      throw std::runtime_error("curl_easy_init failed");
    }

    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);   // follow redirects
    curl_easy_setopt(curl_, CURLOPT_TIMEOUT, 10L);         // seconds
    curl_easy_setopt(curl_, CURLOPT_USERAGENT, "libcurl-example/1.0");
  }

  // REST GET request. Returns the response body.
  // Throws std::runtime_error on a transport error or a non-2xx status.
  std::string sendGETRequest(const std::string& url)
  {
    std::string response;
    curl_easy_setopt(curl_, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl_);
    if (res != CURLE_OK) {
      throw std::runtime_error(std::string("GET request failed: ") + curl_easy_strerror(res));
    }

    long status = 0;
    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &status);
    if (status < 200 || status >= 300) {
      throw std::runtime_error("GET request returned HTTP " + std::to_string(status));
    }
    return response;
  }

  ~CurlSender()
  {
    curl_easy_cleanup(curl_);
    curl_global_cleanup();
  }

  // Delete the copy constructor so we don't copy CURL* to another object
  CurlSender(const CurlSender&) = delete;

  // Delete the copy assignment operator so we don't copy CURL* to another object
  CurlSender& operator=(const CurlSender&) = delete;

private:
  CURL* curl_;
};

// One row of the doc's table: a character and where to draw it.
struct GridChar
{
  int x;
  int y;
  std::string ch;  // std::string, not char: glyphs like █ are multi-byte UTF-8
};

// Strip HTML tags and decode the entities Google Docs uses to escape text.
static std::string htmlToText(std::string_view html)
{
  static constexpr std::pair<std::string_view, std::string_view> entities[] = {
    {"&amp;", "&"}, {"&lt;", "<"}, {"&gt;", ">"}, {"&quot;", "\""}, {"&#39;", "'"}};

  std::string out;
  for (size_t i = 0; i < html.size(); ++i) {
    if (html[i] == '<') {
      size_t end = html.find('>', i);
      if (end == std::string_view::npos) break;
      i = end;
      continue;
    }
    if (html[i] == '&') {
      auto it = std::find_if(std::begin(entities), std::end(entities),
                             [&](const auto& e) { return html.substr(i).starts_with(e.first); });
      if (it != std::end(entities)) {
        out += it->second;
        i += it->first.size() - 1;
        continue;
      }
    }
    out += html[i];
  }
  return out;
}

static std::optional<int> parseInt(std::string_view s)
{
  while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front()))) s.remove_prefix(1);
  while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) s.remove_suffix(1);

  int value = 0;
  auto [end, ec] = std::from_chars(s.data(), s.data() + s.size(), value);
  if (ec != std::errc{} || end != s.data() + s.size()) {
    return std::nullopt;
  }
  return value;
}

// Return the text of each <td> in one table row.
static std::vector<std::string> rowCells(std::string_view row)
{
  std::vector<std::string> cells;
  size_t pos = 0;
  while ((pos = row.find("<td", pos)) != std::string_view::npos) {
    size_t content_start = row.find('>', pos);
    if (content_start == std::string_view::npos) break;
    size_t content_end = row.find("</td>", content_start);
    if (content_end == std::string_view::npos) break;
    cells.push_back(htmlToText(row.substr(content_start + 1, content_end - content_start - 1)));
    pos = content_end;
  }
  return cells;
}

// Read the (x-coordinate, character, y-coordinate) rows from the first <table> in the page.
// Rows whose coordinates aren't integers, like the header row, are skipped.
static std::vector<GridChar> parseTable(std::string_view html)
{
  size_t table_start = html.find("<table");
  size_t table_end = html.find("</table>", table_start);
  if (table_start == std::string_view::npos || table_end == std::string_view::npos) {
    throw std::runtime_error("No <table> found in the document");
  }
  std::string_view table = html.substr(table_start, table_end - table_start);

  std::vector<GridChar> chars;
  size_t pos = 0;
  while ((pos = table.find("<tr", pos)) != std::string_view::npos) {
    size_t row_end = table.find("</tr>", pos);
    if (row_end == std::string_view::npos) break;
    std::vector<std::string> cells = rowCells(table.substr(pos, row_end - pos));
    pos = row_end;

    if (cells.size() != 3) continue;
    std::optional<int> x = parseInt(cells[0]);
    std::optional<int> y = parseInt(cells[2]);
    if (!x || !y) continue;
    chars.push_back({*x, *y, cells[1]});
  }
  return chars;
}

// Print the characters in a grid, with spaces in empty positions.
// y increases upward, so the largest y is the top row.
static void printGrid(const std::vector<GridChar>& chars)
{
  if (chars.empty()) return;

  int max_x = 0;
  int max_y = 0;
  for (const GridChar& c : chars) {
    if (c.x < 0 || c.y < 0) {
      throw std::runtime_error("Negative coordinate in the document");
    }
    max_x = std::max(max_x, c.x);
    max_y = std::max(max_y, c.y);
  }

  // grid[y][x]
  std::vector<std::vector<std::string>> grid(max_y + 1, std::vector<std::string>(max_x + 1, " "));
  for (const GridChar& c : chars) {
    grid[c.y][c.x] = c.ch;
  }

  for (int y = max_y; y >= 0; --y) {
    for (const std::string& cell : grid[y]) {
      std::cout << cell;
    }
    std::cout << '\n';
  }
}

int main()
{
  const std::string url = "https://docs.google.com/document/d/e/2PACX-1vTMOmshQe8YvaRXi6gEPKKlsC6UpFJSMAk4mQjLm_u1gmHdVVTaeh7nBNFBRlui0sTZ-snGwZM4DBCT/pub";
  try {
    CurlSender curl_rest;
    std::string html = curl_rest.sendGETRequest(url);
    printGrid(parseTable(html));
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::cout << "It's expected now to get a libcurl memory leak warning. That's libcurl, not this program." << std::endl;
  return 0;
}
