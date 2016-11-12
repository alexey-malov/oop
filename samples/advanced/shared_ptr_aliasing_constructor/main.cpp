#include <memory>
#include <vector>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <string>
#include <iostream>
#include <functional>

using namespace std;

struct Document;
typedef weak_ptr<Document> DocumentWeakPtr;
typedef shared_ptr<Document> DocumentSharedPtr;
typedef shared_ptr<const Document> ConstDocumentSharedPtr;

struct Chapter;
typedef weak_ptr<Chapter> ChapterWeakPtr;
typedef shared_ptr<Chapter> ChapterSharedPtr;
typedef shared_ptr<const Chapter> ConstChapterSharedPtr;

// Интерфейс контейнера глав
struct IChapterContainer
{
	virtual size_t GetChapterCount()const throw() = 0;
	virtual ChapterSharedPtr GetChapter(size_t index) = 0;
	virtual ConstChapterSharedPtr GetChapter(size_t index)const = 0;
	virtual const ChapterSharedPtr & AddChapter(const ChapterSharedPtr& chapter) = 0;
	virtual const ChapterSharedPtr & RemoveChapter(const ChapterSharedPtr& chapter) = 0;
	virtual DocumentSharedPtr GetDocument() throw () = 0;
	virtual ConstDocumentSharedPtr GetDocument()const throw() = 0;
protected:
	~IChapterContainer(){}
};

// Реализация контейнера глав
template <typename ThisType>
struct ChapterContainer 
	: IChapterContainer
	, enable_shared_from_this<ThisType>
{
	// Добавляет главу в контейнер (строгая гарантия безопасности исключений)
	const ChapterSharedPtr & AddChapter(const ChapterSharedPtr& chapter) override
	{
		// Главу нельзя добавить, если она находится в каком-либо контейнере
		if (chapter->m_parent)
		{
			throw logic_error("The chapter is already added to somewhere");
		}

		// Запрещаем добавлять главы, относящиеся к чужому документу
		if (chapter->m_document.lock() != GetDocument())
		{
			throw logic_error("The chapter belongs to a different document");
		}
		
		m_chapters.push_back(chapter);
		chapter->m_parent = this;
		return chapter;
	}

	// Удаляет главу из контейнера (строгая гарантия безопасности исключений)
	const ChapterSharedPtr & RemoveChapter(const ChapterSharedPtr& chapter)
	{
		// Нельзя удалить чужую главу
		if (chapter->m_parent != this)
		{
			throw invalid_argument("The chapter does not belong to this chapter container");
		}

		auto pos = find_if(m_chapters.begin(), m_chapters.end(), [&](const ChapterWeakPtr& item){
			return item.lock() == chapter;
		});

		assert(pos != m_chapters.end());
		m_chapters.erase(pos);
		chapter->m_parent = nullptr;

		return chapter;
	}

	virtual size_t GetChapterCount() const throw() override
	{
		return m_chapters.size();
	}

	virtual ChapterSharedPtr GetChapter(size_t index) override
	{
		return m_chapters.at(index).lock();
	}

	virtual ConstChapterSharedPtr GetChapter(size_t index) const override
	{
		return m_chapters.at(index).lock();
	}

private:
	vector<ChapterWeakPtr> m_chapters;
};

// Глава. Хранит заглавие, ссылки на документ-владелец и на родительский контейнер
// Глава также может хранить внутри себя дочерние главы
struct Chapter 
	: ChapterContainer<Chapter>
	
{
	friend struct Document;
	friend struct ChapterContainer < Chapter > ;
	friend struct ChapterContainer < Document >;

	virtual ConstDocumentSharedPtr GetDocument()const throw() override
	{
		return m_document.lock();
	}

	virtual DocumentSharedPtr GetDocument() throw() override
	{
		return m_document.lock();
	}

	// Возвращаем ссылку на родительский контейнер
	shared_ptr<const IChapterContainer> GetParent()const throw()
	{
		return {GetDocument(), m_parent};
	}

	// Возвращаем ссылку на родительский контейнер
	shared_ptr<IChapterContainer> GetParent() throw()
	{
		return{ GetDocument(), m_parent };
	}


	string GetTitle()const
	{
		return m_title;
	}

	~Chapter()
	{
		cout << "The chapter" << m_title << " has been destroyed" << endl;
	}

	Chapter(const Chapter&) = delete;
	Chapter& operator=(const Chapter&) = delete;
private:
	Chapter(const DocumentSharedPtr & document, const string& title = string())
		: m_document(document)
		, m_title(title)
	{
	}

	DocumentWeakPtr m_document;
	string m_title;
	IChapterContainer* m_parent = nullptr;
};

