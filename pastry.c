
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pastry.h"

// A static array of char to store the tastes
char tastes_values[7][50] = { "Chocolate", "Vanilla", "Strawberry", "Orange", "Apple", "Banana", "Fudge" };

Element_str* initialize_tastes(){

    Element_str* l_tastes = malloc(sizeof(*l_tastes));

    // We use the static array to create the Linked List that contains the tastes

    for (int i = 0; i < 7; ++i) {
        Element_str* new = malloc(sizeof(*new));
        strcpy(new->text, tastes_values[i]);

        new->next = l_tastes;
        l_tastes = new;
    }

    return l_tastes;

}

Order_Queue* create_order_queue(){
    // We create and allocate the memory the order queue
    Order_Queue* q_orders = malloc(sizeof (*q_orders));
    q_orders->data = NULL;
    return q_orders;
}

int order_queue_is_full(Order_Queue* q_orders){

    // If Queue is empty, return 0
    if(q_orders->data == NULL) {
        return 0;
    }

    // We count the number of orders using while
    Element_str* temp = q_orders->data;
    int order_count = 1;
    while (temp->next != NULL){
        order_count++;
        temp = temp->next;
    }

    // Return 1 if the total number of orders is superior or equal to 10, else 0
    return order_count >= 10;

}

void pass_order(char order[50], Order_Queue* f_orders ){

    if(order_queue_is_full(f_orders) == 1){
        // Stop the new order
        printf("Order queue is full !\n");
        return;
    }

    Element_str* new_order = malloc(sizeof(*new_order));
    new_order->next = NULL;
    strcpy(new_order->text, order);

    // If the order queue is empty, simply put the new order at the top of the queue
    if(f_orders->data == NULL){
        f_orders->data = new_order;
    }

        // Else, simply add the new order at the end of the list : First In, First Out
    else {
        Element_str* temp = f_orders->data;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_order;
    }

}

Element_str* process_order(Order_Queue* q_orders ){
    // Check if the order queue is empty
    if(q_orders->data == NULL){
        // If order queue is empty, we return NULL
        printf("There is currently no order in the queue !\n");
        return NULL;
    }

    else {
        // Save current address
        Element_str* current_order = q_orders->data;
        // Remove the order from the queue
        q_orders->data = q_orders->data->next;
        // Return current address
        return current_order;
    }

}

Cake* create_cake(Element_str* order){
    Cake* new_cake = malloc(sizeof (*new_cake));
    new_cake->order = order;
    Taste_Stack* s_tastes = malloc(sizeof (*s_tastes));
    s_tastes->data = NULL;
    new_cake->s_tastes = s_tastes;
    return new_cake;
}

void build_Cake(Cake* cake, Element_str* l_tastes){
    printf("Building a cake with order : %s\n", cake->order->text);
    int i = 0;
    // For every character, which correspond to a taste, we find the corresponding full word
    while (cake->order->text[i] != '\0'){

        // We save the first taste address
        Element_str* first_taste = l_tastes;
        // We find the corresponding taste
        while (l_tastes->text[0] != cake->order->text[i]){
            l_tastes = l_tastes->next;
        }
        printf("Adding %c correspond to taste %s\n", cake->order->text[i], l_tastes->text);
        Element_str* current_taste = malloc(sizeof (*current_taste));
        // After finding the corresponding taste of the letter, we copy it into the Taste Element
        strcpy(current_taste->text, l_tastes->text);

        current_taste->next = cake->s_tastes->data;
        cake->s_tastes->data = current_taste;

        // We go back to the head of the tastes list
        l_tastes = first_taste;
        i++;
    }
}

Tasting_Queue* create_tasting_queue(){
    // Simply alloc for the queue
    Tasting_Queue* q_tasting = malloc(sizeof (*q_tasting));
    q_tasting->data = NULL;
    return q_tasting;
}

void deliver(Cake* cake, Tasting_Queue* q_tasting){

    // Putting the cake in a Cake element
    // Think about what happens to the order for this cake : order is destroyed in tasting function
    Element_cake* ready_cake = malloc(sizeof (*ready_cake));
    ready_cake->next = NULL;
    ready_cake->cake = cake;

    // If the tasting queue is empty, simply put the new Cake element at the top of the queue
    if(q_tasting->data == NULL){
        q_tasting->data = ready_cake;
    }

    else {
        // Else add the new Cake element at the end of the queue
        Element_cake* temp = q_tasting->data;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = ready_cake;
    }

}

void tasting(Tasting_Queue* q_tasting, int nb_parts){
    if(q_tasting->data == NULL){
        // Stop the tasting if tasting queue is null
        return;
    }

    else {

        Element_cake* current_cake = q_tasting->data;

        if (current_cake->cake->s_tastes->data == NULL){
            // Stop the tasting if tastes stack is null
            return;
        }

        else {
            int current_part = 0;
            Element_str* current_taste =  current_cake->cake->s_tastes->data;
            while (current_part < nb_parts && current_taste != NULL) {
                // Remove from the taste stack
                printf("Currently eating %s from %s cake\n", current_taste->text, current_cake->cake->order->text);
                Element_str* old_taste = current_taste;
                current_taste = current_taste->next;
                free(old_taste);
                current_part++;
            }

            if(current_taste == NULL){
                // If cake has been entirely ate, remove it from the tasting queue
                printf("Cake %s has been entirely ate, removing it\n", current_cake->cake->order->text);
                Element_cake* old = q_tasting->data;
                q_tasting->data = q_tasting->data->next;
                // Free the different allocations
                free(old->cake->s_tastes);
                free(old->cake->order);
                free(old->cake);
                free(old);
            }

        }

    }

}