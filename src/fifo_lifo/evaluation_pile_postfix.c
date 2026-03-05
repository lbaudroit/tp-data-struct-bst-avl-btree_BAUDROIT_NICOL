#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * Prend une chaîne de la forme "1 2 +"
 */
// int eval_postfix(const char *expr) {
//     int i = 0;
//     int result = 0;
//
//     do {
//         char op1 = expr[i];
//         char op2 = expr[i+2];
//         char operande = expr[i+5];
//
//         int op1_asint = op1 - '0';
//         int op2_asint = op2 - '0';
//
//         printf("%d %c %d\n", op1_asint, operande, op2_asint);
//
//         switch (operande) {
//             case '+': result = op1_asint + op2_asint; break;
//             case '-': result = op1_asint - op2_asint; break;
//             case '*': result = op1_asint * op2_asint; break;
//             case '/': result = op1_asint / op2_asint; break;
//             default: return -9999;
//         }
//
//         if (expr[i + 3] > '\0') {
//             return result;
//         } else {
//             expr[i + 2] = ('0' + result);
//             i += 3;
//         }
//
//     } while (expr[i + 3] > '\0');
//
//     return result;
// }
// Implementation comme dit par M. Veyssade :
// concernant const char * c'est que logiquement l'utilisateur donne une chaîne de caractère, il faudrait donc 1. découper en token 2. transformer en entier / opérande et 3. utiliser une fifo/lifo pour l’évaluation.
// la tokenisation est possible via strtok ou via exo3 fait en C/Unix. La transformation en entier est possible via atoi
// En utilisant donc strtok
int eval_postfix(const char *expr) {
    // Il est nécessaire de coier l'expression dans un buffer car strtok modifie la chaine elle même, source : https://koor.fr/C/cstring/strtok.wp
    char buffer[256]; // Fonction de copie : https://koor.fr/C/cstring/strncpy.wp
    strncpy(buffer, expr, sizeof(buffer));

    int stack[100]; // Implementation simple de lifo
    int top = -1;   // Pointeur de la lifo

    // 1. Découpage en token
    char *token = strtok(buffer, " ");

    while (token != NULL) {
        // Si opérateur = effectuer le calcul
        // strlen pour vérifier que on à pas un nombre, donc soit un chiffre ou opérateur
        // strchr pour vérifier si apartient à une chaine : https://koor.fr/C/cstring/strchr.wp (NULL si pas de caractère, lui-même sinon)
        if (strlen(token) == 1 && strchr("+-*/", token[0])) {
            // 3. Utiliser une LIFO pour l'évaluation
            if (top < 1) return -9999; // Vérification qu'on a au moins 2 nombre dans la pile

            int b = stack[top--];
            int a = stack[top--];

            switch (token[0]) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
            }
        } else {
            // 2. Transformer en entier (atoi) https://koor.fr/C/cstdlib/atoi.wp
            stack[++top] = atoi(token);
        }

        token = strtok(NULL, " "); // Passage au prochain token
    }

    return stack[top]; // Le dernier doit être notre résultat
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
