#include "render_section.hpp"
#include "is_node_empty.hpp"

using namespace mstch;

visitor::render_section::render_section(
        render_context& context,
        const std::string& section,
        std::set<flag> flags):
        context(context),
        section(section),
        flags(flags)
{
}

std::string visitor::render_section::operator()(
        const boost::blank& blank) const
{
    return render_context(mstch::object{{".", mstch::node{}}}, context)
            .render(section);
}

std::string visitor::render_section::operator()(const int& i) const {
    return render_context(mstch::object{{".", i}}, context).render(section);
}

std::string visitor::render_section::operator()(const bool& b) const {
    return render_context(mstch::object{{".", b}}, context).render(section);
}

std::string visitor::render_section::operator()(const std::string& str) const {
    return render_context(mstch::object{{".", str}}, context).render(section);
}

std::string visitor::render_section::operator()(const object& obj) const {
    return render_context(obj, context).render(section);
}

std::string visitor::render_section::operator()(const array& a) const {
    std::ostringstream out;
    if(flags.find(flag::keep_array) != flags.end())
        out << render_context(mstch::object{{".", a}}, context).render(section);
    else
        for (auto& item: a)
            out << boost::apply_visitor(
                    render_section(context, section, {flag::keep_array}), item);
    return out.str();
}

std::string visitor::render_section::operator()(
        const string_lambda& lambda) const
{
    return lambda();
}

std::string visitor::render_section::operator()(
        const renderer_lambda& lambda) const
{
    return (lambda())(section, [&](const std::string& text) {
        return render_context(mstch::object{}, context).render(text);
    });
}
