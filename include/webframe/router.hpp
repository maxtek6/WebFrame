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

#ifndef WEBFRAME_ROUTER_HPP
#define WEBFRAME_ROUTER_HPP

#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

namespace webframe
{
    class request;
    class response;
    class handler;

    class tree_node
    {
    public:
        tree_node() = default;
        ~tree_node() = default;
        void add(const std::string& path, handler* h);
        handler* find(const std::string& path, std::vector<std::string>& variables) const;
    private:
        enum class node_type
        {
            leaf,
            token,
            wildcard
        };
        static void split_path(const std::string& path, std::queue<std::string>& tokens);
        tree_node *push_token(const std::string& token);
        tree_node *push_wildcard();
        tree_node *next(const std::string& token, std::vector<std::string>& variables) const;
        tree_node *next_token(const std::string& token) const;
        tree_node *next_wildcard(const std::string& token, std::vector<std::string>& variables) const;
        std::unique_ptr<std::unordered_map<std::string, std::unique_ptr<tree_node>>> _token_nodes;
        std::unique_ptr<tree_node> _wildcard_node;
        node_type _type = node_type::leaf;
        handler *_handler = nullptr;
    };

    class router
    {
    public:
        router() = default;
        ~router() = default;
        void add_route(const std::string& path, handler* h);
        handler *find_route(const std::string& path, std::vector<std::string>& variables) const;
        void set_default(handler* h);
        handler* get_default() const;
    private:        
        tree_node _root;
        handler* _default_handler = nullptr;
    };
}
#endif