#include "Comment_parser.h"

using namespace Ouroboros::Bench::Parser;

Comment_parser::Comment_parser() : Comment_parser::base_type(comment_rule, "Comment")
{
	using qi::omit;
	using ascii::char_;
	using qi::lit;
	using qi::on_error;
    using qi::fail;

	using phoenix::construct;
    using phoenix::val;
	using namespace qi::labels;

	comment_rule = lit("#") >> omit[*char_];
	comment_rule.name("comment");

	on_error<fail>
	(
		comment_rule,
		std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
	);
}