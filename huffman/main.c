#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 266
#define INPUT "input.txt"
#define OUTPUT "output.txt"

typedef struct nodetype
{
    char alpa;   
    int cnt; 

    struct nodetype* left;
    struct nodetype* right;
}node;

typedef struct pq   // 우선순위 대기열
{
    node* Node;         // 대기열에 있는 node
    struct pq* next;   // 다음 node
}pq;

#define ROOT    -1 // 부호화 함수 출력시 초기값

pq* insert(node* r);        // 우선순위 대기열에 노드를 정렬하여 삽입
node* huffman(int n);       // 허프만 코드 트리를 만드는 함수
node* Remove();             // 우선 순위 대기열에서 노드를 삭제
void print_PQ();            // 우선 순위 대기열 출력
void print_tree(node* r, int n, char* code);    // 결과 허프만 부호화 출력
void freetree(node* r);     // 메모리 해제;

int num = 0;

char dc_c[26][MAX];
char dc_a[26];

char a[MAX];

pq* PQ = NULL;      // 우선순위 대기열

int main()
{
	FILE* fp = fopen(INPUT, "r");

   	char alpa[26];
   	int cnt[26] = { 0 };
   	char str[MAX];
	char buf[MAX];
	char s[20];

   	fscanf(fp, "%s", str);

   	printf("%s\n", str);

	fclose(fp); 

   	for(int i = 0; i < 26; i++){
      	alpa[i] = 'A' + i;
   	}

   	for(int i = 0; i < strlen(str); i++){
      	if(str[i] >= 'A' && str[i] <= 'Z'){
         	if(str[i] <= 'Z')
            	cnt[str[i] - 'A']++;
      	}
   	}

   	for(int i = 0; i < 26; i++){
     	for(int j = i; j < 26; j++){
         	if(cnt[i] < cnt[j]){
            	int tmp = 0;
            	char swp = ' ';

            	tmp = cnt[i];
            	cnt[i] = cnt[j];
            	cnt[j] = tmp;

            	swp = alpa[i];
            	alpa[i] = alpa[j];
            	alpa[j] = swp;
         	}
     	}
   	}

   	for(int i = 0; i < 26; i++){
      	if(cnt[i] != 0){
         	printf("%c : %d\n", alpa[i], cnt[i]);

			sprintf(s, "%c:%d ", alpa[i], cnt[i]);

			FILE *fp1 = fopen("sort.txt", "a+"); 
			
			fprintf(fp1, s);

			fclose(fp1); 
		}
   	}	


    int n = 1;
    node* result = (node*) malloc(sizeof(node));   
    char* code = (char*) malloc(sizeof(char));

    FILE* file = fopen("sort.txt", "r");  

    if(file == NULL) {
        perror("File open error");
        return 0;
    }

    while(1) {
        node* r = (node*) malloc(sizeof(node));
        if( ( fscanf(file, "%c:%d ", &r->alpa, &r->cnt)) == -1) {
            break;       
        }

        r->left = NULL;
        r->right = NULL;

        insert(r);      

        n++;
    }

    printf("----- Huffman Algorithm -----\n\n");
    print_PQ();     

    result = huffman(n);    

    printf("\n-- Result Huffman code tree --\n");
    print_tree(result, ROOT, code);
    printf("\n");

    printf("\n-- Huffman code encoding --\n");
    for(int i = 0; i < strlen(dc_a); i++){
        printf("%s : %s\n", dc_a[i], dc_c[i]);
    }
    freetree(result);  
    fclose(file);

    return 0;
}

void freetree(node* r)  
{
    if(r) {
        freetree(r->left);
        freetree(r->right);
        free(r);
    }
}

pq* insert(node* r)
{
    pq* tmp = NULL;
    pq* new = NULL;

    new = (pq*) malloc(sizeof(pq));
    new->Node = r;      
    new->next = NULL;

    if(PQ == NULL){    
        PQ = new;
        return PQ;
    } else if(PQ->Node->cnt >= new->Node->cnt) {
        new->next = PQ;            
        PQ = new;
    }else {                           
        tmp = PQ;                      
        while(tmp->next != NULL) {       
            if(tmp->next->Node->cnt < new->Node->cnt)
                tmp = tmp->next;       
            else {                      
                new->next = tmp->next;  
                tmp->next = new;       
                break;
            }
        }
        if(tmp->next == NULL)   
            tmp->next = new;

        return tmp;
    }
    return 0;
}

node* huffman(int n)   
{
    node* p;
    node* q;
    node* r;

    int i;

    for(i = 1; i < n - 1; i++) {
        p = Remove();  
        q = Remove();   

        r = (node*) malloc(sizeof(node)); 

        r->left = p;
        r->right = q;
        r->cnt = p->cnt + q->cnt;
        r->alpa = '*';  

        insert(r);        

        printf("-- Create sub tree (%d/%d)\n  ", i, n-2);
        printf("%c:%d = %c:%d + %c:%d\n",
                r->alpa, r->cnt, p->alpa, p->cnt, q->alpa, q->cnt);
        print_PQ();
    }

    r = Remove();  
    return r;
}

node* Remove() 
{
    node* pq_firstnode = NULL;

    pq_firstnode = PQ->Node;
    PQ = PQ->next;

    return pq_firstnode;
}

void print_PQ()    
{
    pq* tmp = PQ;
    printf("-- Priority Queue\n  | ");
    while(tmp != NULL){
        printf("%c:%d | ", tmp->Node->alpa, tmp->Node->cnt);
        tmp = tmp->next;
    }
    printf("\n\n");
}

void print_tree(node* r, int n, char* code) {
    if(r) {
        n++;  

        code[n] = '1';    
        print_tree(r->left, n, code);

        code[n] = '0';   
        print_tree(r->right, n, code);
        
        code[n] = '\0';   

        if(r->left == NULL && r->right == NULL) {  // 자식이 있는 노드는 출력하지 않음
            printf(" - %c:%d\t= %s\n", r->alpa, r->cnt, code);

            char tmp[26];
            char *t = malloc(sizeof(char) * 26);

            strcpy(tmp, &r->alpa);
            strcpy(&dc_a[num], tmp);

            strncpy(t, code);
            strncpy(dc_c[num], t);

            num++;
        }
    }
}


//단축키 수정
//ctrl alt c == 컴파일
//ctrl alt r == 실행