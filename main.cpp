#include "event.h"
#include <iostream>

int main(){
    OrderEvent x("GOOG", "MKT", 100, "BUY");
    x.print_order();
    return 0;
}