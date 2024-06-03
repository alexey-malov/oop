#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

// Структура, хранящая данные, общие для всех типов HTTP-запросов.
// Она не будет использоваться для полиморфного удаления наследников.
// По умолчанию у неё публичный невиртуальный деструктор, чтобы
// не иметь накладных расходов на таблицу виртуальных функций.
struct BaseHttpRequest
{
	// У всех запросов есть target и заголовки
	std::string target;
	std::unordered_map<std::string, std::string> headers;
};

struct GetRequest : BaseHttpRequest
{
	// У GET-запроса нет тела
};

struct PutRequest : BaseHttpRequest
{
	std::string body;
};

struct PostRequest : BaseHttpRequest
{
	std::string body;
};

struct DeleteRequest : BaseHttpRequest
{
	// DELETE-запрос не имеет тело
};

// Запрос — один из указанных запросов
using Request = std::variant<GetRequest, PostRequest, PutRequest, DeleteRequest>;

template <class... Ts>
struct overloaded : Ts...
{
	using Ts::operator()...;
};

inline void PrintBaseRequest(const BaseHttpRequest& r, std::string_view method, std::ostream& out)
{
	out << method << ' ' << r.target << " HTTP/1.1\r\n";
	for (const auto& [name, value] : r.headers)
	{
		out << name << ": " << value << "\r\n";
	}
	out << "\r\n";
}

inline void Print(const Request& request, std::ostream& out)
{
	struct RequestVisitor
	{
		std::ostream& out;
		void operator()(const GetRequest& r) const { PrintBaseRequest(r, "GET", out); }
		void operator()(const DeleteRequest& r) const { PrintBaseRequest(r, "DELETE", out); }
		void operator()(const PostRequest& r) const
		{
			PrintBaseRequest(r, "POST", out);
			out << r.body << "\r\n";
		}
		void operator()(const PutRequest& r) const
		{
			PrintBaseRequest(r, "PUT", out);
			out << r.body << "\r\n";
		}
	};
	std::visit(RequestVisitor{ out }, request);
}
