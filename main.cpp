#include <stdio.h>
#include <limits>
#include <cmath>

//const int MAXINT = 100;
struct VNode{
    int V;
    int E;
    VNode *next = NULL;
};

void joinV(VNode **list,int v1,int v2,int e){
    VNode *begin = list[v1]->next;
    VNode *nV = new VNode;
    nV->V = v2;
    nV->E = e;
    nV->next = begin;
    list[v1]->next=nV;
}

VNode** initV(int n){
    VNode **list = new VNode*[n];
    for(int i=0;i<n;i++){
        VNode* nV = new VNode;
        nV->V = i;
        nV->E = 0;
        list[i] = nV;
    }
    return list;
}

void printList(VNode *begin){
    while(begin != NULL){
        printf("[%d:%d]",begin->V,begin->E);
        begin=begin->next;
    }
}

void printGraph(VNode **list,int n){
    for(int i=0;i<n;i++){
        printf("V:%d ",list[i]->V);
        printList(list[i]->next);
        printf("\n");
    }
}

bool find_negative_cycle(VNode** list,int* d,int n){
    for(int j=0;j<n;j++){
        VNode *CV = list[j];
        VNode *CN = CV->next;
        while(CN != NULL){                
            if(d[CN->V] > d[CV->V]+CN->E)
                return true;
            CN = CN->next;
        }
    }
    return false;
}

bool bellman_ford(VNode** list,int* p,int* d,int n){
    for(int i=1;i<n;i++){
        bool test = false;

        for(int j=0;j<n;j++){
            VNode *CV = list[j];
            VNode *CN = CV->next;
            while(CN != NULL){
                if(d[CV->V]!= std::numeric_limits<int>::max() && d[CN->V] > d[CV->V]+CN->E){
                    test = true;
                    d[CN->V] = d[CV->V]+CN->E;
                    p[CN->V] = CV->V;
                }
                CN = CN->next;
            }
        }
        if(!test)
            return true;
    }
    if(find_negative_cycle(list,d,n))
        return false;
    else
        return true;
}

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);

    VNode **list = initV(n);
    for(int i=0;i<m;i++){
        int p,q,s;
        scanf("%d%d%d",&p,&q,&s);
        joinV(list,p,q,s);
    }

    int *d = new int[n];
    int *p = new int[n];
    for(int i=0;i<n;i++){
        d[i] = std::numeric_limits<int>::max();
        p[i] = -1;
    }

    int s,e;
    scanf("%d%d",&s,&e);
    d[s] = 0;
    if(bellman_ford(list,p,d,n)){
     for(int i=0;i<n;i++)
        printf("%d ",d[i]);
    }
    else
        printf("Negative!");


    return 0;
}
