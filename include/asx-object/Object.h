#pragma once

#include <asx-object/export.hxx>
#include <memory>
#include <vector>

namespace asx::object
{
	template <class T, class U>
	concept Derived = std::is_base_of<U, T>::value;

	///
	///	\brief This class defines a generic way to manage object hierarchy.
	///
	class ASX_OBJECT_EXPORT Object : public std::enable_shared_from_this<Object>
	{
	public:
		using SizeType = std::vector<std::shared_ptr<Object>>::size_type;

		Object();
		virtual ~Object() = default;

		Object(const Object&) = delete;
		Object(Object&&) noexcept = delete;

		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		bool addChild(std::shared_ptr<Object> x);
		bool removeChild(std::shared_ptr<Object> x);

		Object* getChild(SizeType x = {}) const;

		template <typename Func>
		std::vector<Object*> getChildren(Func x = [](const auto& x) { return x.get(); }) const
		{
			std::vector<Object*> v;
			v.reserve(this->children.size());

			for(const auto& child : this->children)
			{
				v.push_back(x(child));
			}

			return v;
		}

		template <Derived<Object> T>
		auto getChild(SizeType x = {}) const
		{
			auto child = this->getChild(x);
			return dynamic_cast<T*>(child);
		}

		template <Derived<Object> T, typename Func>
		auto getChildren(Func x = [](const auto& x) { return x.get(); }) const
		{
			std::vector<T*> v;
			v.reserve(this->children.size());

			for(auto child : this->getChildren(x))
			{
				auto typeChild = dynamic_cast<T*>(child);

				if(typeChild != nullptr)
				{
					v.push_back(typeChild);
				}
			}

			return v;
		}

	private:
		std::vector<std::shared_ptr<Object>> children;
	};
}