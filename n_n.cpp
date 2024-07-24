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

    int input_size = 100;
    int output_size = 16;
    int speed = 1;

    double rate_w = 1000;
    double rate_b = 1000;
    double multiplier_w = 1000000 * input_size;
    double multiplier_b = 1000000 * input_size;

    double updates = 20;
    double iterations = 500;
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
                        // cout << temp << " " << input[j] << " " <<
                        // weight[j][i]
                        //      << endl;
                    }
                    intermediate[i] = temp + bias[i];
                    // cout << "intermediate[" << i << "]: " << intermediate[i]
                    //      << endl;
                }
                for (int i = 0; i < output_size; i++) {
                    output[i] = func(intermediate[i]);
                }
                // cout << "output: " << output[0] << " " << output[1] << endl;
                // !desired all out comes to train for.
                desired[0] = 5 * input[0] + 2 * input[1] + 5 * input[2] +
                             3 * input[3] + 2 * input[4] + 1 * input[5] +
                             3 * input[6] + 1 * input[7] + 7 * input[8] +
                             6 * input[9];
                desired[1] = 3 * input[0] + 7 * input[1] + 0 * input[2] +
                             4 * input[3] + 7 * input[4] + 7 * input[5] +
                             0 * input[6] + 4 * input[7] + 3 * input[8] +
                             5 * input[9];
                desired[2] = 9 * input[0] + 1 * input[1] + 6 * input[2] +
                             0 * input[3] + 1 * input[4] + 5 * input[5] +
                             1 * input[6] + 5 * input[7] + 3 * input[8] +
                             1 * input[9];
                desired[3] = 3 * input[0] + 6 * input[1] + 4 * input[2] +
                             4 * input[3] + 2 * input[4] + 5 * input[5] +
                             6 * input[6] + 1 * input[7] + 1 * input[8] +
                             7 * input[9];
                desired[4] = 9 * input[0] + 7 * input[1] + 2 * input[2] +
                             1 * input[3] + 1 * input[4] + 2 * input[5] +
                             2 * input[6] + 3 * input[7] + 8 * input[8] +
                             3 * input[9];
                desired[5] = 8 * input[0] + 9 * input[1] + 1 * input[2] +
                             1 * input[3] + 6 * input[4] + 4 * input[5] +
                             1 * input[6] + 6 * input[7] + 4 * input[8] +
                             6 * input[9];
                desired[6] = 5 * input[0] + 5 * input[1] + 4 * input[2] +
                             9 * input[3] + 8 * input[4] + 4 * input[5] +
                             5 * input[6] + 6 * input[7] + 2 * input[8] +
                             4 * input[9];
                desired[7] = 6 * input[0] + 8 * input[1] + 7 * input[2] +
                             5 * input[3] + 1 * input[4] + 4 * input[5] +
                             8 * input[6] + 9 * input[7] + 2 * input[8] +
                             3 * input[9];
                for (int i = 0; i < output_size; i++) {
                    cost[i] =
                        (desired[i] - output[i]) * (desired[i] - output[i]);
                }
                // cout << cost[0] << " " << cost[1] << endl;
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
                // cout<<endl;
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
            // cout<<endl;
        }

        for (int i = 0; i < output_size; i++) {
            cout << "cost_" << i << ": " << sum_cost[i] / examples << " ";
            myfile << sum_cost[i] / examples << " ";
        }
        myfile << endl;
        cout << endl;
        rate_w = 1000;
        rate_b = 1000;

        if (updates == 300) {
            if (loop1 > 50) {
                multiplier_w = 10000000 * input_size;
            }
            if (loop1 > 100) {
                multiplier_w = 100000000 * input_size;
            }
            if (loop1 > 150) {
                multiplier_w = 1000000000 * input_size;
            }
            if (loop1 > 200) {
                multiplier_w = 10000000000 * input_size;
            }
            if (loop1 > 250) {
                multiplier_w = 100000000000 * input_size;
            }
        }
    }
    for (int i = 0; i < output_size; i++) {
        for (int j = 0; j < input_size; j++) {
            // cout << "weight[" << j << "][" << i << "]: " << weight[j][i] << "
            // ";
        }
        // cout << "bias[" << i << "]: " << bias[i];
        // cout << endl;
    }
}