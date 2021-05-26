#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 266
#define INPUT "input.txt"
#define OUTPUT "output.txt"
 
typedef struct nodetype {
	int freq;
	char alpa;

	struct nodetype* left;
    struct nodetype* right;
} *node;
 
struct nodetype p_get[256] = {{0}};

node q_list[255];
node *q = q_list - 1;

int num = 0;
int plus = 1;

char *code[128] = {0};
char buf[1024];
char decoded_str[MAX];

void make_code(node n, char *s, int len)
{
	static char *out = buf;
	if (n->alpa) {
		s[len] = 0;
		strcpy(out, s);
		code[n->alpa] = out;
		out += len + 1;
		return;
	}
 
	s[len] = '0'; 
	make_code(n->left,  s, len + 1);

	s[len] = '1'; 
	make_code(n->right, s, len + 1);
}

node new_node(int freq, char alpa, node n1, node n2)
{
	node n = p_get + num++;

	if (freq) {
		n->alpa = alpa;
		n->freq = freq;
	}
	else {
		n->left = n1;
		n->right = n2;

		n->freq = n1->freq + n2->freq;
	}

	return n;
}
 
void q_insert(node n)
{
	int j, i = plus++;

	while ((j = i / 2)) {
		if (q[j]->freq <= n->freq) 
			break;

		q[i] = q[j], i = j;
	}

	q[i] = n;
}

node q_remove()
{
	int i, l;
	node n = q[i = 1];
 
	if (plus < 2) 
		return 0;

	plus--;

	while ((l = i * 2) < plus) {
		if (l + 1 < plus && q[l + 1]->freq < q[l]->freq) 
			l++;

		q[i] = q[l], i = l;
	}

	q[i] = q[plus];

	return n;
}
 
void make_q(const char *s)
{
	int freq[128] = {0};

	char alpa[16];
 
	while (*s) freq[(int)*s++]++;
 
	for (int i = 0; i < 128; i++) {
		if (freq[i]) q_insert(new_node(freq[i], i, 0, 0));
	}
	
	while (plus > 2) {
		q_insert(new_node(0, 0, q_remove(), q_remove()));
	}
 
	make_code(q[1], alpa, 0);
}
 
void encode(const char *s, char *out)
{
	while (*s) {
		strcpy(out, code[*s]);
		out += strlen(code[*s++]);
	}
}
 
void decode(const char *s, node t)
{
	node n = t;
	int i = 0;

	while (*s) {
		if (*s++ == '0') 
			n = n->left;
		else 
			n = n->right;
 
		if (n->alpa){
			decoded_str[i] = n->alpa, n = t;
			i++;
		}
	}

	printf("%s\n", decoded_str);
}

int main(void)
{
	FILE* fp = fopen(INPUT, "r");

   	char alpa[26];
   	int cnt[26] = { 0 };

   	char input_str[MAX];
	char sort_str[MAX];
	char buf[MAX];
	char buf2[1024];

   	fscanf(fp, "%s", input_str);

   	printf("%s\n", input_str);

	fclose(fp); 

   	for(int i = 0; i < 26; i++){
      	alpa[i] = 'A' + i;
   	}

   	for(int i = 0; i < strlen(input_str); i++){
      	if(input_str[i] >= 'A' && input_str[i] <= 'Z'){
         	if(input_str[i] <= 'Z')
            	cnt[input_str[i] - 'A']++;
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

			sprintf(sort_str, "%c:%d ", alpa[i], cnt[i]);

			FILE *fp1 = fopen("sort.txt", "a+"); 
			
			fprintf(fp1, sort_str);

			fclose(fp1); 
		}
   	}	
 
	make_q(input_str);

	encode(input_str, buf2);
	printf("encoded: %s\n", buf2);

	FILE *fp2 = fopen("encoding.txt", "a+"); 
			
	fprintf(fp2, buf2);

	fclose(fp2); 

	printf("decoded: ");
	decode(buf2, q[1]);; 

	FILE *fp3 = fopen("decoding.txt", "a+"); 
			
	fprintf(fp3, decoded_str);

	fclose(fp3);

	return 0;
}