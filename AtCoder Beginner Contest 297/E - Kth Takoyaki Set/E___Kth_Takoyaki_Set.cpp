#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <string>
#include <optional>
#include <vector>
#include <set>
#include <numeric>
#include <limits>

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
		void OutputLine(const std::vector<T>& collection)
		{
			if (collection.empty()) {
				return;
			}

			OutputData(collection.front());

			std::for_each(
				std::next(std::cbegin(collection)), std::cend(collection),
				[&](const auto& value)
				{
					OutputData(SPACE);
					OutputData(value);
				}
			);

			OutputData(NEW_LINE);
		}

		// 可変引数テンプレート
		// https://cpprefjp.github.io/lang/cpp11/variadic_templates.html
		//template<class Head, class... Tail>
		//void Output(const std::vector<Head>& head, const std::vector<Tail>&... tail)
		//{
		//	OutputLine(head);
		//	Output(tail...);
		//}

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
	struct InputData
	{
		std::vector<unsigned long long> costs;
		size_t k;
	};

	struct Solution
	{
		unsigned long long cost;
	};

	static void Input(InputData& input)
	{
		size_t n;
		std::cin >> n >> input.k;

		input.costs.resize(n);
		std::for_each(
			std::begin(input.costs), std::end(input.costs),
			[](auto& value)
			{
				std::cin >> value;
			}
		);
	}

	static void Solve(InputData& input, Solution& solution)
	{
		std::set<unsigned long long> possibleCosts{0};

		std::vector<unsigned long long> answer;
		answer.reserve(input.k + 1);

		while (std::size(answer) < input.k + 1) {
			const auto nextAnswer = *std::begin(possibleCosts);
			answer.push_back(nextAnswer);
			possibleCosts.erase(nextAnswer);

			std::transform(
				std::cbegin(input.costs), std::cend(input.costs),
				std::inserter(possibleCosts, std::begin(possibleCosts)),
				[=](const auto cost)
				{
					return cost + nextAnswer;
				}
			);
		}

		solution.cost = answer.back();
	}

	static void Output(const Solution& solution)
	{
		// mock
		sss::io::OutputLine(solution.cost);
	}
};

int main()
{
	Solver::Run();
}
