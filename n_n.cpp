#include <math.h>

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

    int input_size = 144;
    int output_size = 2;
    int speed = 1;

    double rate_w = 1000;
    double rate_b = 1000;
    double multiplier_w = 500000 * input_size;
    double multiplier_b = 500000 * input_size;

    double iterations = 5000;
    double examples = 1000;

    double desired[output_size];
    for (int i = 0; i < output_size; i++) {
        desired[i] = 0;
    }

    double input[input_size] = {0};
    double output[output_size];
    double bias[output_size];
    double weight[input_size][output_size];
    for (int j = 0; j < output_size; j++) {
        for (int i = 0; i < input_size; i++) {
            weight[i][j] = 0;
        }
    }
    for (int i = 0; i < output_size; i++) {
        bias[i] = 0;
    }
    double intermediate[output_size];
    double cost[output_size];

    double sum_cost[output_size];
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
            desired[0] = 5 * input[0] + 2 * input[1] + 5 * input[2] +
                         3 * input[3] + 2 * input[4] + 1 * input[5] +
                         3 * input[6] + 1 * input[7] + 7 * input[8] +
                         6 * input[9];
            desired[1] = 3 * input[0] + 7 * input[1] + 0 * input[2] +
                         4 * input[3] + 7 * input[4] + 7 * input[5] +
                         0 * input[6] + 4 * input[7] + 3 * input[8] +
                         5 * input[9];
            
            for (int i = 0; i < output_size; i++) {
                cost[i] = (desired[i] - output[i]) * (desired[i] - output[i]);
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
        for (int i = 0; i < output_size; i++) {
            cout << "cost_" << i << ": " << sum_cost[i] / examples << " ";
        }
        cout << endl;
    }
}