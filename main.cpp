#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

void TOPSIS(vector<vector<double>> lst,vector<double> weight){
    for (int i = 0; i < lst.size(); i++) {
        if (lst[i].size() < lst[0].size()) {
            lst[i].resize(lst[0].size());
        }
    }

    //Нормализация матрицы
    vector<double> normalization_num;
    for (int i = 0; i < lst[0].size(); i++) {
        double count = 0;
        for (int j = 0; j < lst.size(); j++) {
            count += pow(lst[j][i], 2);
        }
        normalization_num.push_back(sqrt(count));
    }

    for (int i = 0; i < lst[0].size(); i++) {
        for (int j = 0; j < lst.size(); j++) {
            lst[j][i] = lst[j][i] / normalization_num[i];
        }
    }

    //Вычислить взвешенную нормализованную матрицу принятия решений
    for (int i = 0; i < lst[0].size(); i++) {
        for (int j = 0; j < lst.size(); j++) {
            lst[j][i] = lst[j][i] * weight[i];
        }
    }

    //Определите худшую альтернативу
    vector<double> best, worst;
    for (int i = 0; i < lst[0].size(); i++) {
        vector<double> flag;
        for (int j = 0; j < lst.size(); j++) {
            flag.push_back(lst[j][i]);
        }
        best.push_back(*max_element(flag.begin(), flag.end()));
        worst.push_back(*min_element(flag.begin(), flag.end()));
    }

    /* Separation measure for each row */
    vector<double> s_best, s_worst;
    for (auto i : lst) {
        double flag_for_best = 0, flag_for_worst = 0;
        for (int j = 0; j < i.size(); j++) {
            flag_for_best += pow((i[j] - best[j]), 2);
            flag_for_worst += pow((i[j] - worst[j]), 2);
        }
        s_best.push_back(sqrt(flag_for_best));
        s_worst.push_back(sqrt(flag_for_worst));
    }


    vector<string> solution;
    for (int i = 0; i < s_best.size(); i++) {
        solution.push_back(to_string(s_worst[i] / (s_best[i] + s_worst[i])));
        cout << "Program " << i+1 <<" ===== "<<solution[i] << endl;
    }

}

int main() {
    vector<double> weight = {0.25, 0.25, 0.15, 0.1, 0.05, 0.2};
    vector<vector<double>> lst = {
            {0.5, 0.8, 1, 0.3, 0.7, 1},
            {1, 0.7, 0.4, 0.7, 0.2, 0.5},
            {1, 0.4, 0.3, 0.4, 0.25, 0.5},
            {1, 0.4, 0.5, 0.35, 0.3, 0.5}
    };

     TOPSIS(lst,weight);
}

