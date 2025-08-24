#include "es_httpd/server.h"
#include "hv/hlog.h"

using RestRequest = es_httpd::rest::Request;
using RestResponse = es_httpd::rest::Response;
using WebServer = es_httpd::Server;

int main(int argc, char **argv)
{
    const char *static_fs_path = argc > 1 ? argv[1] : "static/";
    const char *static_url_path = "/static/";
    WebServer web_server;


    // 设置静态文件目录,访问http://localhost:8080/static/时自动获取index.html文件
    web_server.set_static(static_url_path, static_fs_path);

    web_server.GET("/hello", [](RestRequest &rq, RestResponse &rs) -> int {
        rs["a"] = "hello";
        rs["b"] = "world";
        return 0;
    });

    web_server.POST("/echo", [](RestRequest &rq, RestResponse &rs) -> int {
        rs["int"] = 123;
        rs["float"] = 3.14;
        rs["string"] = "hello";
        rs["bool"] = true;
        return 0; 
    });

    web_server.GET("/greet/{name}", [](RestRequest &rq, RestResponse &rs) -> int {
        rs["greeting"] = "Hello " + rq["name"];
        return 0; 
    });

    // mkdir("log", 0755);
    hlog_set_file("/tmp/es_httpd.log");
    web_server.set_thread_num(8);
    web_server.set_max_connections(32);
    web_server.run_sync("0.0.0.0:8080");
    return 0;
}
