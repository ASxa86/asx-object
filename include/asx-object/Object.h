#pragma once

#include <asx-object/export.hxx>
#include <functional>
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

		void setID(std::string_view x);
		std::string_view getID() const;

		Object* getParent() const noexcept;

		bool addChild(std::shared_ptr<Object> x);
		bool removeChild(std::shared_ptr<Object> x);

		Object* getChild(SizeType x = {}) const;
		std::vector<Object*> getChildren() const;

		template <Derived<Object> T>
		T* getChild() const
		{
			for(const auto& child : this->children)
			{
				auto typeChild = dynamic_cast<T*>(child.get());

				if(typeChild != nullptr)
				{
					return typeChild;
				}
			}

			return nullptr;
		}

		template <Derived<Object> T>
		auto getChildren() const
		{
			std::vector<T*> v;

			const auto children = this->getChildren();

			v.reserve(children.size());

			for(auto child : children)
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
		std::string id;
		std::vector<std::shared_ptr<Object>> children;
		Object* parent{};
	};
}