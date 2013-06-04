#include "Identifier.h"
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

using namespace Ouroboros::Bench::Language;

Identifier::Identifier()
{
	this->id = -1;
}

Identifier::Identifier(const std::string& name, int id)
{
	this->name = name;
	this->id = id;
}

Identifier::Identifier(const std::string& name)
{
	std::string::const_reverse_iterator lastPartRef = std::find(
		name.rbegin(),
		name.rend(),
		'_');

	if (lastPartRef.base() == name.begin())
	{
		this->name = name;
		this->id = -1;
	}
	else
	{
		std::string lastPart(lastPartRef.base(), name.end());

		try
		{
			int index = boost::lexical_cast<int>(lastPart);

			this->name = std::string(name.begin(), lastPartRef.base() - 1);
			this->id = index;
		}
		catch (...)
		{
			this->name = name;
			this->id = -1;
		}
	}
}

bool Identifier::operator==(const Identifier& other) const
{
	return (name == other.name) &&
		(id == other.id);
}

void Identifier::print(std::ostream& os)
{
	os << name;
	
	if (id != -1)
		os << "_" << id;
}