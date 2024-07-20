#include <iostream>
using namespace std;

double func(double value) {
    if (value > 0) {
        return value;
    } else {
        return 0;
    }
}

int main() {
    srand(time(0));
    double rate_w = 1000;
    double rate_b = 1000;
    double input;
    double output;
    double weight = 2.00072;
    double bias = -0.00476901;
    double intermediate;
    double cost;
    for(int k=0;k<100;k++){
    double sum_cost = 0;
    for (int j = 0; j < 1000; j++) {
        sum_cost=0;
        double sum_w = 0;
        double sum_b = 0;
        double sum_a = 0;
        for (int i = 0; i < 1000; i++) {
            input = (double)(rand() % 101) / 10;
            // cout<<input<<" - ";
            intermediate = input * weight + bias;
            output = func(intermediate);
            double desired = 2 * input;
            // cout<<"here: "<<input<<" "<<desired<<endl;
            cost = (desired - output) * (desired - output);
            // cout << cost << endl;
            sum_cost += cost;
            double w, b, a;
            w = 2 * (desired - output) * input;
            b = 2 * (desired - output);
            a = 2 * (desired - output) * weight;
            sum_w += w;
            sum_b += b;
            sum_a += a;
        }
        double gradient_w = sum_w / 1000;
        double gradient_b = sum_b / 1000;
        // double gradient_a = sum_a / 10000;
        weight = weight + gradient_w * rate_w / 1000000;
        bias = bias + gradient_b * rate_b / 1000000;
        // cout << gradient_w << " " << gradient_b << " " << gradient_a <<
        // endl; cout << weight << " " << bias << endl;
        // rate_w = rate_w / 10;
        rate_w--;
        rate_b--;
    }

    cout << "average cost: " << sum_cost / 1000 << endl;
    cout << weight << " " << bias << endl;
    rate_w=1000;
    rate_b=1000;
    }
}