// Документ. Управляет главами
struct Document 
	: ChapterContainer<Document>
{
	Document(const Document&) = delete;
	Document& operator=(const Document&) = delete;

	static DocumentSharedPtr Create()
	{
		// Нельзя использовать make_shared из-за приватного деструктора
		return DocumentSharedPtr(new Document());
	}

	virtual DocumentSharedPtr GetDocument() throw () override
	{
		return shared_from_this();
	}

	virtual ConstDocumentSharedPtr GetDocument() const throw() override
	{
		return shared_from_this();
	}

	// Создает главу и сохраняет ее внутри документа. Обеспечивает строгую гарантию безопасности исключений
	shared_ptr<Chapter> CreateChapter(const string& title = string())
	{
		// Получаем сильную ссылку на самих себя
		auto strongThis = shared_from_this();

		// Создаем главу, которая сохранит слабую ссылку на нас
		// make_unique не доступен из-за приватного конструктора, поэтому создаем через new
		unique_ptr<Chapter> chapter(new Chapter(strongThis, title)); // Может выбросить исключение, но не страшно

		// Помещаем ее во множество глав документа
		auto result = m_chapters.insert(move(chapter)); // Может выбросить исключение, но не страшно

		// Оборачиваем указатель в shared_ptr
		return shared_ptr<Chapter>(strongThis, result.first->get()); // не выбрасывает исключений
	}

	~Document()
	{
		cout << "The document is being destroyed" << endl;
	}
private:
	Document() = default;

	set<unique_ptr<Chapter>> m_chapters;
};

void PrintTableOfContents(const Document& doc)
{
	function<void(const IChapterContainer& container, const string& prefix)> PrintContainer;
	PrintContainer = [&](const IChapterContainer& container, const string& prefix)
	{
		auto numChapters = container.GetChapterCount();
		for (size_t i = 0; i < numChapters; ++i)
		{
			auto chapter = container.GetChapter(i);
			auto intro = prefix + to_string(i + 1) + ".";
			cout << intro << " " << chapter->GetTitle() << endl;
			PrintContainer(*chapter, intro);
		}
	};
	PrintContainer(doc, string());
}

void main()
{
	ChapterSharedPtr someChapter;
	{
		auto document = Document::Create();

		assert(document->GetDocument() == document);

		auto chapter1 = document->AddChapter(document->CreateChapter("Chapter 1"));
		assert(chapter1->GetParent() == document);

		auto chapter2 = document->AddChapter(document->CreateChapter("Chapter 2"));
		auto chapter3 = document->AddChapter(document->CreateChapter("Chapter 3"));
		auto chapter21 = chapter2->AddChapter(document->CreateChapter("Chapter 2.1"));
		auto chapter22 = chapter21->GetParent()->AddChapter(document->CreateChapter("Chapter 2.2"));
		assert(chapter21->GetParent() == chapter2);

		PrintTableOfContents(*document);

		cout << "-------Moving Chapter 1 into Chapter 2.1" << endl;

		chapter21->AddChapter(document->RemoveChapter(chapter1));
		assert(chapter1->GetParent() == chapter21);

		PrintTableOfContents(*document);

		cout << "------- Removing Chapter 2.1" << endl;

		chapter2->RemoveChapter(chapter21);
		assert(!chapter21->GetParent());

		PrintTableOfContents(*document);

		someChapter = chapter2;
		// Несмотря на то, что ссылка document уничтожится при выходе из блока,
		// счетчик ссылок на документ не обнулится за счет aliasing-ссылки someChapter из внешнего блока
	}

	cout << "------- Printing the document obtained through the chapter.GetDocument()" << endl;

	// Восстанавливаем ссылку на документ по имеющейся ссылке на одну из глав
	auto doc = someChapter->GetDocument();
	PrintTableOfContents(*doc);

	// При выходе из этого блока счетчик ссылок на документ обнулится и он с главами будет выпилен
	cout << "------- Leaving the function" << endl;
}
