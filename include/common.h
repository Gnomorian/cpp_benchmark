#pragma once
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

constexpr auto concat = [](auto...params)
{
	std::wstringstream stream;
	((stream << params), ...);
	return stream.str();
};

constexpr auto stdCommandline = [](auto argc, auto args)
{
	std::vector<std::wstring_view> buffer;
	auto generator = [i = 0, args] () mutable
	{
		return std::wstring_view {args[i++] };
	};
	std::generate_n(std::back_inserter(buffer), argc, generator);
	return buffer;
};