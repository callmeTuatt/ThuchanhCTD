#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>
#define CONSTANT 100


//Linklist
typedef int elementtype; //Must fix

struct list_el{
  elementtype element;
  struct list_el *next;
  struct list_el *prev;
};
typedef struct list_el dblist;

void makeNullList(dblist **root,dblist **cur,dblist **tail){
  *root=NULL;
  *cur=NULL;
  *tail=NULL;
}

dblist* makeNewNode(elementtype data){
  dblist *New = (dblist*)malloc(sizeof(dblist));
  New->element=data;
  New->next = NULL;
  New->prev = NULL;
  return New;
}

void displayNode(dblist* p){ //Must fix
  if(p==NULL){
    printf("ERROR pointer NULL\n");
    return;
  }
  printf(", %d",p->element);
}

void traversinglist(dblist *root){
	dblist *cur;
  for(cur=root;cur!=NULL;cur=cur->next){
    displayNode(cur);
  }
}

void insertAtHead(elementtype data,dblist **root,dblist **cur,dblist **tail){
	dblist* New=makeNewNode(data);
  if(*root==NULL){
   	*root=New;
 		*tail=New;
 		*cur=*root;
  }
  else{
  	New->next=*root;
  	(*root)->prev=New;
  	*root=*cur=New;
	}
}

void AppendList(elementtype data,dblist **root,dblist **cur,dblist **tail){
	dblist* New=makeNewNode(data);
  if((*root)==NULL){
   	(*root)=New;
 		(*tail)=New;
 		(*cur)=(*root);
 		New->next = New->prev = NULL;
  }
  else{
  	New->prev=(*tail);
  	(*tail)->next=New;
  	(*tail)=(*cur)=New;
  	New->next = NULL;
	}
}

void insertAfterCur(elementtype data,dblist **root,dblist **cur,dblist **tail){
	dblist* New=makeNewNode(data);
	if(*root==NULL){
		*root=New;
 		*tail=New;
 		*cur=*root;
	}
	else if(*cur==NULL){
		printf("ERROR! There is no current.");
		return;
	}
	else{
		if(*cur==*tail){
			(*cur)->next=New;
			New->prev=*cur;
			*tail=*cur=New;
		}
		else{
			New->next=(*cur)->next;
			New->prev=*cur;
			(*cur)->next->prev=New;
			(*cur)->next=New;
			*cur=New;
		}
	}
}

void insertBeforeCur(elementtype data,dblist **root,dblist **cur,dblist **tail){
	dblist* New=makeNewNode(data);
	if(*root==NULL){
		*root=New;
 		*tail=New;
 		*cur=*root;
	}
	else if(*cur==NULL){
		printf("ERROR! There is no current.");
		return;
	}
	else{
		if(*cur==*root){
			(*cur)->prev=New;
			New->next=*cur;
			*root=*cur=New;
		}
		else{
			New->next=*cur;
			New->prev=(*cur)->prev;
			(*cur)->prev->next=New;
			(*cur)->prev=New;
			*cur=New;
		}
	}
}


void insertAtPos(elementtype data,dblist **root,dblist **cur,dblist **tail,int p){//Dem tu 0
	int i;
	if(p==0){
		insertAtHead(data,root,cur,tail);
		return;
	}
	if(*root==NULL){
		printf("There is no list");
		return;
	}
	for(i=0,*cur=*root;i<p;i++){
		if(*cur==*tail){
			if(i==p-1){
				AppendList(data,root,cur,tail);
				return;
			}
			else{
				printf("Not enough element\n");
				return;
			}
		}
		*cur=(*cur)->next;
	}
	insertBeforeCur(data,root,cur,tail);
}

void deleteFirstElement(dblist **root,dblist **cur,dblist **tail){
	if(*root!=NULL){
		if(*root==*tail){
			free(*root);
			makeNullList(root,cur,tail);
		}
		else{
			dblist *to_free;
			to_free=*root;
			*root=(*root)->next;
			(*root)->prev=NULL;
			free(to_free);
			*cur=*root;
		}
	}
}

