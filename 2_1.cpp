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
    double multiplier = 10000000;
    double iterations = 1000;
    double examples = 1000;
    double input;
    double input2;
    double input3;
    double input4;
    double input5;
    double input6;
    double input7;
    double input8;
    double output;
    double weight = 5.0044;
    double bias = 0.991297;
    double weight2 = 2.00236;
    double weight3 = 7.00396;
    double weight4 = -2.00347;
    double weight5 = 6.00373;
    double weight6 = -6.00282;
    double weight7 = 5.00319;
    double weight8 = 4.0037;
    double intermediate;
    double cost;
    double low_cost = 1000000;
    double best_weight;
    double best_weight2;
    double best_weight3;
    double best_weight4;
    double best_weight5;
    double best_weight6;
    double best_weight7;
    double best_weight8;
    double best_bias;
    for (int k = 0; k < 1000; k++) {
        double sum_cost = 0;
        for (int j = 0; j < iterations; j++) {
            sum_cost = 0;
            double sum_w = 0;
            double sum_b = 0;
            double sum_w2 = 0;
            double sum_w3 = 0;
            double sum_w4 = 0;
            double sum_w5 = 0;
            double sum_w6 = 0;
            double sum_w7 = 0;
            double sum_w8 = 0;

            for (int i = 0; i < examples; i++) {
                input = (double)(rand() % 101) / 100;
                input2 = (double)(rand() % 101) / 100;
                input3 = (double)(rand() % 101) / 100;
                input4 = (double)(rand() % 101) / 100;
                input5 = (double)(rand() % 101) / 100;
                input6 = (double)(rand() % 101) / 100;
                input7 = (double)(rand() % 101) / 100;
                input8 = (double)(rand() % 101) / 100;
                // cout<<input<<" - ";
                intermediate = input * weight + input2 * weight2 +
                               input3 * weight3 + input4 * weight4 +
                               input5 * weight5 + input6 * weight6 +
                               input7 * weight7 + input8 * weight8 + bias;
                output = func(intermediate);
                double desired = 5 * input + 2 * input2 + 7 * input3 +
                                 (-2) * input4 + 6 * input5 + (-6) * input6 +
                                 5 * input7 + 4 * input8 + 1;
                // cout<<"here: "<<input<<" "<<desired<<endl;
                cost = (desired - output) * (desired - output);
                // cout << cost << endl;
                sum_cost += cost;
                double w, b, a, w2, w3, w4, w5, w6, w7, w8;
                w = 2 * (desired - output) * input;
                w2 = 2 * (desired - output) * input2;
                w3 = 2 * (desired - output) * input3;
                w4 = 2 * (desired - output) * input4;
                w5 = 2 * (desired - output) * input5;
                w6 = 2 * (desired - output) * input6;
                w7 = 2 * (desired - output) * input7;
                w8 = 2 * (desired - output) * input8;
                b = 2 * (desired - output);
                a = 2 * (desired - output) * weight;
                sum_w += w;
                sum_b += b;
                sum_w2 += w2;
                sum_w3 += w3;
                sum_w4 += w4;
                sum_w5 += w5;
                sum_w6 += w6;
                sum_w7 += w7;
                sum_w8 += w8;
            }
            double gradient_w = (double)sum_w / examples;
            double gradient_w2 = (double)sum_w2 / examples;
            double gradient_w3 = (double)sum_w3 / examples;
            double gradient_w4 = (double)sum_w4 / examples;
            double gradient_w5 = (double)sum_w5 / examples;
            double gradient_w6 = (double)sum_w6 / examples;
            double gradient_w7 = (double)sum_w7 / examples;
            double gradient_w8 = (double)sum_w8 / examples;
            double gradient_b = (double)sum_b / examples;
            // double gradient_a = sum_a / 10000;
            weight = weight + gradient_w * rate_w / multiplier;
            weight2 = weight2 + gradient_w2 * rate_w / multiplier;
            weight3 = weight3 + gradient_w3 * rate_w / multiplier;
            weight4 = weight4 + gradient_w4 * rate_w / multiplier;
            weight5 = weight5 + gradient_w5 * rate_w / multiplier;
            weight6 = weight6 + gradient_w6 * rate_w / multiplier;
            weight7 = weight7 + gradient_w7 * rate_w / multiplier;
            weight8 = weight8 + gradient_w8 * rate_w / multiplier;
            bias = bias + gradient_b * (rate_b / multiplier * 10);
            if (sum_cost < low_cost) {
                low_cost = sum_cost;
                best_weight = weight;
                best_weight2 = weight2;
                best_weight3 = weight3;
                best_weight4 = weight4;
                best_weight5 = weight5;
                best_weight6 = weight6;
                best_weight7 = weight7;
                best_weight8 = weight8;
                best_bias = bias;
            }
            // cout << gradient_w << " " << gradient_b << " " << gradient_a <<
            // endl; cout << weight << " " << bias << endl;
            // rate_w = rate_w / 10;
            // cout << "average cost: " << sum_cost / examples << endl;
            rate_w--;
            rate_b--;
        }
        // weight = best_weight;
        // weight2 = best_weight2;
        // weight3 = best_weight3;
        // weight4 = best_weight4;
        // weight5 = best_weight5;
        // weight6 = best_weight6;
        // weight7 = best_weight7;
        // weight8 = best_weight8;
        // bias = best_bias;
        cout << "run cost: " << sum_cost / examples << endl;
        cout << "weight: " << weight << " " << "weight2: " << weight2 << " "
             << "weight3: " << weight3 << " " << "weight4: " << weight4 << " "
             << "weight5: " << weight5 << " " << "weight6: " << weight6 << " "
             << "weight7: " << weight7 << " " << "weight8: " << weight8 << " "
             << "bias: " << bias << endl;
        rate_w = 1000;
        rate_b = 1000;
        // if(sum_cost/examples<0.01){
        //     multiplier=10000000;
        // }
        // if(sum_cost/examples<0.001){
        //     multiplier=100000000;
        // }
        // if(sum_cost/examples<0.0001){
        //     multiplier=1000000000;
        // }
    }
    // cout<<input<<endl;
}