#include <webframe.hpp>

namespace webframe
{
    uri::uri(const std::string &str)
    {
        parse(str);
    }

    std::string uri::get_scheme() const
    {
        return _scheme;
    }

    std::string uri::get_host() const
    {
        return _host;
    }

    int uri::get_port() const
    {
        return _port;
    }

    std::string uri::get_path() const
    {
        return _path;
    }

    bool uri::get_query(const std::string &key, std::string &value) const
    {
        auto it = _query.find(key);
        bool found(false);
        if (it != _query.end())
        {
            value = it->second;
            found = true;
        }
        return found;
    }

    std::string uri::get_fragment() const
    {
        return _fragment;
    }

    bool uri::find_keyword(const std::string &input_url, size_t &st, size_t &before, const std::string &delim, std::string &result)
    {
        size_t temp_st = st;

        st = input_url.find(delim, before);
        if (st == std::string::npos)
        {
            st = temp_st;
            return false;
        }

        result = input_url.substr(before, st - before);
        before = st + delim.length();

        if (result.empty())
            return false;

        return true;
    }

    bool uri::split_query(const std::string &str, const std::string &delim, std::string &key, std::string &value)
    {
        size_t st = str.find(delim);

        if (st == std::string::npos)
        {
            key = str;
            value = "";
            return false;
        }

        key = str.substr(0, st);
        value = str.substr(st + delim.length());

        return true;
    }

    void uri::parse(const std::string &str)
    {
        size_t st = 0;
        size_t before = 0;

        // scheme 파싱 (예: "http", "https")
        // has_authority: authority(host/userinfo/port) 파싱 여부를 결정하는 플래그
        // - "://" 있음 → scheme 있는 절대 URL
        // - "//"로 시작 → scheme-relative URL
        // - 그 외(상대 경로 등) → authority 없음, path 파싱만 수행
        bool has_authority = uri::find_keyword(str, st, before, "://", _scheme);
        if (!has_authority && str.size() >= 2 && str[0] == '/' && str[1] == '/')
        {
            has_authority = true;
            before = 2;
        }

        if (has_authority)
        {
            // userinfo 파싱 — "@" 앞의 "user:pass" 부분 분리
            // authority 영역(다음 "/" 또는 "?" 또는 "#"까지)에서만 "@"를 탐색
            size_t authority_end = str.find_first_of("/?#", before);
            size_t at_pos = str.find('@', before);
            if (at_pos != std::string::npos &&
                (authority_end == std::string::npos || at_pos < authority_end))
            {
                _userinfo = str.substr(before, at_pos - before);
                before = at_pos + 1;
            }

            // host 파싱 — "/" 또는 "?" 또는 "#"가 나오기 전까지가 host
            // path가 없는 URL(예: http://example.com)도 처리
            size_t host_end = str.find_first_of("/?#", before);
            if (host_end == std::string::npos)
            {
                _host = str.substr(before);
                before = str.length();
            }
            else
            {
                _host = str.substr(before, host_end - before);
                before = host_end;
            }

            _port = 8080; // default port

            // host에서 port 분리 (IPv6 bracketed notation 지원)
            if (!_host.empty() && _host.front() == '[')
            {
                // IPv6: [2001:db8::1] 또는 [2001:db8::1]:8080
                size_t bracket_close = _host.find(']');
                if (bracket_close != std::string::npos)
                {
                    // bracket 뒤에 ":port"가 있는지 확인
                    if (bracket_close + 1 < _host.length() && _host[bracket_close + 1] == ':')
                    {
                        _port = std::atoi(_host.substr(bracket_close + 2).c_str());
                    }
                    // bracket 안의 주소만 추출 ([ ] 제거)
                    _host = _host.substr(1, bracket_close - 1);
                }
            }
            else
            {
                size_t colon_pos = _host.find(':');
                if (colon_pos != std::string::npos)
                {
                    _port = std::atoi(_host.substr(colon_pos + 1).c_str());
                    _host = _host.substr(0, colon_pos);
                }
            }
        }

        // fragment(#) 분리 — 이후 path/query 파싱 범위를 제한
        size_t frag_pos = str.find('#', before);
        size_t effective_end = (frag_pos != std::string::npos) ? frag_pos : str.length();

        if (frag_pos != std::string::npos && frag_pos + 1 < str.length())
        {
            _fragment = str.substr(frag_pos + 1);
        }

        // path 파싱 — "?" 또는 "#" 이전까지의 "/" 구분 세그먼트
        size_t query_pos = str.find('?', before);
        if (query_pos != std::string::npos && query_pos >= effective_end)
            query_pos = std::string::npos; // "#" 뒤의 "?"는 무시

        size_t path_end = effective_end;
        if (query_pos != std::string::npos)
            path_end = query_pos;

        _path = str.substr(before, path_end - before);

        // query string 파싱 — "#" 이전까지만
        if (query_pos != std::string::npos && query_pos + 1 < effective_end)
        {
            const std::string query_string = str.substr(query_pos + 1, effective_end - query_pos - 1);

            size_t q_before = 0;
            while (q_before < query_string.length())
            {
                size_t amp_pos = query_string.find('&', q_before);
                std::string pair;

                if (amp_pos == std::string::npos)
                {
                    pair = query_string.substr(q_before);
                    q_before = query_string.length();
                }
                else
                {
                    pair = query_string.substr(q_before, amp_pos - q_before);
                    q_before = amp_pos + 1;
                }

                if (!pair.empty())
                {
                    std::string key, value;
                    uri::split_query(pair, "=", key, value);
                    if (!key.empty())
                        _query.insert(std::unordered_map<std::string, std::string>::value_type(key, value));
                }
            }
        }
    }

}