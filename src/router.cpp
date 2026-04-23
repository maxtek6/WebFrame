/* WebFrame
 *
 * Copyright (C) 2026 Maxtek Consulting
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <webframe.hpp>

class global_default_handler : public webframe::handler
{
protected:
    void handle_get(const webframe::request *req, webframe::response *res) override
    {
        throw webframe::exception::not_found;
    }

    void handle_post(const webframe::request *req, webframe::response *res) override
    {
        throw webframe::exception::not_found;
    }

    void handle_put(const webframe::request *req, webframe::response *res) override
    {
        throw webframe::exception::not_found;
    }

    void handle_delete(const webframe::request *req, webframe::response *res) override
    {
        throw webframe::exception::not_found;
    }
};

static global_default_handler g_default_handler;

namespace webframe
{
    void tree_node::add(const std::string &path, handler *h)
    {
        std::queue<std::string> tokens;
        split_path(path, tokens);
        tree_node *current = this;
        while (!tokens.empty())
        {
            const std::string &token = tokens.front();
            if (token == "*")
            {
                current = current->push_wildcard();
            }
            else
            {
                current = current->push_token(token);
            }
            tokens.pop();
        }
        current->_handler = h;
    }

    handler *tree_node::find(const std::string &path, std::vector<std::string> &variables) const
    {
        std::queue<std::string> tokens;
        split_path(path, tokens);
        const tree_node *current = this;
        while (!tokens.empty() && current)
        {
            const std::string &token = tokens.front();
            current = current->next(token, variables);
            tokens.pop();
        }
        return current ? current->_handler : nullptr;
    }

    void tree_node::split_path(const std::string &path, std::queue<std::string> &tokens)
    {
        size_t start, end;
        if (!path.empty() && path != "/")
        {
            start = 0;
            while (start < path.size())
            {
                size_t end = path.find('/', start);
                if (end == std::string::npos)
                {
                    end = path.size();
                }
                if (end > start)
                {
                    tokens.push(path.substr(start, end - start));
                }
                start = end + 1;
            }
        }
    }

    tree_node *tree_node::push_token(const std::string &token)
    {
        _type = node_type::token;
        if (!_token_nodes)
        {
            _token_nodes = std::make_unique<std::unordered_map<std::string, std::unique_ptr<tree_node>>>();
        }
        auto &node_ptr = (*_token_nodes)[token];
        if (!node_ptr)
        {
            node_ptr = std::make_unique<tree_node>();
        }
        return node_ptr.get();
    }

    tree_node *tree_node::push_wildcard()
    {
        _type = node_type::wildcard;
        if (!_wildcard_node)
        {
            _wildcard_node = std::make_unique<tree_node>();
        }
        return _wildcard_node.get();
    }

    tree_node *tree_node::next(const std::string &token, std::vector<std::string> &variables) const
    {
        tree_node *node(nullptr);
        switch(_type)
        {
            case node_type::token:
                node = next_token(token);
                break;
            case node_type::wildcard:
                node = next_wildcard(token, variables);
                break;
            default:
                break;
        }
        return node;
    }

    tree_node *tree_node::next_token(const std::string &token) const
    {
        tree_node *node(nullptr);
        if (_token_nodes)
        {
            auto it = _token_nodes->find(token);
            if (it != _token_nodes->end())
            {
                node = it->second.get();
            }
        }
        return node;
    }

    tree_node *tree_node::next_wildcard(const std::string& token, std::vector<std::string> &variables) const
    {
        if (_wildcard_node)
        {
            variables.push_back(token);
        }
        return _wildcard_node ? _wildcard_node.get() : nullptr;
    }

    void router::add_route(const std::string &path, handler *h)
    {
        _root.add(path, h);
    }

    void router::set_default(handler *h)
    {
        _default_handler = h;
    }

    handler *router::find_route(const std::string &path, std::vector<std::string> &variables) const
    {
        handler *h = _root.find(path, variables);
        return h ? h : get_default();
    }

    handler *router::get_default() const
    {
        return _default_handler ? _default_handler : &g_default_handler;
    }
}