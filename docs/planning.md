# 规划
- 基于libhv库的hv::HttpServer和hv::HttpService实现es_httpd::Server类;
- es_httpd::Server.set_thread_num(uint32_t thread_num = 1)设置线程数;
- es_httpd::Server.set_max_connections(uint32_t max_connections = 32)设置最大连接数;
- es_httpd::Server.set_static(const std::string& url_path, const std::string& fs_path)设置静态文件路径;
- es_httpd::GET(const std::string& url_path, std::function<int(es_httpd::rest::Request&, es_httpd::rest::Response&)> handler)设置GET请求处理函数;
- es_httpd::POST(const std::string& url_path, std::function<int(es_httpd::rest::Request&, es_httpd::rest::Response&)> handler)设置POST请求处理函数;
- es_httpd::Server.run_sync(const std::string &ip_port = "0.0.0.0:8080")同步运行;
- es_httpd::Server.run_async(const std::string &ip_port = "0.0.0.0:8080")异步运行;
- es_httpd::Server.stop()停止运行;

- es_httpd::rest::Request类包含请求信息, 实现const hv::Json &operator[](const std::string& key)获取请求参数;
- es_httpd::rest::Response类包含响应信息, 实现void set_status_code(int status)设置响应状态码, hv::Json& operator[](const std::string& key)设置响应参数;
