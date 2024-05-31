// RAII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>
#include <utility>
#include <cassert>

extern "C" {
struct Resource
{
};

Resource* CreateResource();
void UseResource(Resource* resource);
// Удаляет ресурс. Если resource == nullptr, функиция ничего не делает
void DeleteResource(Resource* resource);
}

class ResourceHolder
{
public:
	ResourceHolder()
		: m_resource{ CreateResource() }
	{
		if (!m_resource)
		{
			throw std::runtime_error("Failed to create resource");
		}
	}
	ResourceHolder(const ResourceHolder&) = delete;
	ResourceHolder& operator=(const ResourceHolder&) = delete;

	ResourceHolder(ResourceHolder&& other) noexcept
		: m_resource{ std::exchange(other.m_resource, nullptr) }
	{
	}
	ResourceHolder& operator=(ResourceHolder&& rhs) noexcept
	{
		if (this != &rhs)
		{
			DeleteResource(m_resource);
			m_resource = std::exchange(rhs.m_resource, nullptr);
		}
		return *this;
	}
	~ResourceHolder()
	{
		DeleteResource(m_resource);
	}
	void Use()
	{
		assert(m_resource);
		UseResource(m_resource);
	}

private:
	Resource* m_resource;
};

int main()
{
	ResourceHolder r;
	r.Use();
}
