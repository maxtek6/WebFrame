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

#include <test.hpp>

namespace webframe::test
{
    void application::configure_router(webframe::router *router)
    {
        setup_router(router);
        _client = std::make_unique<client>(router);
    }

    void application::setup_router(webframe::router *router)
    {
        (void)router;
    }

    void dispatch_error::run_tests(client *c)
    {
        (void)c;
        throw std::runtime_error("dispatch error");
    }

    void empty_router::run_tests(client *c)
    {
        request req;
        req.method = webframe::method::http_get;
        req.path = "/somepath";
        response res;
        c->run(&req, &res);
        MAXTEST_ASSERT(res.status_code == 404);
    }
}