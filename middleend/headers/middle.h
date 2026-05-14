#ifndef MIDDLE_H
#define MIDDLE_H

#include "../../general/generalheaders/treefuncs.h"

Node_t *OptimizeTree    (Node_t *node, int dump_flag);
Node_t *CalcNode        (Node_t *node, int *change_par);
Node_t *CalcConstNode   (Node_t *node, int *change_par, int dump_flag);
Node_t *RemoveFictElems (Node_t *node, int *change_par, int dump_flag);
Node_t *RemoveFictNode  (Node_t *node, int *change_par);
Node_t *RemoveFict      (Node_t *node, int *change_par);

#endif