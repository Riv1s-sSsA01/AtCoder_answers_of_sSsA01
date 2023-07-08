#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <string>
#include <optional>
#include <vector>
#include <numeric>
#include <limits>

namespace sss
{
	namespace io
	{

		auto& outStream = std::cout;

		constexpr auto* const SPACE = " ";

		std::string  TRUE_TEXT = "Yes";
		std::string FALSE_TEXT = "No";

		template<class T>
		void Output(const T& value)
		{
			outStream << value;
		}

		void Output(const bool is)
		{
			outStream << (is ? TRUE_TEXT : FALSE_TEXT);
		}

		template<class T>
		void Output(const std::vector<T>& collection)
		{
			if (collection.empty()) {
				return;
			}

			Output(collection.front());

			std::for_each(
				std::next(std::cbegin(collection)), std::cend(collection),
				[&](const auto& value)
				{
					Output(SPACE);
					Output(value);
				}
			);
		}

		// 可変引数テンプレート
		// https://cpprefjp.github.io/lang/cpp11/variadic_templates.html
		template<class Head, class... Tail>
		void Output(const std::vector<Head>& head, const std::vector<Tail>&... tail)
		{
			Output(head);
			Output("\n");

			Output(tail...);
		}

	} // namespace io

} // namespace sss

class Solver
{
public:
	void Run()
	{
		Input();
		const auto solution = Solve();
		Output(solution);
	}

private:
	struct Solution
	{
		size_t count;
	};

	void Input()
	{
		size_t n;
		std::cin >> n >> m;

		std::cin >> a1 >> a2;
		values.resize(n - 2);
		std::for_each(
			std::begin(values), std::end(values),
			[](auto& value)
			{
				std::cin >> value;
			}
		);
	}

	Solution Solve()
	{
		std::sort(std::begin(values), std::end(values));

		auto min = std::numeric_limits<int>::max();
		for (auto i = 0; i < static_cast<int>(std::size(values)) - m + 1; ++i) {
			min = std::min(
				min,
				std::max(static_cast<int>(a1) - static_cast<int>(values[i]), 0) + std::max(static_cast<int>(values[i + m - 1]) - static_cast<int>(a2), 0)
			);
		}

		return {static_cast<size_t>(min)};
	}

	void Output(const Solution& solution) const
	{
		sss::io::Output(
			solution.count
		);
	}

	// メンバ--------------------------------------------------------------------------
	int m;

	size_t a1;
	size_t a2;
	std::vector<size_t> values;
};

int main()
{
	Solver{}.Run();
}
