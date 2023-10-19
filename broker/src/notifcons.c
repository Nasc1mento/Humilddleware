//
// Created by afreis on 10/18/23.
//

#include <malloc.h>
#include "stdio.h"
#include "mom.h"
#include "notifengine.h"
#include "submanager.h"

void notify(invocation *inv, int fd) {

   if (inv->op == "SUBSCRIBE")
   {
         inssub(inv->topic, fd);
   }
    else if (inv->op == "PUBLISH")
    {

    }
    else if (inv->op == "UNSUBSCRIBE")
    {

    }
    else
    {
         printf("Invalid operation");
    }


}
