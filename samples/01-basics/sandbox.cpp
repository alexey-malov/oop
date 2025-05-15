#include <iostream>

class IPlugin
{
public:
	virtual ~IPlugin() = default;
	// прочие методы
};

class IRenderable
{
public:
	virtual ~IRenderable() = default;
	virtual void Render() = 0;
};

class ConcretePlugin : public IPlugin
	, public IRenderable
{
public:
	void Render() override
	{
	}
};

void Process(IPlugin& plugin)
{
	// Если plugin поддерживает рендеринг, используем его
	if (auto renderable = dynamic_cast<IRenderable*>(&plugin))
	{
		// Мы запросили интерфейс, а не конкретную реализацию
		renderable->Render();
	}
	// проводим прочие операции над плагином
}

int main()
{
	ConcretePlugin plugin;
	Process(plugin);
}