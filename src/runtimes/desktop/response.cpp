#include <desktop.hpp>

namespace webframe
{
    namespace desktop
    {
        response::response(wxWebViewHandlerResponse *response, bool &sent) : _response(response), _sent(sent)
        {
        }

        void response::set_status(int status)
        {
            _response->SetStatus(status);
        }

        void response::set_header(const std::string &key, const std::string &value)
        {
            _response->SetHeader(key, value);
        }

        void response::set_body(const uint8_t *data, size_t size)
        {
            _response->Finish(std::string(reinterpret_cast<const char *>(data), size));
            _sent = true;
        }

        void response::write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback)
        {
            std::vector<uint8_t> buffer;
            bool has_more_data = true;
            while (has_more_data)
            {
                std::pair<const uint8_t *, size_t> data;
                if (callback(data))
                {
                    buffer.insert(buffer.end(), data.first, data.first + data.second);
                }
                else
                {
                    has_more_data = false;
                }
            }
            set_body(buffer.data(), buffer.size());
        }
    }
}