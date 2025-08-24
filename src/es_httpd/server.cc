#include "es_httpd/server.h"
#include <iostream>

namespace es_httpd
{

    Server::Server(void)
    {
        m_server.registerHttpService(&m_service);
        set_thread_num();
        set_max_connections();
    }

    void Server::set_thread_num(uint32_t thread_num)
    {
        if (thread_num < 1) {
            
        }
        m_server.setThreadNum(thread_num);
    }

    void Server::set_max_connections(uint32_t max_connections)
    {
        if (max_connections < 1) {
            max_connections = 1;
        }
        m_server.setMaxWorkerConnectionNum(max_connections);
    }

    bool Server::set_static(const std::string &url_path = "/", const std::string &fs_path = ".")
    {
        if (url_path.empty() || fs_path.empty())
        {
            std::cout << "Server set_static invalid param " << std::endl;
            return false;
        }

        m_service.Static(url_path.c_str(), fs_path.c_str());
        return true;
    }

    bool Server::run_sync(const std::string &ip_port)
    {
        if (ip_port.empty()) {
            std::cout << "Server run_sync invalid param " << std::endl;
            return false;
        }

        std::cout << "Server running at http://" << ip_port << std::endl;
        int ret = m_server.run(ip_port.c_str(), true);
        if (ret != 0) {
            std::cout << "Server failed to run at http://" << ip_port << std::endl;
            return false;
        }

        return true;
    }

    bool Server::run_async(const std::string &ip_port)
    {
        if (ip_port.empty()) {
            std::cout << "Server run_async invalid param " << std::endl;
            return false;
        }

        int ret = m_server.run(ip_port.c_str(), false);
        if (ret != 0) {
            std::cout << "Server failed to run at http://" << ip_port << std::endl;
            return false;
        }

        std::cout << "Server running at http://" << ip_port << std::endl;
        return true;
    }

    bool Server::stop(void)
    {
        int ret = m_server.stop();
        if (ret != 0) {
            std::cout << "Server failed to stop" << std::endl;
            return false;
        }

        std::cout << "Server stopped" << std::endl;
        return true;
    }
};