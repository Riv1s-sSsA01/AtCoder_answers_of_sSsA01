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
	struct Address
	{
		size_t row;
		size_t col;
	};
	struct InputData
	{
		std::vector<std::vector<bool>> cells;
	};
	struct Solution
	{
		std::vector<Address> addresses;
	};

	static void Input(InputData& input)
	{
		size_t N, M;
		std::cin >> N >> M;
		input.cells.resize(N);

		std::for_each(
			std::begin(input.cells), std::end(input.cells),
			[&](auto& row)
			{
				std::string text;
				std::cin >> text;
				for (auto i = 0ull; i < text.size(); ++i) {
					row.push_back(text[i] == '#');
				}
			}
		);
	}
	static void Output(const Solution& solution)
	{
		std::for_each(
			std::cbegin(solution.addresses), std::cend(solution.addresses),
			[](const auto& address)
			{
				sss::io::OutputData(address.row + 1);
				sss::io::OutputData(sss::io::SPACE);
				sss::io::OutputData(address.col + 1);
				sss::io::OutputData(sss::io::NEW_LINE);
			}
		);
	}

	static bool IsTakCodeCell(const Address& address, bool cell)
	{
		switch (address.row) {
		case 0:
		case 1:
		case 2:
			switch (address.col) {
			case 0:
			case 1:
			case 2:
				return cell == true;
			case 3:
				return cell == false;
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			default:
				return true;
			}
		case 3:
			switch (address.col) {
			case 0:
			case 1:
			case 2:
			case 3:
				return cell == false;
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			default:
				return true;
			}
		case 4:
			return true;
		case 5:
			switch (address.col) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				return true;
			case 5:
			case 6:
			case 7:
			case 8:
				return cell == false;
			default:
				return true;
			}
		case 6:
		case 7:
		case 8:
			switch (address.col) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				return true;
			case 5:
				return cell == false;
			case 6:
			case 7:
			case 8:
				return cell == true;
			default:
				return true;
			}
		default:
			return true;
		}
	}

	static constexpr auto TAK_CODE_SIZE = 9ull;

	static bool IsTakCodeOrigin(const Address& address, const InputData& inputData)
	{
		if (address.row + TAK_CODE_SIZE > std::size(inputData.cells)) {
			return false;
		}
		if (address.col + TAK_CODE_SIZE > std::size(inputData.cells.front())) {
			return false;
		}
		for (auto row = 0ull; row < TAK_CODE_SIZE; ++row) {
		for (auto col = 0ull; col < TAK_CODE_SIZE; ++col) {
			const auto cell = inputData.cells[address.row + row][address.col + col];
			if (not IsTakCodeCell({ row, col }, cell)) {
				return false;
			}
		}
		}
		return true;
	}

	static void Solve(InputData& input, Solution& solution)
	{
		for (auto row = 0ull; row + TAK_CODE_SIZE <= std::size(input.cells); ++row) {
		for (auto col = 0ull; col + TAK_CODE_SIZE <= std::size(input.cells.front()); ++col) {
			const auto address = Address{ row, col };
			if (IsTakCodeOrigin(address, input)) {
				solution.addresses.push_back(address);
		}
		}
		}
	}
};

int main()
{
	Solver::Run();
}
