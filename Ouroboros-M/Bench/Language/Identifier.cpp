#include "Identifier.h"
#include <boost/format.hpp>

using namespace Ouroboros::Bench::Language;

Identifier::Identifier()
{
	this->id = -1;
}

Identifier::Identifier(std::string& name, int id)
{
	this->name = name;
	this->id = id;
}

Identifier::Identifier(const std::string& name, int id)
{
	this->name = name;
	this->id = id;
}

Identifier::Identifier(std::string& name)
{
	this->name = name;
	this->id = -1;
}

Identifier::Identifier(const std::string& name)
{
	this->name = name;
	this->id = -1;
}

bool Identifier::operator==(const Identifier& other) const
{
	return (name == other.name) &&
		(id == other.id);
}

std::string Identifier::GetFullName()
{
	using boost::format;
	std::string result = name;

	if (id != -1)
	{
		auto suffix = (format("{%1%}") % id).str();
		return result.append(suffix);
	}

	return result;
}

std::string Identifier::ToString()
{
	return GetFullName();
}

void Identifier::print(std::ostream& os)
{
	os << name;
	
	if (id != -1)
		os << "{" << id << "}";
}