#include <stdio.h>

/*
 * Prend une chaîne de la forme "1 2 +"
 */
int eval_postfix(const char *expr) {
    int i = 0;
    int result = 0;

    do {
        char op1 = expr[i];
        char op2 = expr[i+2];
        char operande = expr[i+5];

        int op1_asint = op1 - '0';
        int op2_asint = op2 - '0';

        printf("%d %c %d\n", op1_asint, operande, op2_asint);

        switch (operande) {
            case '+': result = op1_asint + op2_asint; break;
            case '-': result = op1_asint - op2_asint; break;
            case '*': result = op1_asint * op2_asint; break;
            case '/': result = op1_asint / op2_asint; break;
            default: return -9999;
        }

        if (expr[i + 3] > '\0') {
            return result;
        } else {
            expr[i + 2] = ('0' + result);
            i += 3;
        }

    } while (expr[i + 3] > '\0');

    return result;
}

bool fails_test(char* pile, int expected_result) {
    int result = eval_postfix(pile);

    if (result == expected_result) {
        return true;
    }
    printf("Error (expected %d, got %d)\n", expected_result, result);
    return false;
}

int main() {

    char* petite_pile = "3 4 +";
    int expected_petite_pile = 7;
    if (fails_test(petite_pile, expected_petite_pile)) {
        return -1;
    }

    char* grosse_pile = "3 4 + 2 *";
    int expected_grosse_pile = 17;
    if (fails_test(grosse_pile, expected_grosse_pile)) {
        return -1;
    }
}