#include <iostream>
#include <string>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <limits>
#include <optional>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

namespace sss
{
	namespace io
	{
		auto& outStream = std::cout;

		constexpr auto* const SPACE		= " ";
		constexpr auto* const NEW_LINE	= "\n";

		std::string  TRUE_TEXT = "Yes";
		std::string FALSE_TEXT = "No";

		template<class T>
		void OutputData(const T& value)
		{
			outStream << value;
		}

		void OutputData(const bool is)
		{
			outStream << (is ? TRUE_TEXT : FALSE_TEXT);
		}

		template<class T>
		void OutputLine(const T& value)
		{
			OutputData(value);
			OutputData(NEW_LINE);
		}

		template<class T>
		void OutputLine(const std::vector<T>& collection, const bool isReverse)
		{
			if (collection.empty()) {
				return;
			}

			OutputData(isReverse ? collection.back() : collection.front());

			if (isReverse) {
				std::for_each(
					std::next(std::crbegin(collection)),
					std::crend(collection),
					[&](const auto& value)
					{
						OutputData(SPACE);
						OutputData(value);
					}
				);
			}
			else {
				std::for_each(
					std::next(std::cbegin(collection)),
					std::cend(collection),
					[&](const auto& value)
					{
						OutputData(SPACE);
						OutputData(value);
					}
				);
			}

			OutputData(NEW_LINE);
		}

		template<class T>
		void OutputLine(const std::vector<T>& collection)
		{
			OutputLine(collection, false);
		}

		template<class T>
		void OutputLineReverse(const std::vector<T>& collection)
		{
			OutputLine(collection, true);
		}

		// 可変引数テンプレート
		// https://cpprefjp.github.io/lang/cpp11/variadic_templates.html
		void Output() {}

		template<class Head, class... Tail>
		void Output(const Head& head, const Tail&... tail)
		{
			OutputLine(head);
			Output(tail...);
		}

	} // namespace io

} // namespace sss

class Solver
{
public:
	static void Run()
	{
		InputData input{};
		Input(input);

		Solution solution{};
		Solve(input, solution);

		Output(solution);
	}

private:
	using Value = unsigned long long;
	struct Price
	{
		Value price;
		bool isSell;
	};
	struct InputData
	{
		std::vector<Price> prices;
	};
	struct Solution
	{
		Value price;
	};

	static void Input(InputData& input)
	{
		size_t N, M;
		std::cin >> N >> M;
		input.prices.resize(N + M);

		for (auto i = 0u; i < N; ++i) {
			std::cin >> input.prices[i].price;
			input.prices[i].isSell = true;
		}
		for (auto i = 0u; i < M; ++i) {
			std::cin >> input.prices[N + i].price;
			input.prices[N + i].isSell = false;
		}
	}
	static void Output(const Solution& solution)
	{
		sss::io::Output(solution.price);
	}

	static void Solve(InputData& input, Solution& solution)
	{
		std::sort(
			std::begin(input.prices), std::end(input.prices),
			[](const auto& left, const auto& right)
			{
				if (left.price == right.price) {
					if (left.isSell) {
						return !right.isSell;
					}
					else {
						return false;
					}
				}
				return left.price < right.price;
			}
		);

		int count = 0;
		std::for_each(
			std::cbegin(input.prices), std::cend(input.prices),
			[&](const auto& price)
			{
				if (!price.isSell) {
					--count;
				}
			}
		);
		for (auto i = 0ull; i < std::size(input.prices); ++i) {
			const auto& price = input.prices[i];
			++count;
			if (count >= 0) {
				solution.price = price.isSell ? price.price : (price.price + 1);
				return;
			}
		}
	}
};

int main()
{
	Solver::Run();
}
