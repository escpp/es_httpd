#pragma once
#include "hv/HttpMessage.h"

namespace es_httpd {
namespace rest {
    
    class Response
    {
    public:
        Response(void) = delete;
        Response(HttpResponse *response) : m_response(response) {
            if (nullptr == m_response) {
                return;
            }
            m_response->content_type = APPLICATION_JSON;
            m_response->status_code = HTTP_STATUS_OK;
        }

        bool set_json(hv::Json &json)
        {
            if (nullptr == m_response) {
                return false;
            }
            m_response->json = json;
            return true;
        }

        bool set_body(const std::string &body)
        {
            if (nullptr == m_response) {
                return false;
            }
            m_response->body = body;
            return true;
        }
  
        hv::Json& operator[](const std::string &key)
        {
            if (nullptr == m_response || key.empty()) {
                static hv::Json empty_json;
                empty_json.clear();
                return empty_json;
            }
            return m_response->json[key];
        }

        int get_status_code(void)
        {
            if (nullptr == m_response) {
                return 500;
            }
            return m_response->status_code;
        }

        bool load_file(const char *path)
        {
            if (nullptr == m_response || nullptr == path) {
                return false;
            }
            
            hv::Json j;
            int ret = m_response->File(path);
            if (200 != ret) {
                j["code"] = ret;
                j["msg"] = std::string("failed to load file ") + path;
                j["data"] = hv::Json();
                m_response->Json(j);
                return false;
            }
            
            j["code"] = 0;
            j["msg"] = "success";
            j["data"] = hv::Json::parse(m_response->body);
            m_response->Json(j);
            std::cout << m_response->body << std::endl;
            return true;
        }

    private:
        HttpResponse *m_response = nullptr;
    };
}
}