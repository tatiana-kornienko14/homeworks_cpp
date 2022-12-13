#include <iostream>
#include <regex>
#include <stack>
#include "utils.hpp"

bool is_number(const std::string &str) {
    static const std::regex r(R"([+-]?(\d*\.)?\d+([Ee[+-]?\d+)?)");
    return std::regex_match(str, r);
}

int Calculate(const std::string& data) {
    std::vector<int> v1; // хотела сделать тип double, но в тестах int, так что пока так
    std::string tmp;
    bool f = 0, pr = 0, dl = 0, mns = 0;
    
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] != '*' && 
            data[i] != '+' && 
            data[i] != '-' && 
            data[i] != '/' && 
            !(is_number(std::to_string(data[i])))) {
            std::cout << "ошибка!\n";
            return 0;
        }

        if (f) {
            if (data[i] == ')') {
                int tmp_ans = Calculate(tmp);

                if (pr) {
                    v1[v1.size()-1] *= tmp_ans;
                    pr = 0;
                } else if (dl) {
                    v1[v1.size()-1] /= tmp_ans;
                    dl = 0;
                } else if (mns) {
                    v1.push_back(-tmp_ans);
                    mns = 0;
                } else {
                   v1.push_back(tmp_ans);
                }

                tmp = {};
                f = 0;
            } else {
                tmp.push_back(data[i]);
            }

            continue;
        }

        if (data[i] == '(') {
            f = 1;
            continue;
        }

        if (pr) {
            v1[v1.size()-1] *= std::stoi(data[i]);
            pr = 0;
            continue;
        }

        if (dl) {
            v1[v1.size()-1] /= std::stoi(data[i]);
            dl = 0;
            continue;
        }

        if (mns) {
            v1.push_back(-std::stoi(data[i]));
            mns = 0;
            continue;
        }

        if (data[i] == '*') {
            pr = 1;
            continue;
        }

        if (data[i] == '/') {
            dl = 1;
            continue;
        }

        if (data[i] == '-') {
            mns = 1;
            continue;
        }

        if (data[i] == '+') {
            continue;
        }

        v1.push_back(std::stoi(data[i]));
    }

    int answer = 0;

    for (auto n : v1) {
        answer += n;
    }

    return answer;
}
