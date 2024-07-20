#include <iostream>
using namespace std;

float apx(float value) {
    float a = value / (1 + abs(value));
    return a;
}

float derip(float value) {
    float a = 1 / ((1 + abs(value)) * (1 + abs(value)));
    return a;
}

float derin(float value) {
    float a = 1 / ((1 - abs(value)) * (1 - abs(value)));
    return a;
}

float gen() {
    int temp = rand() % 101 - 50;
    float num = (float)temp / 50;
    return num;
}

int main() {
    float cost;
    float cost_gradient_array[2][6] = {0};
    float temp;

    float z_a[3];
    float in[1];
    float l1[1];
    float l2[1];
    float re[1];

    srand(time(0));

    float w_in[1];
    float b_in[1];

    float w_l1[1];
    float b_l1[1];

    float w_l2[1];
    float b_l2[1];

    float y = 1;

    // w_in[0]=gen();
    // b_in[0]=gen();
    // w_l1[0]=gen();
    // b_l1[0]=gen();
    // w_l2[0]=gen();
    // b_l2[0]=gen();

    w_in[0] = 0.56;
    b_in[0] = 0.19;
    w_l1[0] = 0.65;
    b_l1[0] = -0.27;
    w_l2[0] = 0.10;
    b_l2[0] = 0.40;
    int iterations = 3;
    // float result_cost[iterations];
    float result_sum = 0;

    int run;
    for (int loops = 0; loops < iterations; loops++) {
        run = 0;
        cost_gradient_array[2][6] = {0};
        for (int itr = 0; itr < 2; itr++) {
            // cin >> in[0];
            // in[0]=0.6;
            in[0] = gen();

            // ! here

            // * layer 1
            z_a[0] = in[0] * w_in[0] + b_in[0];
            l1[0] = apx(z_a[0]);

            // * layer 2
            z_a[1] = in[0] * w_l1[0] + b_l1[0];
            l2[0] = apx(z_a[1]);

            // * result
            z_a[2] = in[0] * w_l2[0] + b_l2[0];
            re[0] = apx(z_a[2]);

            cost = (re[0] - y) * (re[0] - y);

            float gradient_a[3][3];
            float gradient_w[3][3];
            float gradient_b[3][2];

            float cost_gradient_a[3];
            float cost_gradient_w[3];
            float cost_gradient_b[3];

            // ! last layer
            gradient_w[0][0] = 2 * (re[0] - y);
            if (z_a[0] < 0) {
                gradient_w[0][1] = derin(z_a[0]);
            } else {
                gradient_w[0][1] = derip(z_a[0]);
            }
            gradient_w[0][2] = l2[0];

            gradient_b[0][0] = 2 * (re[0] - y);
            if (z_a[0] < 0) {
                gradient_b[0][1] = derin(z_a[0]);
            } else {
                gradient_b[0][1] = derip(z_a[0]);
            }

            gradient_a[0][0] = 2 * (re[0] - y);
            if (z_a[0] < 0) {
                gradient_a[0][1] = derin(z_a[0]);
            } else {
                gradient_a[0][1] = derip(z_a[0]);
            }
            gradient_a[0][2] = w_l2[0];

            cost_gradient_w[0] =
                gradient_w[0][0] * gradient_w[0][1] * gradient_w[0][2];
            cost_gradient_b[0] = gradient_b[0][0] * gradient_b[0][1];
            cost_gradient_a[0] =
                gradient_a[0][0] * gradient_a[0][1] * gradient_a[0][2];

            // ! 2nd last layer
            // gradient_w[1][0]=2*(l2[0]-y);
            // gradient_w[1][0] = 2 * (cost_gradient_w[0] * cost_gradient_w[0]);
            gradient_w[1][0] = 2 * (cost_gradient_a[0]);
            if (z_a[1] < 0) {
                gradient_a[0][1] = derin(z_a[0]);
            } else {
                gradient_a[0][1] = derip(z_a[0]);
            }
            gradient_w[1][2] = l1[0];

            // gradient_b[1][0]=2*(l2[0]-y);
            // gradient_b[1][0] = 2 * (cost_gradient_b[0] * cost_gradient_b[0]);
            gradient_b[1][0] = 2 * (cost_gradient_a[0]);
            if (z_a[1] < 0) {
                gradient_a[0][1] = derin(z_a[0]);
            } else {
                gradient_a[0][1] = derip(z_a[0]);
            }

            // gradient_a[1][0] = 2 * (cost_gradient_a[0] * cost_gradient_a[0]);
            gradient_a[1][0] = 2 * (cost_gradient_a[0]);
            if (z_a[1] < 0) {
                gradient_a[0][1] = derin(z_a[0]);
            } else {
                gradient_a[0][1] = derip(z_a[0]);
            }
            gradient_a[1][2] = w_l1[0];

            cost_gradient_w[1] =
                gradient_w[1][0] * gradient_w[1][1] * gradient_w[1][2];
            cost_gradient_b[1] = gradient_b[1][0] * gradient_b[1][1];
            cost_gradient_a[1] =
                gradient_a[1][0] * gradient_a[1][1] * gradient_a[1][2];

            // ! 3
            // gradient_w[2][0] = 2 * (cost_gradient_w[1] * cost_gradient_w[1]);
            gradient_w[2][0] = 2 * (cost_gradient_a[1]);
            if (z_a[2] < 0) {
                gradient_a[0][1] = derin(z_a[0]);
            } else {
                gradient_a[0][1] = derip(z_a[0]);
            }
            gradient_w[2][2] = in[0];

            // gradient_b[2][0] = 2 * (cost_gradient_b[1] * cost_gradient_b[1]);
            gradient_b[2][0] = 2 * (cost_gradient_a[1]);
            if (z_a[2] < 0) {
                gradient_a[0][1] = derin(z_a[0]);
            } else {
                gradient_a[0][1] = derip(z_a[0]);
            }

            // gradient_a[2][0] = 2 * (cost_gradient_a[1] * cost_gradient_a[1]);
            gradient_a[2][0] = 2 * (cost_gradient_a[1]);
            if (z_a[2] < 0) {
                gradient_a[0][1] = derin(z_a[0]);
            } else {
                gradient_a[0][1] = derip(z_a[0]);
            }
            gradient_a[2][2] = w_in[0];

            cost_gradient_w[2] =
                gradient_w[2][0] * gradient_w[2][1] * gradient_w[2][2];
            cost_gradient_b[2] = gradient_b[2][0] * gradient_b[2][1];
            cost_gradient_a[2] =
                gradient_a[2][0] * gradient_a[2][1] * gradient_a[2][2];

            for (int i = 0; i < 3; i++) {
                cost_gradient_array[run][i] = cost_gradient_b[i];
            }

            for (int i = 0; i < 3; i++) {
                cost_gradient_array[run][i + 3] = cost_gradient_w[i];
            }

            run++;

            result_sum = result_sum + re[0];
            // cout << "result: " << re[0] << endl;
            // cout << "cost: " << cost << endl;
        }
        float sum[6] = {0};
        float average_cost[6];
        for (int i = 0; i < run + 1; i++) {
            for (int j = 0; j < 6; j++) {
                sum[j] += cost_gradient_array[i][j];
            }
        }
        for (int i = 0; i < 6; i++) {
            average_cost[i] = sum[i] / (run + 1);
        }
        for (int i = 0; i < 6; i++) {
            // cout << average_cost[i] << endl;
        }
        cout << w_in[0] << " " << b_in[0] << " " << w_l1[0] << " " << b_l1[0]
             << " " << w_l2[0] << " " << b_l2[0] << endl;
        w_in[0] = w_in[0] + average_cost[5];
        b_in[0] = b_in[0] + average_cost[2];
        w_l1[0] = w_l1[0] + average_cost[4];
        w_l2[0] = w_l2[0] + average_cost[3];
        b_l1[0] = b_l1[0] + average_cost[1];
        b_l2[0] = b_l2[0] + average_cost[0];
        int run = 0;
        cout << result_sum / 5 << endl;
        result_sum = 0;
    }
    cout << w_in[0] << " " << b_in[0] << " " << w_l1[0] << " " << b_l1[0] << " "
         << w_l2[0] << " " << b_l2[0] << endl;
}