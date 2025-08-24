#pragma once
#include "hv/HttpMessage.h"

namespace es_httpd {
namespace rest {
    
    class Request
    {
    public:
        Request(void) = delete;
        Request(HttpRequest *request) : m_request(request) {}

        const std::string operator[](const char *key)
        {
            if (nullptr == m_request) {
                return hv::empty_string;
            }
            return m_request->GetParam(key);
        }

        const hv::QueryParams& params(void) const 
        {
            if (nullptr == m_request) {
                static hv::QueryParams empty_params;
                return empty_params;
            }
            return m_request->query_params;
        }

        const http_headers& headers(void) const
        {
            if (nullptr == m_request) {
                static http_headers empty_headers;
                return empty_headers;
            }
            return m_request->headers;
        }

        const http_cookies& cookies(void) const
        {
            if (nullptr == m_request) {
                static http_cookies empty_cookies;
                return empty_cookies;
            }
            return m_request->cookies;
        }

        const hv::Json& body(void) const
        {
            if (nullptr == m_request) {
                static hv::Json empty_json;
                return empty_json;
            }
            m_request->GetJson();
            return m_request->json;
        }

        bool save_file(const char *path)
        {
            if (nullptr == m_request || nullptr == path) {
                return false;
            }
            return m_request->SaveFile(path);
        }

    private:
        HttpRequest *m_request = nullptr;
    };
}
}