void deleteLastElement(dblist **root,dblist **cur,dblist **tail){
	if(*tail!=NULL){
		if(*root==*tail){
			free(*root);
			makeNullList(root,cur,tail);
		}
		else{
			dblist *to_free;
			to_free=*tail;
			*tail=(*tail)->prev;
			(*tail)->next=NULL;
			free(to_free);
			*cur=*tail;
		}
	}
}

void deleteCurElement(dblist **root,dblist **cur,dblist **tail){
	if(*cur!=NULL){
		if(*cur==*root){
			deleteFirstElement(root,cur,tail);
		}
		else if(*cur==*tail){
			deleteLastElement(root,cur,tail);
		}
		else{
			dblist* to_free;
			(*cur)->next->prev=(*cur)->prev;
			(*cur)->prev->next=(*cur)->next;
			to_free=*cur;
			*cur=(*cur)->next;
			free(to_free);
		}
	}
}

void deleteAtPos(dblist **root,dblist **cur,dblist **tail,int p){//Bat dau dem tu 0
	if(*root!=NULL){
		int i;
		for(i=0,*cur=*root;i<p;i++){
			if((*cur)->next==NULL){
				printf("Not enough element\n");
				return;
			}
			*cur=(*cur)->next;
		}
		deleteCurElement(root,cur,tail);
	}
}

void list_reverse(dblist **root,dblist **cur,dblist **tail){
	dblist *tmp;
	*cur=*root;
	while(*cur!=NULL){
		tmp=(*cur)->next;
		(*cur)->next=(*cur)->prev;
		(*cur)->prev=tmp;
		*cur=tmp;
	}
	tmp=*root;
	*cur=*root=*tail;
	*tail=tmp;
}

void freeNode(dblist **root){
	dblist *to_free;
	for(to_free=*root;to_free!=NULL;to_free=*root){
    *root=to_free->next;
    free(to_free);
  }
}





//BST

typedef struct elm{
	char word[50];
	int appearCount;
	dblist *rootLine, *curLine, *tailLine;
}elmType;

typedef struct node_type{
  elmType element;
  struct node_type *left,*right;
}nodeType;

typedef nodeType *treetype;//treetype a <=> nodeType* a

void makeNullTree(treetype* N){
  (*N)=NULL;
}

nodeType* Create_Node(elmType data){
  nodeType* New = (nodeType*)malloc(sizeof(nodeType));
  if(New!=NULL){
	  New->element=data;
	  New->left=NULL;
	  New->right=NULL;
  }
  return New;
}

int isEmptyTree(treetype N){
	return N==NULL;
}

treetype leftChild(treetype N){
	if(N!=NULL)return N->left;
	else return NULL;
}

treetype rightChild(treetype N){
	if(N!=NULL)return N->right;
	else return NULL;
}

int Compare(elmType a, elmType b){
	if(strcmp(a.word,b.word	)>0)return 1;
	else if(strcmp(a.word,b.word)<0) return -1;
	else return 0;
}

void insertNode(treetype* T,elmType data){
	if(*T==NULL)(*T)=Create_Node(data);
	else{
		if(Compare(data,(*T)->element)==1)insertNode(&(*T)->right,data);
		else insertNode(&(*T)->left,data);
	}
}

int isLeaf(treetype N){
	if(isEmptyTree(N)){
		return 0;
	}
	else return(N->left==NULL&&N->right==NULL);
}

int countNode(treetype N){
	if(isEmptyTree(N))return 0;
	else return 1+countNode(N->left)+countNode(N->right);
}

void InOrderPrint(treetype T){
	if(T!=NULL){
		InOrderPrint(T->left);
		printf("%s %d", T->element.word, T->element.appearCount);
		traversinglist(T->element.rootLine);
		printf("\n");
		InOrderPrint(T->right);
		
	}
}

int Max(int a, int b){
	if(a>b)return a;
	else return b;
}

int treeHeight(treetype T){
	if(T==NULL){
		return 0;
	}
	else{
		if(isLeaf(T))return 0;
		else return 1+ Max(treeHeight(T->left),treeHeight(T->right));
	}
}

int leafNode(treetype T){
	if(T==NULL){
		return 0;
	}
	else{
		if(isLeaf(T))return 1;
		else return leafNode(T->left)+leafNode(T->right);
	}
}

