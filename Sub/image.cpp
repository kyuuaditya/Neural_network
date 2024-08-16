#include <bits/stdc++.h>
#include <stdio.h>

#include "CImg.h"
using namespace std;
using namespace cimg_library;

int main() {
    srand(time(0));
    int height = 800;
    int width = 800;
    int radius = 200;
    CImg<unsigned char> img(width, height, 1, 3);
    // CImgDisplay show(img, "image");
    img.fill(0);
    int centrey = height / 2;
    int centrex = width / 2;
    int p;
    int q;
    int img2[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            img2[i][j] = 0;
        }
    }
    CImg<unsigned char> final(10, 10, 1, 3);
    // CImgDisplay show2(final, "why");

    for (int yo = 0; yo < 1; yo++) {
        // while (1) {
        img.fill(0);
        final.fill(0);
        centrey = height / 2 + (rand() % (height / 5) + 1) - height / 10;
        centrex = width / 2 + (rand() % (height / 5) + 1) - height / 10;
        radius = (height / 5) + (rand() % (height / 5) + 1) - height / 10;

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                q = j / 80;
                p = i / 80;
                if ((double)((centrex - i) * (centrex - i) +
                             (centrey - j) * (centrey - j)) < radius * radius) {
                    img(i, j, 0, 0) = 255;
                    img(i, j, 0, 1) = 255;
                    img(i, j, 0, 2) = 255;
                    img2[p][q] += 255;
                }
            }
        }
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                img2[j][i] = img2[j][i] / 6400;
                // cout << img2[j][i] << " ";
                final(j, i, 0, 0) = img2[j][i];
                final(j, i, 0, 1) = img2[j][i];
                final(j, i, 0, 2) = img2[j][i];
            }
            // cout << endl;
        }
        // img.display(show);
        // final.display(show2);
        // show.wait(1000);
        final.save("img.png");
    }
    // while (!show.is_closed() && !show.is_closed()) {
    //     img.display(show);
    //     final.display(show2);
    // }
}
