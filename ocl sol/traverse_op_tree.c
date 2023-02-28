
void new_node(int r, int i, int j, 
              int *queue, int *parent, bool *reachable,
              int *queue_end_idx)
{

    // On creating new, take a note of what has been reached
    if (r>=100 && r<1000)
    {
        reachable[r-100] = true;
    }

    // printf("  %d %d %d %f\n", *queue_end_idx, parent[i], parent[j], r);

    // copy old vals to new node
    for(int k=0; k<6; k++)
    {
        queue[(*queue_end_idx)*6 +k] = parent[k];
    }

    queue[(*queue_end_idx)*6 +i] = r;
    queue[(*queue_end_idx)*6 +j] = 0; 

    // printf("  %d %d %d %d %d %d\n\n", queue[(*queue_end_idx)*6 +0],
    //                                   queue[(*queue_end_idx)*6 +1],
    //                                   queue[(*queue_end_idx)*6 +2],
    //                                   queue[(*queue_end_idx)*6 +3],
    //                                   queue[(*queue_end_idx)*6 +4],
    //                                   queue[(*queue_end_idx)*6 +5]);

    (*queue_end_idx)++;
    // printf("  %d %d %d %d %d %d\n\n", parent[0], parent[1], parent[2], parent[3], parent[4], parent[5]);
}

bool traverse(bool *reachable, // reachability for targets 100-999
              int *queue,      // Every 6 ints is a node in the graph, each node being an intermediate number set (after applying some ops)
              int *gameset)    // The gameset for which we are trying to enumerate all valid combinations of operations
// Traverses the tree of op choices for a single game set.
{

    //// Init given arrs
    for(int i=0; i<6; i++)
    {
        queue[i]=gameset[i];
    }

    for(int i=6; i<MAX_QUEUE_SIZE*6; i++)
    {
        queue[i]=0;
    }

    for (int i=0; i<900; i++)
    {
        reachable[i] = false;
    }
    //

    int parent[6];
    int queue_end_idx = 0;
    int n1, n2, node_sum;

    while (queue_end_idx>=0)
    {
        //// This will point to a generated node, but could be an end node
        node_sum=0;
        for(int i=0; i<6; i++)
        {
            if (queue[queue_end_idx*6 +i]>0) { node_sum++; }
        }
        if (node_sum<=1) // not an expandable node, move back
        {
            queue_end_idx--;
            continue;
        }
        //

        // current node to expand
        for(int i=0; i<6; i++)
        {
            parent[i] = queue[queue_end_idx*6 +i];
        }

        for(int i=0; i<6; i++)
        {
            for(int j=i+1; j<6; j++)
            {
                n1 = parent[i];
                n2 = parent[j];
                
                if (n1>0 && n2>0) // Empty slots set to 0
                {
                    // printf("\n%d %d %d %d %d\n", i, j, queue_end_idx, n1, n2);

                    // New by addition, written over expanded node
                    new_node(n1+n2, i, j, queue, parent, reachable, &queue_end_idx);
                    if (queue_end_idx>=MAX_QUEUE_SIZE) { return false; }

                    // New by multiplication
                    new_node(n1*n2, i, j, queue, parent, reachable, &queue_end_idx);
                    if (queue_end_idx>=MAX_QUEUE_SIZE) { return false; }

                    // New by substraction
                    if (n1>n2)
                    {
                        new_node(n1-n2, i, j, queue, parent, reachable, &queue_end_idx);
                        if (queue_end_idx>=MAX_QUEUE_SIZE) { return false; }
                    } else {
                        new_node(n2-n1, j, i, queue, parent, reachable, &queue_end_idx);
                        if (queue_end_idx>=MAX_QUEUE_SIZE) { return false; }
                    }

                    // New by division
                    if (n1%n2==0)
                    {
                        new_node(n1/n2, i, j, queue, parent, reachable, &queue_end_idx);
                        if (queue_end_idx>=MAX_QUEUE_SIZE) { return false; }
                    } else if (n1%n2==0) {
                        new_node(n2/n1, j, i, queue, parent, reachable, &queue_end_idx);
                        if (queue_end_idx>=MAX_QUEUE_SIZE) { return false; }
                    }

                    queue_end_idx--; // point back to last valid node 
                                     // (new_node increments to empty slot for writing, but we will want to read next)

                }
            }
        }

    }

    return true;
}
