#include <test.hpp>

namespace webframe::test
{
    webframe::method request::get_method() const
    {
        return method;
    }

    std::string request::get_path() const
    {
        return path;
    }

    bool request::get_header(const std::string &key, std::string &value) const
    {
        auto it = headers.find(key);
        if (it == headers.end())
        {
            return false;
        }
        value = it->second;
        return true;
    }

    std::pair<const uint8_t *, size_t> request::get_body() const
    {
        return { body.data(), body.size() };
    }

    void request::read_body(const std::function<void(const uint8_t *, size_t)> &callback) const
    {
        callback(body.data(), body.size());
    }

    void response::set_status(int status)
    {
        status_code = status;
    }

    void response::set_header(const std::string &key, const std::string &value)
    {
        headers[key] = value;
    }

    void response::set_body(const uint8_t *data, size_t size)
    {
        body.assign(data, data + size);
    }

    void response::write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback)
    {
        bool has_more = true;
        while (has_more)
        {
            std::pair<const uint8_t *, size_t> chunk;
            has_more = callback(chunk);
            if(chunk.first && chunk.second > 0)
            {
                body.insert(body.end(), chunk.first, chunk.first + chunk.second);
            }
        }
        
    }
}