#include <stdio.h>
#include <stdlib.h>
//#include "gameBalance.h"
//#include "math.h"
#include "classes_header/array.h"


int main() {
    int *arr = malloc(10 * sizeof(int));
    struct Results x = Results.new(arr, 10);
    for (int i = 0; i < x.length; ++i) {
        printf("%d ", ((int*) x.array)[i]);
    }
//    struct Player p1[5] = {
//            Player.new(3600, 3600, 3200, "Ksenobite"),
//            Player.new(2700, 3200, 2350, "Demogram"),
//            Player.new(2600, 0, 3200, "ElyShar"),
//            Player.new(2500, 3000, 3600, "Honoka"),
//            Player.new(2900, 3100, 3400, "Qyry")};
//    for (int i = 0; i < 5; i++) {
//        p1[i].activateTags(&p1[i], "THD", 3);
//    }
//    struct Player p2[5] = {
//            Player.new(2200, 2300, 0, "Silver"),
//            Player.new(3000, 2900, 2500, "Konder"),
//            Player.new(3300, 2700, 2800, "Svevoloch"),
//            Player.new(3300, 3000, 3400, "AuntPetunia"),
//            Player.new(3850, 3100, 3500, "Freezzle")};
//    for (int i = 0; i < 5; i++)
//        p1[i].changeFlex(&p1[i]);
//    for (int i = 0; i < 5; i++)
//        p2[i].changeFlex(&p2[i]);
//    int fMask[5] = {2, 2, 0, 1, 1};
//    int sMask[5] = {0, 1, 1, 2, 2};
//    int teamMask[10] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
//    struct Balance B = Balance.new(p1, p2, fMask, sMask, teamMask, 5);
//    B.imbalanceFunc(&B);
//    printf("%Lf\n", B.result);

//    size_t teamSize = 5;
//    size_t maskSize = 0;
//    unsigned int ** ansArray = createTeamMasks(&teamSize, &maskSize);
//    printf("%d\n", maskSize);
//    for (int i = 0; i < maskSize; ++i) {
//        for (int j = 0; j < teamSize * 2; ++j) {
//            printf("%d ", ansArray[i][j]);
//        }
//        printf("\n");
//    }
    return 0;
}
