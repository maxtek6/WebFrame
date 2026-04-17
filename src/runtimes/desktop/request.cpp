#include <desktop.hpp>

namespace webframe
{
    namespace desktop
    {
        request::request(const wxWebViewHandlerRequest *request) : _request(request)
        {
            _body = _request->GetDataString();
        }

        webframe::method request::get_method() const
        {
            const wxString method = _request->GetMethod();
            webframe::method result;
            if (method == "GET")
            {
                result = webframe::method::http_get;
            }
            else if (method == "POST")
            {
                result = webframe::method::http_post;
            }
            else if (method == "PUT")
            {
                result = webframe::method::http_put;
            }
            else if (method == "DELETE")
            {
                result = webframe::method::http_delete;
            }
            else
            {
                result = static_cast<webframe::method>(-1);
            }
            return result;
        }

        std::string request::get_path() const
        {   
            wxURI uri = _request->GetURI();
            wxString uri_path = uri.GetPath();
            if (!uri_path.StartsWith("/"))
            {
                uri_path.Prepend("/");
            }
            return std::string(uri_path.ToStdString());
        }

        std::string request::get_uri() const
        {
            return _request->GetURI().ToStdString();
        }

        bool request::get_header(const std::string &key, std::string &value) const
        {
            wxString header_value = _request->GetHeader(key);
            bool result(false);
            if (!header_value.empty())
            {
                value = std::string(header_value.ToStdString());
                result = true;
            }
            return result;
        }

        std::pair<const uint8_t *, size_t> request::get_body() const
        {
            const uint8_t *data = reinterpret_cast<const uint8_t *>(_body.GetData().AsCharBuf().data());
            size_t size = _body.size();
            return { data, size };
        }

        void request::read_body(const std::function<void(const uint8_t *, size_t)> &callback) const
        {
            const auto& [data, size] = get_body();
            callback(data, size);
        }
    }
}