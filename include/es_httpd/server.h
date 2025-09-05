#pragma once

#include "hv/HttpServer.h"
#include "hv/HttpService.h"
#include "rest/handler.h"

namespace es_httpd
{

    class Server
    {
    public:
        Server(void);
        ~Server(void) = default;

        /**
         * @brief 设置工作线程数,设置与cpu核心数相同可发挥多核优势
         * @param thread_num 线程数2
         */
        void set_thread_num(uint32_t thread_num = 2);

        /**
         * @brief 设置最大连接数，默认64，内存大可以设置大一些，最大不超过65535
         * @param max_connection_num 最大连接数
         */
        void set_max_connections(uint32_t max_connections = 32);

        /**
         * @brief 设置静态文件目录
         * @param url_path url路径
         * @param fs_path 文件系统路径
         * @retval true 设置成功, false 设置失败
         */
        bool set_static(const std::string &url_path, const std::string &fs_path);

        /**
         * @brief 非阻塞方式启动web服务器
         * @param ip_port 监听地址和端口, 默认0.0.0.0:8080
         * @return true 成功, false 失败
         */
        bool run_async(const std::string &ip_port = "0.0.0.0:8080");

        /**
         * @brief 阻塞方式启动web服务器
         * @param ip_port 监听地址和端口, 默认0.0.0.0:8080
         * @return true 成功, false 失败
         */
        bool run_sync(const std::string &ip_port = "0.0.0.0:8080");

        /**
         * @brief 停止服务器
         * @return true 成功, false 失败
         */
        bool stop(void);

        void GET(const std::string &path, rest::Handler handler)
        {
            m_service.GET(path.c_str(), [handler](HttpRequest *req, HttpResponse *resp) -> int {
                return rest::exec_handler(handler, req, resp);
            });
        }

        void POST(const std::string &path, rest::Handler handler)
        {
            m_service.POST(path.c_str(), [handler](HttpRequest *req, HttpResponse *resp) -> int {
                return rest::exec_handler(handler, req, resp);
            });
        }

        void PUT(const std::string &path, rest::Handler handler)
        {
            m_service.PUT(path.c_str(), [handler](HttpRequest *req, HttpResponse *resp) -> int {
                return rest::exec_handler(handler, req, resp);
            });
        }

        void PATCH(const std::string &path, rest::Handler handler)
        {
            m_service.PATCH(path.c_str(), [handler](HttpRequest *req, HttpResponse *resp) -> int {
                return rest::exec_handler(handler, req, resp);
            });
        }

        void DELETE(const std::string &path, rest::Handler handler)
        {
            m_service.Delete(path.c_str(), [handler](HttpRequest *req, HttpResponse *resp) -> int {
                return rest::exec_handler(handler, req, resp);
            });
        }

    private:
        hv::HttpServer m_server;
        hv::HttpService m_service;
    };
}
