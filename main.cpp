#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <random>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/algorithm/string/case_conv.hpp>

void encrypt() {
    std::array<wchar_t, 36> symbols = {L'а', L'б', L'в', L'г', L'д', L'е', L'ё', L'ж', L'з', L'и', L'й', L'к', L'л',
                                       L'м',
                                       L'н', L'о', L'п', L'р', L'с', L'т', L'у', L'ф', L'х', L'ц', L'ч', L'ш', L'щ',
                                       L'ъ',
                                       L'ы', L'ь', L'э', L'ю', L'я', L',', L'.', L' '};
    std::array<bool, 36> exist{};
    std::vector<int> pos;
    std::fill(exist.begin(), exist.end(), false);
    using namespace boost::numeric::ublas;
    setlocale(LC_ALL, "ru_RU.UTF8");
    std::wstring str;
    std::wcout << L"Введите строку: ";
    std::getline(std::wcin, str);
    std::wcout << L"Вы ввели: " << str << std::endl;
    boost::algorithm::to_lower(str, std::locale("ru_RU.UTF8"));
    std::wcout << L"После форматирования: " << str << std::endl;
    matrix<wchar_t> table_1(6, 6);
    std::size_t counter = 0;
    std::size_t len = str.length();
    std::default_random_engine generator;
    int i;
    int j;
    for (i = 0; i < table_1.size1(); ++i) {
        for (j = 0; j < table_1.size2(); ++j) {
            if (counter < len) {
                table_1(i, j) = str[counter];
                exist[std::distance(symbols.begin(), std::find(symbols.begin(), symbols.end(), str[counter++]))] = true;
            }
        }
    }
    for (const auto& k: exist)
        if (!k) pos.push_back(std::distance(exist.begin(),k));
    std::uniform_int_distribution<int> distribution(0,static_cast<int>(pos.size()));
    auto dice = [&distribution, &generator]  { return distribution(generator); };
    for (; i < table_1.size1(); ++i) {
        for (; j < table_1.size2(); ++j) {
            table(i,j) = symbols[]
        }
    }
    std::wcout << L"Матрица: " << table_1 << std::endl;
}

void decrypt() {}

int main() {
    encrypt();
    return 0;
}