int innerNode(treetype T){
	if(T==NULL){
		return 0;
	}
	else{
		if(isLeaf(T))return 0;
		else return 1+innerNode(T->left)+innerNode(T->right);
	}
}

int numRight(treetype T){
	if(T==NULL){
		return 0;
	}
	else{
		if(T->right==NULL)return 0+numRight(T->left);
		else return 1+numRight(T->left)+numRight(T->right);
	}
}

treetype searchT(treetype T, elmType x){//Search
	if(T==NULL) return T;
	if(Compare(x,T->element)==0) return T;
	else if(isLeaf(T))return NULL;
	else if(Compare(x,T->element)==1)return searchT(T->right,x);
	else return searchT(T->left,x);
}

elmType deletemin(treetype *n){
  elmType k;
  if((*n)->left == NULL){
    k = (*n)->element;
    (*n) = (*n)->right;
    return k;
  }
  else 
    return deletemin(&(*n)->left);
}

void delete(treetype *n, elmType key){
  if(*n!=NULL){
    if(Compare(key,(*n)->element)==-1)
      delete(&(*n)->left,key);
    else if(Compare(key,(*n)->element)==1)
      delete(&(*n)->right,key);
    else if((*n)->left == NULL && (*n)->right == NULL)
      *n = NULL;
    else if((*n)->left == NULL)
      *n = (*n)->right;
    else if((*n)->right == NULL)
      *n = (*n)->left;
    else
      (*n)->element = deletemin(&(*n)->right);
  }
}

void freeTree(treetype T){
	if(T==NULL) return;
	freeTree(T->left);
	freeTree(T->right);
	freeNode(&(T->element.rootLine));
	free((void*)T);
}



//Code


treetype searchTbyword(treetype T, char* word){//Search
	elmType wordData;
	strcpy(wordData.word, word);
	return searchT(T, wordData);
}

void AddWord(treetype* wordTree ,char *word, int line){
	treetype curword = searchTbyword(*wordTree, word);
	if(curword==NULL){//new
		elmType wordData;
		strcpy(wordData.word, word);
		wordData.appearCount=1;
		makeNullList(&(wordData.rootLine), &(wordData.curLine), &(wordData.tailLine));
		AppendList(line, &(wordData.rootLine), &(wordData.curLine), &(wordData.tailLine));
		insertNode(wordTree, wordData);
	}
	else{
		curword->element.appearCount++;
		AppendList(line, &(curword->element.rootLine), &(curword->element.curLine), &(curword->element.tailLine));
	}
}

void ReadFile(char* fileName ,treetype* wordTree, treetype* stopTree){
	char c, prevC;
	int count, line;
	char word[20];
	bool danhTuRieng, isAword;
	FILE *ptr=fopen(fileName,"r");
	if(ptr==NULL){
		printf("cant open %s\n", fileName);
		return;
	}
	for(count=0, line=1, prevC='f', isAword = false, danhTuRieng = false;(c=fgetc(ptr))!=EOF; prevC = c){
		// printf("%c",c);
		if(c>=65&&c<=90){//Upper
			c+=32;
			if(prevC==' '){//danh tu rieng
				danhTuRieng=true;
			}
		}

		if(c<97 || c>122){//end word
			if(!danhTuRieng && isAword){//save
				word[count]='\0';
				if(searchTbyword(*stopTree, word)==NULL){
					
					// printf("%s %d\n", word, line);
					AddWord(wordTree, word, line);
				}
			}

			count=0;
			danhTuRieng=false;
			isAword=false;

			if(c=='\n'){
				line++;
			}
		}
		else{
			if(!isAword) isAword=true;
			word[count++]=c;
		}
	}
	fclose(ptr);
}

int main(int argc, char const *argv[])
{
	treetype wordTree, stopTree;
	makeNullTree(&wordTree);
	makeNullTree(&stopTree);
	
	ReadFile("completed/stopw.txt", &stopTree, &wordTree);//build stop word

	ReadFile("completed/alice30.txt", &wordTree, &stopTree);//buil need to read word

	InOrderPrint(wordTree);
	// InOrderPrint(stopTree);

	freeTree(wordTree);
	freeTree(stopTree);
	return 0;
}