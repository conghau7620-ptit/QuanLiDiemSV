#include "library.h"

void add_lopcq(char ** data){
    LopCQ new_lopcq(data[0]);
    database.get_dslcq().push_back(new_lopcq);
}
