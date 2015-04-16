#pragma once

#include <deque>
#include <sstream>
#include <string>
#include <stack>

#include "mstch/mstch.hpp"
#include "state/render_state.hpp"
#include "template_type.hpp"

namespace mstch {
    class render_context {
    public:
        class push {
        public:
            push(render_context& context, const mstch::node& node = {});
            ~push();
            std::string render(const template_type& templt);
        private:
            render_context& context;
        };

        render_context(
                const mstch::node& node,
                const std::map<std::string,template_type>& partials);
        mstch::node get_node(const std::string& token);
        std::string render(const template_type& templt);
        std::string render_partial(const std::string& partial_name);
        template<class T, class... Args>
        void set_state(Args&&... args) {
            state.top() = std::unique_ptr<state::render_state>(
                    new T(std::forward<Args>(args)...));
        }
    private:
        static const mstch::node null_node;
        mstch::node find_node(
                const std::string& token,
                const std::deque<node>& current_nodes);
        const std::map<std::string,template_type>& partials;
        std::deque<mstch::node> nodes;
        std::stack<std::unique_ptr<state::render_state>> state;
    };
}
