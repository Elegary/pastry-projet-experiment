#include <stdio.h>
#include <stdlib.h>

#include "pastry.h"

int main(){
    printf("Hello, worlddddd! \n");

    Element_str* l_tastes;
    Order_Queue* q_orders;
    Tasting_Queue* q_tasting;

    l_tastes = initialize_tastes();
    q_orders = create_order_queue();
    q_tasting = create_tasting_queue();

    pass_order("VCSO", q_orders);
    pass_order("CSAB", q_orders);
    pass_order("FCSF", q_orders);
    pass_order("CVSO", q_orders);
    pass_order("FCSF", q_orders);
    pass_order("FCSF", q_orders);
    pass_order("FCSF", q_orders);
    pass_order("FCSF", q_orders);
    pass_order("VCSFCSFO", q_orders);
    pass_order("FCSFFCSF", q_orders);
    pass_order("FCSF", q_orders);

    Element_str* order = process_order(q_orders);
    Cake* cake = create_cake(order);
    build_Cake(cake, l_tastes);
    printf("First taste of your cake : %s\n", cake->s_tastes->data->text);

    deliver(cake, q_tasting);
    tasting(q_tasting, 5);

    printf("\n");

    order = process_order(q_orders);
    cake = create_cake(order);
    build_Cake(cake, l_tastes);
    printf("First taste of your cake : %s\n", cake->s_tastes->data->text);
    deliver(cake, q_tasting);
    tasting(q_tasting, 5);

    free(q_orders);
    free(q_tasting);

    return 0;
}