#include <iostream>
#include <string>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <cstdlib>
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
	struct Data
	{
		unsigned long long n;
		unsigned long long k;
	};
	struct InputData
	{
		std::vector<Data> datas;
	};
	struct Solution
	{
		std::vector<bool> isPossibles;
	};

	static void Input(InputData& input)
	{
		size_t t;
		std::cin >> t;
		input.datas.resize(t);

		std::for_each(
			std::begin(input.datas), std::end(input.datas),
			[](auto& data)
			{
				std::cin >> data.n >> data.k;
			}
		);
	}
	static void Output(const Solution& solution)
	{
		std::for_each(
			std::cbegin(solution.isPossibles), std::cend(solution.isPossibles),
			[](const auto isPossible)
			{
				sss::io::OutputLine(isPossible);
			}
		);
	}

	static bool IsPossible(const Data& data)
	{
		auto remainderSum = 0ull;

		auto temporaryN = data.n;
		while (temporaryN > 0) {
			const auto divided = std::div(temporaryN, 3ll);
			temporaryN = divided.quot;
			remainderSum += divided.rem;
		}

		if (data.k < remainderSum) {
			return false;
		}
		if (data.k > data.n) {
			return false;
		}
		return (data.k % 2) == (data.n % 2);
	}

	static void Solve(InputData& input, Solution& solution)
	{
		solution.isPossibles.reserve(std::size(input.datas));
		std::transform(
			std::cbegin(input.datas), std::cend(input.datas),
			std::back_inserter(solution.isPossibles),
			[](const auto& data)
			{
				return IsPossible(data);
			}
		);
	}
};

int main()
{
	Solver::Run();
}
