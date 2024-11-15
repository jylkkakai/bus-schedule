#ifndef QUERY_H_
#define QUERY_H_

#include <curl/curl.h>
#include <string>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp);
std::string url_query(std::string url);
#endif // QUERY_H_
