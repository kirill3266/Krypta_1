#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <random>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <chrono>

using namespace boost::numeric::ublas;

//смещение: -1
void encrypt(std::wstring &str, boost::numeric::ublas::matrix<wchar_t> &m, std::vector<int> &pos, int &shift) {
    std::array<wchar_t, 36> symbols = {L'а', L'б', L'в', L'г', L'д', L'е', L'ё', L'ж', L'з', L'и', L'й', L'к', L'л',
                                       L'м',
                                       L'н', L'о', L'п', L'р', L'с', L'т', L'у', L'ф', L'х', L'ц', L'ч', L'ш', L'щ',
                                       L'ъ',
                                       L'ы', L'ь', L'э', L'ю', L'я', L',', L'.', L' '};

    std::array<bool, 36> exist = {};
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, 35);
    auto dice = std::bind(distribution, generator);
    wchar_t ch;
    //генерация диска
    for (int i = 0; i < m.size1(); ++i) {
        std::fill(exist.begin(), exist.end(), false);
        for (int j = 0; j < m.size2(); ++j) {
            while (true) {
                ch = symbols[dice()];
                if (!exist[std::distance(symbols.begin(), std::find(symbols.begin(), symbols.end(), ch))]) {
                    m(i, j) = ch;
                    if (ch == str[i]) pos[i] = j;
                    exist[std::distance(symbols.begin(), std::find(symbols.begin(), symbols.end(), ch))] = true;
                    break;
                }
            }
        }
    }
    std::wcout << L"Ключ: " << m << std::endl;
    //выполнение смещения
    for (int i = 0; i < pos.size(); ++i) {
        pos[i] += shift;
        while (pos[i] < 0) pos[i] += 36;
        while (pos[i] > 35) pos[i] -= 36;
    }
    for (int i = 0; i < str.length(); ++i)
        str[i] = m(i, pos[i]);
    std::wcout << L"Закодированное сообщение: " << str << std::endl;
    //Частотный анализ
    std::array<int,36> chast = {};
    int aboba;
    std::fill(chast.begin(),chast.end(),0);
    for(auto i:str) {
        chast[std::distance(symbols.begin(),std::find(symbols.begin(),symbols.end(),i))] += 1;
    }
    for(int i =0;i<chast.size();++i) {
        if(chast[i]!=0)
            std::wcout << symbols[i] << L": " << double(chast[i])/str.length() << L" ";
    }
    std::wcout << std::endl;
}

void decrypt(matrix<wchar_t> &m, std::vector<int> &pos, int shift) {
    for (int i = 0; i < pos.size(); ++i) {
        pos[i] -= shift;
        while (pos[i] < 0) pos[i] += 36;
        while (pos[i] > 35) pos[i] -= 36;
    }
    std::wstring str;
    for (int i = 0; i < pos.size(); ++i)
        str.push_back(m(i, pos[i]));
    std::wcout << L"Раскодированное сообщение: " << str << std::endl;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF8");
    std::wstring str;
    int shift;
    std::wcout << L"Введите строку для кодирования: ";
    std::getline(std::wcin, str);
    std::wcout << L"Введите смещение: ";
    std::wcin >> shift;
    matrix<wchar_t> m(str.length(), 36);
    std::vector<int> pos(str.length());
    encrypt(str, m, pos, shift);
    decrypt(m,pos,shift);
    return 0;
}
