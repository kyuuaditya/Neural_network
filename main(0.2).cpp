#include <iostream>
using namespace std;

float normalise(float value) {
    if(value>0){
        return value;
    }else{
        return 0;
    }
    // float a = value / (1 + abs(value));
    // return a;
}

float derivative(float value) {
    if(value>0){
        return 1;
    }else{
        return 0;
    }
    // float a = 1 / ((1 + abs(value)) * (1 + abs(value)));
    // return a;
}

float generate_random() {
    int temp = rand() % 101 - 50;
    float num = (float)temp / 50;
    return num;
}

int main() {
    // set number of times to train full set.
    int iterations = 10;
    float rate = 0.1;
    int examples = 10;

    // setting size of layers.
    int input_size = 8;
    int layer1_size = 4;
    int layer2_size = 4;
    int output_size = 2;

    // stores the values of desired results.
    float result_desired[output_size] = {0};
    float cost[output_size];

    // neurons / activations container.
    float n_input[input_size];
    float n_layer1[layer1_size];
    float n_layer2[layer2_size];
    float n_output[output_size];

    // before normalisation.
    float z_layer1[layer1_size];
    float z_layer2[layer2_size];
    float z_output[output_size];

    // set by number of total layers -1
    float weights_l1[input_size][layer1_size];
    float weights_l2[layer1_size][layer2_size];
    float weights_op[layer2_size][output_size];

    // declaring bias
    float bias_l1[layer1_size];
    float bias_l2[layer2_size];
    float bias_op[output_size];

    // reset random variables
    srand(time(0));

    // assigning random weights and bias.
    for (int j = 0; j < layer1_size; j++) {
        for (int i = 0; i < input_size; i++) {
            weights_l1[i][j] = generate_random();
        }
        bias_l1[j] = generate_random();
    }
    for (int j = 0; j < layer2_size; j++) {
        for (int i = 0; i < layer1_size; i++) {
            weights_l2[i][j] = generate_random();
        }
        bias_l2[j] = generate_random();
    }
    for (int j = 0; j < output_size; j++) {
        for (int i = 0; i < layer2_size; i++) {
            weights_op[i][j] = generate_random();
        }
        bias_op[j] = generate_random();
    }

    // training dataset iterations
    int run = 0;
    int total_values = input_size * layer1_size + layer1_size * layer2_size +
                       layer2_size * output_size + layer2_size + layer1_size +
                       output_size;
    float linear_gradient[examples][total_values] = {0};

    // declaring cost array
    float gradient_weights_l1[input_size][layer1_size];
    float gradient_bias_l1[layer1_size];
    float gradient_weights_l2[layer1_size][layer2_size];
    float gradient_bias_l2[layer2_size];
    float gradient_weights_op[layer2_size][output_size];
    float gradient_bias_op[output_size];
    float gradient_activation_l1[layer1_size];
    float gradient_activation_l2[layer2_size];

    // loop for generations
    for (int train = 0; train < iterations; train++) {
        gradient_weights_l1[input_size][layer1_size] = {0};
        gradient_bias_l1[layer1_size] = {0};
        gradient_weights_l2[layer1_size][layer2_size] = {0};
        gradient_bias_l2[layer2_size] = {0};
        gradient_weights_op[layer2_size][output_size] = {0};
        gradient_bias_op[output_size] = {0};
        gradient_activation_l1[layer1_size] = {0};
        gradient_activation_l2[layer2_size] = {0};

        run = 0;
        float cost_total[examples][output_size] = {0};

        // second loop for training
        for (int exam = 0; exam < examples; exam++) {
            // settting random values in input neurons.
            for (int i = 0; i < input_size; i++) {
                n_input[i] = generate_random();
            }

            // calculations for first layer
            z_layer1[layer1_size] = {0};
            for (int i = 0; i < layer1_size; i++) {
                for (int j = 0; j < input_size; j++) {
                    z_layer1[i] += n_input[j] * weights_l1[j][i];
                }
                z_layer1[i] += bias_l1[i];
                n_layer1[i] = normalise(z_layer1[i]);
            }
            // calculations for second layer
            for (int i = 0; i < layer2_size; i++) {
                for (int j = 0; j < layer1_size; j++) {
                    z_layer2[i] += n_layer1[j] * weights_l2[j][i];
                }
                z_layer1[i] += bias_l2[i];
                n_layer2[i] = normalise(z_layer2[i]);
            }
            // calculations for third layer
            for (int i = 0; i < output_size; i++) {
                for (int j = 0; j < layer2_size; j++) {
                    z_output[i] += n_layer2[j] * weights_op[j][i];
                }
                z_layer1[i] += bias_op[i];
                n_output[i] = normalise(z_output[i]);
                // cout << n_output[i] << endl;
            }

            // *change accordingly
            // desired outcome.
            result_desired[0] = n_input[0];
            result_desired[1] = 0.1;

            // cost function.
            for (int i = 0; i < output_size; i++) {
                cost[i] = (abs(result_desired[i]) - abs(n_output[i])) *
                          (abs(result_desired[i]) - abs(n_output[i]));
            }
            cost_total[run][0] = cost[0];
            cost_total[run][1] = cost[1];
            // cout << cost[0] << " " << cost[1] << endl;

            float a, b, c = 0;
            // finding weight gradient
            for (int i = 0; i < output_size; i++) {
                a = 2 *  (n_output[i] - result_desired[i]);
                b = derivative(z_output[i]);
                for (int j = 0; j < layer2_size; j++) {
                    c = n_output[j];
                    gradient_weights_op[j][i] = a * b * c;
                }
            }

            // finding bias gradient
            for (int i = 0; i < output_size; i++) {
                a = 2 * (n_output[i] - result_desired[i]);
                b = derivative(z_output[i]);
                gradient_bias_op[i] = a * b;
            }

            // finding activation gradient
            for (int i = 0; i < output_size; i++) {
                c = 0;
                a = 2 *  (n_output[i] - result_desired[i]);
                b = derivative(z_output[i]);
                for (int j = 0; j < layer2_size; j++) {
                    c += weights_op[j][i];
                    gradient_activation_l2[j] = a * b * c;
                }
            }

            // ? layer 2

            // finding weight gradient
            for (int i = 0; i < layer2_size; i++) {
                a = 2 *  (gradient_activation_l2[i]);
                b = derivative(z_layer2[i]);
                for (int j = 0; j < layer2_size; j++) {
                    c = n_layer2[j];
                    gradient_weights_l2[j][i] = a * b * c;
                }
            }

            // finding bias gradient
            for (int i = 0; i < layer2_size; i++) {
                a = 2 *  (gradient_activation_l2[i]);
                b = derivative(z_layer2[i]);
                gradient_bias_l2[i] = a * b;
            }

            // finding activation gradient
            for (int i = 0; i < layer2_size; i++) {
                c = 0;
                a = 2 * (gradient_activation_l2[i]);
                b = derivative(z_layer2[i]);
                for (int j = 0; j < layer1_size; j++) {
                    c += weights_l2[j][i];
                    gradient_activation_l1[i] = a * b * c;
                }
            }

            // ? layer 2

            // finding weight gradient
            for (int i = 0; i < layer1_size; i++) {
                a = 2 *  (gradient_activation_l1[i]);
                b = derivative(z_layer1[i]);
                for (int j = 0; j < layer1_size; j++) {
                    c = n_layer1[j];
                    gradient_weights_l1[j][i] = a * b * c;
                }
            }

            // finding bias gradient
            for (int i = 0; i < layer1_size; i++) {
                a = 2 *  (gradient_activation_l2[i]);
                b = derivative(z_layer1[i]);
                gradient_bias_l1[i] = a * b;
            }

            // // finding activation gradient
            // for (int i = 0; i < layer1_size; i++) {
            //     c = 0;
            //     a = 2 * (gradient_activation_l1[i]);
            //     b = derivative(z_layer1[i]);
            //     for (int j = 0; j < input_size; j++) {
            //         c += weights_l1[j][i];
            //         gradient_activation_l1[i] = a * b * c;
            //     }
            // }
            int num = 0;
            for (int i = 0; i < input_size; i++) {
                for (int j = 0; j < layer1_size; j++) {
                    linear_gradient[run][num] = gradient_weights_l1[i][j];
                    num++;
                }
            }
            for (int i = 0; i < layer1_size; i++) {
                for (int j = 0; j < layer2_size; j++) {
                    linear_gradient[run][num] = gradient_weights_l2[i][j];
                    num++;
                }
            }
            for (int i = 0; i < layer2_size; i++) {
                for (int j = 0; j < output_size; j++) {
                    linear_gradient[run][num] = gradient_weights_op[i][j];
                    num++;
                }
            }
            for (int j = 0; j < layer1_size; j++) {
                linear_gradient[run][num] = gradient_bias_l1[j];
                num++;
            }
            for (int j = 0; j < layer2_size; j++) {
                linear_gradient[run][num] = gradient_bias_l2[j];
                num++;
            }
            for (int j = 0; j < output_size; j++) {
                linear_gradient[run][num] = gradient_bias_op[j];
                num++;
            }
            run++;
        }

        float sum_cost1 = 0;
        float sum_cost2 = 0;
        for (int i = 0; i < examples; i++) {
            sum_cost1 += cost_total[i][0];
            sum_cost2 += cost_total[i][1];
        }
        cout << sum_cost1 / examples << " " << sum_cost2 / examples << endl;

        float sum_gradient[total_values] = {0};

        // calculating average gradient.
        for (int i = 0; i < total_values; i++) {
            for (int j = 0; j < examples; j++) {
                sum_gradient[i] += linear_gradient[j][i];
            }
        }
        float average_gradient[total_values] = {0};
        for (int i = 0; i < total_values; i++) {
            average_gradient[i] = (rate * sum_gradient[i]) / examples;
            // cout << average_gradient[i] << " ";
        }
        cout << endl;
        int num = 0;
        for (int i = 0; i < input_size; i++) {
            for (int j = 0; j < layer1_size; j++) {
                gradient_weights_l1[i][j] =
                    gradient_weights_l1[i][j] - average_gradient[num];
                num++;
            }
        }
        for (int i = 0; i < layer1_size; i++) {
            for (int j = 0; j < layer2_size; j++) {
                gradient_weights_l2[i][j] =
                    gradient_weights_l2[i][j] - average_gradient[num];
                num++;
            }
        }
        for (int i = 0; i < layer2_size; i++) {
            for (int j = 0; j < output_size; j++) {
                gradient_weights_op[i][j] =
                    gradient_weights_op[i][j] - average_gradient[num];
                num++;
            }
        }
        for (int j = 0; j < layer1_size; j++) {
            gradient_bias_l1[j] = gradient_bias_l1[j] - average_gradient[num];
            num++;
        }
        for (int j = 0; j < layer2_size; j++) {
            gradient_bias_l2[j] = gradient_bias_l2[j]-average_gradient[num];
            num++;
        }
        for (int j = 0; j < output_size; j++) {
            gradient_bias_op[j] = gradient_bias_op[j] - average_gradient[num];
            num++;
        }
    }
}