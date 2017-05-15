#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int search_index(int price, int **d_prices, int index) {
    int left = 0, right = index;
    int mid;
  
    while (left < right) {
        mid = (right + left) / 2;

        if (price <= *d_prices[left] && price > *d_prices[mid]) {
            right = mid;
        } else {
            left = mid;
        }

        if (right - left == 1) {
            left = right;
        }
    }
  
    if (price == *d_prices[left]) {
        left++;
    }
  
  return left;
}

void insert(int *p, int index, int **d_prices, int *d_p_index, int quantity) {
    int i, *temp, *mem = p;

    if (index >= quantity) {
        return;
    }
  
    for (i = index; i <= *d_p_index; i++) {
        temp = d_prices[i];
        d_prices[i] = mem;
        mem = temp;
    }

    if (quantity - *d_p_index > 1) {
        (*d_p_index)++;
        d_prices[*d_p_index] = mem;
    }
}

int main(int argc, char *argv[]) {
	char *input_file, *output_file;
	FILE *fp = NULL;
    int prices[10001], quantity = 0, price, discount;
    int discount_quantity, discount_prices_index = -1;
    int **discount_prices;
    float sum, prices_sum = 0.0, discount_prices_sum = 0.0;
    int i, insert_index;

    if (argc >= 2) {
        input_file = argv[1];
    } else {
        //input_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/discnt/inputData/01.in";
        input_file = "discnt.in";
    }

    if (argc >= 3) {
        output_file = argv[2];
    } else {
        //output_file = "/Users/red_lion/Documents/Projects/GitHub/algorithms-lits/discnt/discnt.out";
        output_file = "discnt.out";
    }

    fp = fopen(input_file, "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    while(fscanf(fp, "%d", &price) == 1) {
        prices[quantity++] = price;
    }
    discount = prices[--quantity];
    fclose(fp);

    discount_quantity = quantity / 3;
    if (discount_quantity > 0) {
        discount_prices = new int*[discount_quantity];
    }

    for (i = 0; i < quantity; i++) {
        prices_sum += prices[i];

        if (discount_quantity > 0) {
            if (discount_prices_index >= 0) {
                if (prices[i] > *discount_prices[0]) {
                    insert_index = 0;
                } else if (prices[i] == *discount_prices[0]) {
                    insert_index = 1;
                } else if (prices[i] <= *discount_prices[discount_prices_index]) {
                        insert_index = discount_prices_index + 1;
                } else {
                        insert_index = search_index(prices[i], discount_prices, discount_prices_index);
                }

                if (insert_index < discount_quantity) {
                    insert(&prices[i], insert_index, discount_prices, &discount_prices_index, discount_quantity);
                }
            } else {
                discount_prices[++discount_prices_index] = &prices[i];
            }
        }
    }

    for (i = 0; i < discount_quantity; i++) {
        discount_prices_sum += *discount_prices[i];
    }

    if (*discount_prices != NULL) {
        delete [] discount_prices;
    }

    sum = prices_sum - discount_prices_sum * discount / 100.0;

    fp = fopen(output_file, "w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    fprintf(fp, "%.2f", sum);
    fclose(fp);

    return 0;
}
