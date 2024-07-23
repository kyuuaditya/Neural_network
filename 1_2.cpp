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
    double multiplier = 1000000;
    double iterations = 1000;
    double examples = 1000;
    double input;
    double input2;
    double output;
    double output2;
    double weight = 100;
    double weight2 = 100;
    double bias = 100;
    double bias2 = 100;
    double intermediate;
    double intermediate2;
    double cost;
    double cost2;
    for (int k = 0; k < 100; k++) {
        double sum_cost = 0;
        double sum_cost2 = 0;
        for (int j = 0; j < iterations; j++) {
            sum_cost = 0;
            sum_cost2 = 0;
            double sum_w = 0;
            double sum_b = 0;
            double sum_a = 0;

            double sum_w2 = 0;
            double sum_b2 = 0;
            double sum_a2 = 0;
            for (int i = 0; i < examples; i++) {
                input = (double)(rand() % 101) / 10;
                input = (double)(rand() % 101) / 10;
                // cout<<input<<" - ";
                intermediate = input * weight + bias;
                intermediate2 = input2 * weight2 + bias2;
                output = func(intermediate);
                output2=func(intermediate2);
                double desired = 5 * input + 6;
                double desired2=2*input2+8;
                // cout<<"here: "<<input<<" "<<desired<<endl;
                cost = (desired - output) * (desired - output);
                cost2 = (desired2 - output2) * (desired2 - output2);
                // cout << cost << endl;
                sum_cost += cost;
                sum_cost2 += cost2;
                double w, b, a;
                double w2,b2,a2;
                w = 2 * (desired - output) * input;
                b = 2 * (desired - output);
                a = 2 * (desired - output) * weight;
                w2 = 2 * (desired2 - output2) * input2;
                b2 = 2 * (desired2 - output2);
                a2 = 2 * (desired2 - output2) * weight2;
                sum_w += w;
                sum_b += b;
                sum_a += a;
                sum_w2 += w2;
                sum_b2 += b2;
                sum_a2 += a2;
            }
            double gradient_w = (double)sum_w / examples;
            double gradient_b = (double)sum_b / examples;
            double gradient_w2 = (double)sum_w2 / examples;
            double gradient_b2 = (double)sum_b2 / examples;
            // double gradient_a = sum_a / 10000;
            weight = weight + gradient_w * rate_w / multiplier;
            bias = bias + gradient_b * rate_b / multiplier;

            weight2 = weight2 + gradient_w2 * rate_w / multiplier;
            bias2 = bias2 + gradient_b2 * rate_b / multiplier;
            // cout << gradient_w << " " << gradient_b << " " << gradient_a <<
            // endl; cout << weight << " " << bias << endl;
            // rate_w = rate_w / 10;
            rate_w--;
            rate_b--;
            // cout << "average cost: " << sum_cost / examples << endl;
        }
        cout << "run cost: " << sum_cost / examples << endl;
        cout << "run cost2: " << sum_cost2 / examples << endl;
        cout << "weight: " << weight << " " << "bias: " << bias <<" "<<"weight2: " << weight2 << " " << "bias2: " << bias2<< endl;
        rate_w = 1000;
        rate_b = 1000;
    }
}