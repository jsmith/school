//
// Jacob Smith 3534295
// Raven-Lee Mills 3564447
//

#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, edges_length;
    scanf("%d %d", &n, &edges_length);

    int offsets[n + 1];
    for(int i = 0; i < n + 1; i++) {
        scanf("%d", &(offsets[i]));
    }

    int edges[edges_length];
    for(int i = 0; i < edges_length; i++) {
        scanf("%d", &(edges[i]));
    }

    // Scan in variable path
    int path_length = 0;
    int path[20];
    while(scanf("%d", &path[path_length]) == 1) {
        path_length++;
    }

    // Int array used to keep track off the amount of times each vertex is visited
    int counts[n];
    for(int i = 0; i < n; i++) {
        counts[i] = 0;
    }


    bool isPath = true;
    for (int j = 0; j < path_length; j++){
        int vertex = path[j];
        counts[vertex]++;

        //If the vertex in path is accessed end loop, because j+1 does not exist
        if(j + 1 == path_length){
            break;
        }
        int next_vertex = path[j+1];

        bool isInPath = false;
        for (int i = offsets[vertex]; i < offsets[vertex+1]; i++) {

            //Checks if the next vertex is accessible from current vertex
            if (next_vertex == edges[i]){
                isInPath = true;
                break;
            }
        }

        //If the next vertex is not accessible or the vertex is not distinct, the path is not valid
        if(!isInPath || counts[vertex] > 1) {
            isPath = false;
            break;
        }
    }

    bool isHamilton = true;
    for(int i = 0; i < n; i++) {
        // If the amount of times each vertex is visited is not exactly 1 then the path is not Hamiltonian
        if(counts[i] != 1) {
            isHamilton = false;
            break;
        }
    }

    if(isPath){
        printf("is a path\n");
    } else {
        printf("is NOT a path\n");
    }

    if(isHamilton){
        printf("is a Hamiltonian path\n");
    } else {
        printf("is NOT a Hamiltonian path\n");
    }
}