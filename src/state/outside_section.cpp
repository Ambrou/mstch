#include "visitor/render_node.hpp"
#include "outside_section.hpp"
#include "in_section.hpp"
#include "in_inverted_section.hpp"
#include "render_context.hpp"

using namespace mstch;

std::string state::outside_section::render(
        render_context& ctx,
        const token& token)
{
    switch(token.type()) {
    case token_type::section_open:
        ctx.set_state<in_section>(token.content());
        break;
    case token_type::inverted_section_open:
        ctx.set_state<in_inverted_section>(token.content());
        break;
    case token_type::variable:
    case token_type::unescaped_variable: {
        std::set<visitor::render_node::flag> flags{};
        if (token.type() == token_type::variable)
            flags.insert(visitor::render_node::flag::escape_html);
        return boost::apply_visitor(
                visitor::render_node(flags), ctx.get_node(token.content()));
    }
    case token_type::comment: break;
    case token_type::text:
        return token.raw();
    case token_type::partial:
        break;//render_context(mstch::object{{".", i}}, ctx).render(section);
    case token_type::section_close:
        // TODO ERROR
        break;
    }
    return "";
}
