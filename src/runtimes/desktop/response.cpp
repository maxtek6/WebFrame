#include <desktop.hpp>

class response_body_writer : public wxWebViewHandlerResponseData
{
public:
    response_body_writer() = default;
    ~response_body_writer() = default;

    wxInputStream *GetStream() override
    {
        if (!_stream)
        {
            _stream = std::make_unique<wxMemoryInputStream>(_buffer.data(), _buffer.size());
        }
        return _stream.get();
    }

    void write(const uint8_t *data, size_t size)
    {
        _buffer.insert(_buffer.end(), data, data + size);
    }

private:
    std::vector<uint8_t> _buffer;
    std::unique_ptr<wxMemoryInputStream> _stream;
};


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
            std::unique_ptr<response_body_writer> body_writer = std::make_unique<response_body_writer>();
            body_writer->write(data, size);
            _response->Finish(wxSharedPtr<wxWebViewHandlerResponseData>(body_writer.release()));
            _sent = true;
        }

        void response::write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback)
        {
            std::unique_ptr<response_body_writer> body_writer = std::make_unique<response_body_writer>();
            bool has_more(true);
            while(has_more)
            {
                std::pair<const uint8_t *, size_t> data;
                has_more = callback(data);
                if (data.first && data.second)
                {
                    body_writer->write(data.first, data.second);
                }
            }
            _response->Finish(wxSharedPtr<wxWebViewHandlerResponseData>(body_writer.release()));
            _sent = true;    
        }
    }
}