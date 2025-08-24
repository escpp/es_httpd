#pragma once
#include <functional>
#include "request.h"
#include "response.h"

namespace es_httpd
{
    namespace rest
    {
        using Handler = std::function<int(Request &, Response &)>;

        template<typename RequestPtr, typename ResponsePtr>
        int exec_handler(Handler handler, RequestPtr rq, ResponsePtr rs)
        {
            rest::Request request(rq);
            rest::Response response(rs);
            int ret = handler(request, response);
            if (0 == ret) {
                return response.get_status_code();
            }
            return ret;
        }
    }
}