#ifndef WEBFRAME_HANDLER_HPP
#define WEBFRAME_HANDLER_HPP

namespace webframe
{
    class request;
    class response;

    class handler
    {
    public:
        void handle_request(const request* req, response* res);
    protected:
        virtual void handle_get(const request* req, response* res);
        virtual void handle_post(const request* req, response* res);
        virtual void handle_put(const request* req, response* res);
        virtual void handle_delete(const request* req, response* res);
    };
}

#endif