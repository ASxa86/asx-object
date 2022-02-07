#include <asx-object/Object.h>
#include <algorithm>

using asx::object::Object;

Object::Object()
{
}

bool Object::addChild(std::shared_ptr<Object> x)
{
	const auto result = std::ranges::find(this->children, x);

	if(result == std::end(this->children))
	{
		this->children.emplace_back(std::move(x));
		return true;
	}

	return false;
}

bool Object::removeChild(std::shared_ptr<Object> x)
{
	const auto result = std::ranges::remove(this->children, x);

	if(std::begin(result) != std::end(this->children))
	{
		this->children.erase(std::begin(result), std::end(result));
		return true;
	}

	return false;
}

Object* Object::getChild(SizeType x) const
{
	if(x < this->children.size())
	{
		return this->children[x].get();
	}

	return nullptr;
}
