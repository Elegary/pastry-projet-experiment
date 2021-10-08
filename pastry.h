
#ifndef PASTRY_PROJECT_PASTRY_H
#define PASTRY_PROJECT_PASTRY_H

typedef struct Element_str{
    char text[50];
    struct Element_str* next;
} Element_str;

typedef struct Cake{
    struct Element_str* order;
    struct Taste_Stack* s_tastes;
} Cake;

typedef struct Order_Queue{
    struct Element_str* data;

} Order_Queue;

typedef struct Taste_Stack{
    struct Element_str* data;
} Taste_Stack;

typedef struct Element_cake{
    struct Cake* cake;
    struct Element_cake* next;
} Element_cake;

typedef struct Tasting_Queue{
    struct Element_cake* data;
} Tasting_Queue;


// Functions

Element_str* initialize_tastes();
void pass_order(char order[50], Order_Queue* f_orders );
Element_str* process_order(Order_Queue* q_orders );
Order_Queue* create_order_queue();
int order_queue_is_full(Order_Queue* q_orders);
Cake* create_cake(Element_str* order);
void build_Cake(Cake* cake, Element_str* l_tastes);
void deliver(Cake* cake, Tasting_Queue* q_tasting);
Tasting_Queue* create_tasting_queue();
void tasting(Tasting_Queue* q_tasting, int nb_parts);

#endif //PASTRY_PROJECT_PASTRY_H
