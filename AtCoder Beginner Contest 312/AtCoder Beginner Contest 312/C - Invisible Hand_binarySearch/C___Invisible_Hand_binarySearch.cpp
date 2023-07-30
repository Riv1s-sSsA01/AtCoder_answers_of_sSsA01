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
	using Value = unsigned;
	
	struct InputData
	{
		std::vector<Value> sellValues;
		std::vector<Value> buyValues;
	};
	struct Solution
	{
		Value value;
	};

	static void Input(InputData& input)
	{
		size_t N, M;
		std::cin >> N >> M;
		input.sellValues.resize(N);
		input.buyValues.resize(M);

		std::for_each(
			std::begin(input.sellValues), std::end(input.sellValues),
			[](auto& value)
			{
				std::cin >> value;
			}
		);
		std::for_each(
			std::begin(input.buyValues), std::end(input.buyValues),
			[](auto& value)
			{
				std::cin >> value;
			}
		);
	}
	static void Output(const Solution& solution)
	{
		sss::io::Output(solution.value);
	}

	static void Solve(InputData& input, Solution& solution)
	{
		std::sort(std::begin(input.sellValues), std::end(input.sellValues));
		std::sort(std::begin(input.buyValues),  std::end(input.buyValues));

		Value lower = 1;
		Value upper = 1000000000;
		while (true) {
			const auto value = (lower + upper) / 2;

			const auto seller = std::upper_bound(
				std::cbegin(input.sellValues), std::cend(input.sellValues),
				value
			);
			const auto buyer = std::upper_bound(
				std::crbegin(input.buyValues), std::crend(input.buyValues),
				value, std::greater<Value>{}
			);
			const auto sellerCount = std::distance(std::cbegin(input.sellValues), seller);
			const auto  buyerCount = std::distance(std::crbegin(input.buyValues), buyer);

			const auto isOk = sellerCount >= buyerCount;
			if (upper <= lower + 1) {
				solution.value = (isOk ? lower : upper);
				return;
			}
			else {
				(isOk ? upper : lower) = value;
			}
		}
	}
};

int main()
{
	Solver::Run();
}
