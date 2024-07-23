#include <fstream>
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

    ofstream myfile;
    myfile.open("file.txt");

    double rate_w = 1000;
    double rate_b = 1000;
    double multiplier_w = 1000000;
    double multiplier_b = 1000000;
    double updates = 200;
    double iterations = 1000;
    double examples = 1000;

    int input_size = 4;
    int output_size = 4;

    double desired[output_size] = {0};

    double input[input_size];
    double output[output_size];
    double bias[output_size] = {100};
    double weight[input_size][output_size] = {100};
    double intermediate[output_size];
    double cost[output_size];

    for (int loop1 = 0; loop1 < updates; loop1++) {
        double sum_cost[output_size] = {0};
        for (int loop2 = 0; loop2 < iterations; loop2++) {
            for (int i = 0; i < output_size; i++) {
                sum_cost[i] = 0;
            }
            double sum_b[output_size] = {0};
            double sum_w[input_size][output_size] = {0};
            for (int loop3 = 0; loop3 < examples; loop3++) {
                for (int i = 0; i < input_size; i++) {
                    input[i] = (double)(rand() % 101) / 100;
                }
                for (int i = 0; i < output_size; i++) {
                    double temp = 0;
                    for (int j = 0; j < input_size; j++) {
                        temp += input[j] * weight[j][i];
                    }
                    intermediate[i] = temp + bias[i];
                }
                for (int i = 0; i < output_size; i++) {
                    output[i] = func(intermediate[i]);
                }
                // !desired all out comes to train for.
                desired[0] = 35 * input[0] + 62 * input[1] + 55 * input[2] +
                             61 * input[3] +32;
                desired[1] = 56 * input[0] + 50 * input[1] + 86 * input[2] +
                             12 * input[3] + 71;
                desired[2] = 86 * input[0] + 48 * input[1] + 32 * input[2] +
                             35 * input[3] + 68;
                desired[3] = 21 * input[0] + 65 * input[1] + 58 * input[2] +
                             49 * input[3] + 69;
                for (int i = 0; i < output_size; i++) {
                    cost[i] =
                        (desired[i] - output[i]) * (desired[i] - output[i]);
                }
                for (int i = 0; i < output_size; i++) {
                    sum_cost[i] += cost[i];
                }
                double w[input_size][output_size];
                double b[output_size];
                for (int i = 0; i < output_size; i++) {
                    for (int j = 0; j < input_size; j++) {
                        w[j][i] = 2 * (desired[i] - output[i]) * input[j];
                        sum_w[j][i] += w[j][i];
                    }
                }
                for (int i = 0; i < output_size; i++) {
                    b[i] = 2 * (desired[i] - output[i]);
                    sum_b[i] += b[i];
                }
            }
            double gradient_w[input_size][output_size];
            for (int i = 0; i < output_size; i++) {
                for (int j = 0; j < input_size; j++) {
                    gradient_w[j][i] = sum_w[j][i];
                }
            }
            double gradient_b[output_size];
            for (int i = 0; i < output_size; i++) {
                gradient_b[i] = (double)sum_b[i] / examples;
            }
            for (int i = 0; i < output_size; i++) {
                for (int j = 0; j < input_size; j++) {
                    weight[j][i] += gradient_w[j][i] * rate_w / multiplier_w;
                }
            }
            for (int i = 0; i < output_size; i++) {
                bias[i] = bias[i] + gradient_b[i] * (rate_b / multiplier_b);
            }
            rate_w--;
            rate_b--;
        }

        for (int i = 0; i < output_size; i++) {
            cout << "cost_" << i << ": " << sum_cost[i] / examples << " ";
            myfile << sum_cost[i] / examples << " ";
        }
        myfile << endl;
        cout << endl;
        rate_w = 1000;
        rate_b = 1000;
    }
    for (int i = 0; i < output_size; i++) {
        for (int j = 0; j < input_size; j++) {
            cout << "weight[" << j << "][" << i << "]: " << weight[j][i] << " ";
        }
        cout << "bias[" << i << "]: " << bias[i];
        cout << endl;
    }
}