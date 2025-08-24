# es_httpd - C++ HTTP服务器框架

es_httpd是一个基于[hv](https://github.com/ithewei/libhv)库的轻量级C++ HTTP服务器框架，提供了简洁的RESTful API接口，便于快速开发Web服务和API。

## 特性

- 🚀 简洁易用的API设计
- 📦 内置JSON响应支持
- 🔧 灵活的配置选项
- 🛣️ 支持RESTful路由
- 📁 静态文件服务支持
- 🧵 多线程处理能力

## 快速开始

### 基本示例

```cpp
#include "es_httpd/server.h"
#include "hv/hlog.h"

using RestRequest = es_httpd::rest::Request;
using RestResponse = es_httpd::rest::Response;
using WebServer = es_httpd::Server;

int main()
{
    WebServer web_server;

    // 设置静态文件服务
    web_server.set_static("/static/", "static/");

    // 注册GET路由
    web_server.GET("/hello", [](RestRequest &rq, RestResponse &rs) -> int {
        rs["message"] = "Hello World";
        return 0;
    });

    // 启动服务器
    web_server.run_sync("0.0.0.0:8080");
    return 0;
}
```

## 核心接口说明

### Server类

`es_httpd::Server` 类是主要的服务器接口，位于 `include/es_httpd/server.h`。

#### 构造函数
```cpp
Server(void);  // 创建服务器实例
```

#### 服务器配置方法

##### set_thread_num
```cpp
void set_thread_num(uint32_t thread_num = 2);
```
设置工作线程数，建议设置为CPU核心数以获得最佳性能。

##### set_max_connections
```cpp
void set_max_connections(uint32_t max_connections = 32);
```
设置最大连接数，默认32，最大不超过65535。

##### set_static
```cpp
bool set_static(const std::string &url_path, const std::string &fs_path);
```
设置静态文件目录：
- `url_path`: URL访问路径（如 "/static/"）
- `fs_path`: 文件系统路径（如 "static/"）

#### 服务器控制方法

##### run_async
```cpp
bool run_async(const std::string &ip_port = "0.0.0.0:8080");
```
非阻塞方式启动服务器，立即返回。

##### run_sync
```cpp
bool run_sync(const std::string &ip_port = "0.0.0.0:8080");
```
阻塞方式启动服务器，直到服务器停止。

##### stop
```cpp
bool stop(void);
```
停止服务器运行。

#### 路由注册方法

##### GET
```cpp
void GET(const std::string &path, rest::Handler handler);
```
注册GET请求处理程序。

##### POST
```cpp
void POST(const std::string &path, rest::Handler handler);
```
注册POST请求处理程序。

## 路由回调机制

### Handler函数签名

路由处理程序使用以下签名：
```cpp
std::function<int(Request &, Response &)>
```

- **返回值**: 整数状态码，0表示成功，非0表示错误
- **参数1**: `Request &` - HTTP请求对象
- **参数2**: `Response &` - HTTP响应对象

### 路由示例

#### 基本路由
```cpp
web_server.GET("/api/users", [](RestRequest &rq, RestResponse &rs) -> int {
    rs["users"] = {"user1", "user2", "user3"};
    return 0;
});
```

#### 路径参数路由
```cpp
web_server.GET("/user/{id}", [](RestRequest &rq, RestResponse &rs) -> int {
    std::string userId = rq["id"];  // 获取路径参数
    rs["user_id"] = userId;
    rs["name"] = "User " + userId;
    return 0;
});
```

#### POST请求处理
```cpp
web_server.POST("/api/data", [](RestRequest &rq, RestResponse &rs) -> int {
    // 处理POST数据
    rs["status"] = "success";
    rs["received"] = true;
    return 0;
});
```

## 请求处理

### Request类

位于 `include/es_httpd/rest/request.h`，用于访问请求参数。

#### 获取参数
```cpp
// 获取查询参数或路径参数
std::string value = rq["param_name"];

// 示例：获取路径参数
web_server.GET("/product/{category}/{id}", [](RestRequest &rq, RestResponse &rs) -> int {
    std::string category = rq["category"];
    std::string id = rq["id"];
    // ... 处理逻辑
    return 0;
});
```

## 响应构建

### Response类

位于 `include/es_httpd/rest/response.h`，用于构建JSON响应。

#### 设置响应数据
```cpp
// 使用下标操作符
rs["key"] = value;

// 使用set方法
rs.set("key", value);

// 支持的数据类型
rs["string"] = "hello";      // 字符串
rs["number"] = 42;           // 整数
rs["float"] = 3.14;          // 浮点数
rs["boolean"] = true;        // 布尔值
rs["array"] = {1, 2, 3};     // 数组
rs["object"] = {{"key", "value"}}; // 对象
```

#### 完整响应示例
```cpp
web_server.GET("/api/profile", [](RestRequest &rq, RestResponse &rs) -> int {
    rs["user"] = {
        {"id", 123},
        {"name", "John Doe"},
        {"email", "john@example.com"},
        {"active", true},
        {"roles", {"admin", "user"}}
    };
    rs["timestamp"] = "2024-01-01T00:00:00Z";
    return 0;
});
```

## 配置选项

### 日志配置
```cpp
#include "hv/hlog.h"

// 设置日志文件
hlog_set_file("/tmp/es_httpd.log");

// 设置日志级别
hlog_set_level(LOG_LEVEL_DEBUG);
```

### 服务器配置示例
```cpp
WebServer web_server;

// 基本配置
web_server.set_thread_num(4);          // 4个工作线程
web_server.set_max_connections(100);   // 最大100个连接

// 静态文件服务
web_server.set_static("/public/", "public/");
web_server.set_static("/assets/", "assets/");

// 启动服务器
web_server.run_sync("0.0.0.0:8080");
```

## 完整示例

```cpp
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

    // 设置静态文件服务
    web_server.set_static(static_url_path, static_fs_path);

    // 简单问候接口
    web_server.GET("/hello", [](RestRequest &rq, RestResponse &rs) -> int {
        rs["greeting"] = "Hello World";
        rs["timestamp"] = "2024-01-01T00:00:00Z";
        return 0;
    });

    // 路径参数示例
    web_server.GET("/greet/{name}", [](RestRequest &rq, RestResponse &rs) -> int {
        rs["message"] = "Hello " + std::string(rq["name"]);
        return 0;
    });

    // POST数据处理
    web_server.POST("/echo", [](RestRequest &rq, RestResponse &rs) -> int {
        rs["received"] = true;
        rs["status"] = "success";
        return 0;
    });

    // 复杂数据响应
    web_server.GET("/api/users", [](RestRequest &rq, RestResponse &rs) -> int {
        rs["users"] = {
            {{"id", 1}, {"name", "Alice"}, {"email", "alice@example.com"}},
            {{"id", 2}, {"name", "Bob"}, {"email", "bob@example.com"}},
            {{"id", 3}, {"name", "Charlie"}, {"email", "charlie@example.com"}}
        };
        return 0;
    });

    // 配置日志
    hlog_set_file("/tmp/es_httpd.log");
    
    // 服务器配置
    web_server.set_thread_num(8);
    web_server.set_max_connections(32);
    
    // 启动服务器
    web_server.run_sync("0.0.0.0:8080");
    
    return 0;
}
```

## 构建说明

### 依赖项
- C++11或更高版本
- [hv](https://github.com/ithewei/libhv)库

### CMake构建x86芯片平台的libes_httpd.so
```bash
make x86
```
### CMake构建STM32MP135芯片平台的libes_httpd.so
```bash
make mp135
```

### 运行示例
```bash
./es_httpd_example
```

### 测试API
```bash
# 测试问候接口
curl http://localhost:8080/hello

# 测试路径参数
curl http://localhost:8080/greet/John

# 测试静态文件
curl http://localhost:8080/static/index.html
```

## 最佳实践

1. **错误处理**: 在Handler中返回适当的HTTP状态码
2. **资源管理**: 合理设置线程数和连接数
3. **日志记录**: 使用hv的日志功能进行调试和监控
4. **异常安全**: 确保Handler不会抛出未捕获的异常

## 故障排除

### 常见问题

1. **端口占用**: 确保8080端口未被其他程序使用
2. **权限问题**: 确保有权限访问日志文件和静态目录
3. **依赖问题**: 确保正确安装并链接hv库

### 调试技巧

```cpp
// 启用详细日志
hlog_set_level(LOG_LEVEL_DEBUG);

// 在Handler中添加日志
web_server.GET("/debug", [](RestRequest &rq, RestResponse &rs) -> int {
    hlogd("Received request to /debug");
    // ... 处理逻辑
    return 0;
});
```

## 许可证

本项目基于MIT许可证开源。

## 贡献

欢迎提交Issue和Pull Request来改进es_httpd框架。
