#include "in_inverted_section.hpp"
#include "outside_section.hpp"
#include "visitor/render_section.hpp"
#include "visitor/is_node_empty.hpp"

using namespace mstch;

state::in_inverted_section::in_inverted_section(
        const std::string& section_name):
        section_name(section_name), skipped_openings(0)
{
}

std::string state::in_inverted_section::render(
        render_context& ctx, const token& token)
{
    switch(token.token_type()) {
    case token::type::section_close:
        if(token.content() == section_name && skipped_openings == 0) {
            std::string out;
            auto& section_node = ctx.get_node(section_name);
            if(boost::apply_visitor(visitor::is_node_empty(), section_node))
                out = render_context::push(ctx).render(section_text.str());
            ctx.set_state<outside_section>();
            return out;
        } else {
            skipped_openings--;
            section_text << token.raw();
        }
        break;
    case token::type::inverted_section_open:
    case token::type::section_open:
        skipped_openings++;
    case token::type::text:
    case token::type::variable:
    case token::type::unescaped_variable:
    case token::type::comment:
    case token::type::partial:
        section_text << token.raw();
        break;
    }
    return "";
}
