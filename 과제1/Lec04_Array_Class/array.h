/*#pragma once
#include <iostream>

#define HEIGHT 8
#define WIDTH 8

// 2차원 이미지 배열에서 최대 화소 밝기를 찾아 반환하는 함수
int GetMaxBrightness(int img[HEIGHT][WIDTH]) {
    // 1. 최대값을 저장할 변수를 선언하고, 배열의 첫 번째 원소로 초기화합니다.
    int max_val = img[0][0];

    // 2. 이중 for문을 사용하여 2차원 배열의 모든 요소를 순회합니다.
    for (int i = 0; i < HEIGHT; i++) {       // 행(Row) 반복
        for (int j = 0; j < WIDTH; j++) {    // 열(Column) 반복
            
            // 3. 현재 픽셀의 밝기가 지금까지 찾은 최대값(max_val)보다 크면 갱신합니다.
            if (img[i][j] > max_val) {
                max_val = img[i][j];
            }
        }
    }

    // 4. 최종적으로 찾은 최대값을 반환합니다.
    return max_val;
}*/