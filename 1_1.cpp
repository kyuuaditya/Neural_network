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
    double multiplier=1000000;
    double iterations=1000;
    double examples=1000;
    double input;
    double output;
    double weight = 100;
    double bias = 100;
    double intermediate;
    double cost;
    for(int k=0;k<100;k++){
        double sum_cost = 0;
        for (int j = 0; j < iterations; j++) {
            sum_cost = 0;
            double sum_w = 0;
            double sum_b = 0;
            double sum_a = 0;
            for (int i = 0; i < examples; i++) {
                input = (double)(rand() % 101) / 10;
                // cout<<input<<" - ";
                intermediate = input * weight + bias;
                output = func(intermediate);
                double desired = 5*input+6;
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
            double gradient_w =(double) sum_w / examples;
            double gradient_b =(double) sum_b / examples;
            // double gradient_a = sum_a / 10000;
            weight = weight + gradient_w * rate_w / multiplier;
            bias = bias + gradient_b * rate_b / multiplier;
            // cout << gradient_w << " " << gradient_b << " " << gradient_a <<
            // endl; cout << weight << " " << bias << endl;
            // rate_w = rate_w / 10;
            rate_w--;
            rate_b--;
            // cout << "average cost: " << sum_cost / examples << endl;
        }
    cout << "run cost: " << sum_cost / examples << endl;
    cout << "weight: "<<weight << " "<<"bias: " << bias << endl;
    rate_w=1000;
    rate_b=1000;
    }
}