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