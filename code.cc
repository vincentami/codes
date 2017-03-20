// 最少时间复杂度求数组中第k大的数，写code

#include <iostream>
#include <string.h>

#define BUFLEN (10)

using namespace std;

int buf[] = {9, 7, 7, 2, 1, 8, 0, 2, 0, 11};

void printBuf(int*buf, int len){
	for(int i = 0; i< len; i++){
		cout << buf[i] << " ";
	}
	cout << endl;
}

void swap(int*buf, int bi, int si){
	int mid = buf[bi];
	buf[bi] = buf[si];
	buf[si] = mid;
}

int partition(int *buf, int len){
	int midVal = buf[0];
	int mid = 0;
	int beg = 0;
	int end = len - 1;

	//cout << "partition:" << len << endl;
	if(len == 2){
		if(buf[0] >= buf[1]){
			return 0;
		}else {
			swap(buf, 0, 1);
			return 1;
		}
	}else {
		while(beg < end){
			while(buf[end] < midVal && beg < end){
				end --;	
			}
			if (beg >= end){
				break;
			}
			buf[mid] = buf[end];
			mid = end;
			end --;
			while(buf[beg] > midVal && beg < end){
				beg ++;
			}
			if(beg >= end){
				break;
			}
			buf[mid] = buf[beg];
			mid = beg;
		}
		buf[mid] = midVal;
		return mid;
	}
}

int findTopK(int*buf, int len, int k){
	int index  = 0;

	if (k < 0 || k > len || len <= 0){
		return -1;
	}

	if (len == 1){
		return buf[0];
	}
	index = partition(buf, len);

	//cout << index << " " << k << endl; 
	//printBuf(buf, len);

	if (index == k){
		return buf[index];	
	}else if(index < k) {   
		return findTopK(&buf[index + 1],
			 len - index - 1 , k - index - 1);
	}else {
		return findTopK(buf, index, k);
	}
}

void qsort(int*buf, int len){
	int index = -1;
	if(len <= 1){
		return ;
	}

	if(len == 2){
		if(buf[0] < buf[1]){
			swap(buf, 0, 1);
		}
		return ;
	}

	index = partition(buf, len);
	if(index <= 1){
		qsort(&buf[index+1], len - index - 1);	
	}else if(index >= len - 1){
		qsort(buf, index);
	}else {
		qsort(buf, index);
		qsort(&buf[index + 1], len - index - 1);
	}
}

//litle root heap;
void hadjust(int*buf, int len){
	int i = -1;
	int next = -1;
	int mid = -1;
	int midVal = -1;

	if (len <= 1){
		return ;
	}

	swap(buf, 0, len - 1);

	if (len - 1 == 2){
		if(buf[0] > buf[1]){
			swap(buf,0, 1);
		}
		return ;
	}

	if (len - 1 == 3){
		if(buf[1] < buf[2]){
			next = 1;
		}else{
			next = 2;
		}

		if(buf[next] < buf[0]){
			swap(buf,0, next);
		}
		return ;
	}

	mid = 0 ;
	midVal = buf[mid];
	i = 1;
	while(i*2 - 1 < len - 1){
		if(i*2 < len - 1){
			if(buf[i*2 - 1] < buf[i*2]){
				next = i*2 - 1;	
			}else{
				next = i*2 ;
			}
		}else {
			next = i*2 - 1;
		}

		if(buf[next] < midVal){
			swap(buf, next, mid);
			i = next;
			mid = next;
			midVal = buf[next];
		}else {
			break;
		}
	}
}

// litle root heap;
void hinit(int*buf, int len){
	int i = 0;
	int j = 0;
	int next = 0;
	int mid = -1;
	int midVal = -1;
	if(len <= 1) return ;
	if(len == 2) {
		if(buf[0] < buf[1]){
			swap(buf, 0, 1);
		}
		return ;
	}

	i = len/2 ;
	while(i >= 0){
		j = i;
		mid = i ;
		midVal = buf[mid];
		while(j*2 < len ){
			if((j*2 + 1) <len ){
				if(buf[j*2] < buf[j*2 +1]){
					next = j*2;	
				}else{
					next = j*2 + 1;
				}
			}else{
				next = j*2;
			}

			if(midVal > buf[next]){
				swap(buf, next, mid);
				mid = next ;
				midVal = buf[mid];
				j = next;
			}else{
				break;
			}
		}
		i--;
	}
} 

void hsort(int*buf, int len){
	hinit(buf, len);
	printBuf(buf, len);
	cout << "Heap create\n";
	for(int i = len ; i > 0 ; i--){
		hadjust(buf, i);	
		printBuf(buf, len);
	}
}

void adjustStr(char*buf, int index, int tlen, int len){
	int beg = index;
	for(int i= index + tlen; i< len; i++, beg++){
		buf[beg] = buf[i];
	}

	buf[beg] = '\0';
}

void clearStr(char*buf, int len, string token){
	int i = -1;
	int tlen = token.length();

	while(true){
		for(i = 0; i<= len - tlen ; i ++){
			if(strncmp(&buf[i],token.c_str(), tlen)==0){
				adjustStr(buf, i, tlen, len);
				len = len - tlen;
				break;		
			}
		}
		if(i > len - tlen){
			break;
		}
	}
}

struct pNode{
	char val;
	struct pNode* next;
};

pNode* createList(char* buf, int len){
	pNode* phead = NULL;
	pNode* pp = NULL;
	pNode* ptmp = NULL;
	for(int i = 0; i < len; i++){
		ptmp = new pNode();
		ptmp->val = buf[i];
		ptmp->next = NULL;
		if(i == 0){
			phead = ptmp;
		}else{
			pp->next = ptmp;
		}
		pp = ptmp;
	}
	return phead;
}

pNode* revertList(pNode* phead){
	if(phead == NULL || phead->next == NULL){
		return phead;
	}

	pNode* pp = NULL;
	pNode* pcur = phead;
	pNode* pnext = pcur->next;

	for(; pnext!= NULL;){
		pcur->next = pp;
		pp = pcur;	
		pcur = pnext;
		pnext = pnext->next;
	}
	pcur->next = pp;

	phead = pcur;
	return phead;
}

// a b c d 	e f 
// c b a f 	e d
//   1 2 
pNode* revertXList(pNode* ph, int step){
	pNode* pret = NULL;
	pNode* phead = ph;
	pNode* ptail = ph;
	pNode* pMid = phead;
	pNode* pTail = NULL;
	pNode* pHead = NULL;
	int i = 0;

	while(true){
		phead = pMid;
		ptail = phead;
		for(i = 1; i< step; i++){
			if(ptail->next == NULL)
				break;
			ptail = ptail->next;
		}

		if(i == step){
			pMid = ptail->next; //store head next step;
			ptail->next = NULL;		
		}else{
			pMid = NULL;
		}

		ptail = phead;
		pHead = revertList(phead);
		if(pret == NULL){
			pret = pHead;
		}
		if(pTail != NULL){
			pTail->next = pHead;  //join last tail && head;
		}else{
			pTail = ptail;  
		}
		if(pMid == NULL){  //last Convert;
			break;
		}
	}
	return pret;
}

pNode* createcircle(pNode *phead){
	int i = 0;
	pNode* pp = phead;
	pNode* ptmp = phead;
	pNode* pcir = NULL;
	if(phead == NULL || phead->next == NULL){
		return phead;
	}

	for(i = 0,ptmp= phead; ptmp->next!= NULL;){
		pp = ptmp;
		ptmp = ptmp->next; 
		if(i++%3 == 1){
			pcir = pp;
		}
	}

	pp->next = pcir;
	return phead;
}

bool checkList(pNode* phead){
	if(phead == NULL || phead->next == NULL)
		return false;
	if(phead->next == phead) 
		return true;

	pNode *pp = NULL;
	pNode *pcur = phead;
	pNode *pnext = pcur->next;

	for(;pnext != NULL;){
		pcur->next = pp;
		pp = pcur;
		pcur = pnext;
		pnext = pnext->next;		
	}

	pcur->next = pp;

	return (pcur == phead);
}

void printList(pNode* phead){
	pNode *ptmp = phead;

	for(; ptmp!= NULL; ptmp = ptmp->next){
		cout << ptmp->val << " ";
	}
	cout << endl;
}

//Both Heap;
void* mymemcpy(void*dest, const void* src, int len)
{
	char *d = (char*)dest;
	char *s = (char*)src;
	int l = len;
	if(d == NULL || s == NULL || len <= 0){
		return dest;
	}

	if(d >= s + len || d < s){
		while(len--){
			*d++ = *s++;
		}
	}else{  // src < dest < src+len;
		d = d + len;
		s = s + len;
		while(len--){
			*d-- = *s--;
		}
	}
	return dest;
}

int bfind(int*buf, int len, int val){	
	int beg = -1;
	int end = -1;
	int mid = -1;
	if(len <= 0 ){
		return -1;
	}
	if(len == 1){
		if(buf[0] == val)
			return 0;
		else 
			return -1;
	}

	beg = 0;
	end = len - 1;

	while(beg < end){
		mid = (beg + end)/2;
		if(buf[mid] > val){
			beg = mid + 1;
		}else if(buf[mid] < val){
			end = mid - 1;
		}else{
			return mid;
		}	
	}
	return -1;
}

struct BNode{
	char val;
	BNode *pleft;
	BNode *pright;
};

BNode *BTreeCreate(char*buf, int len, int* tracer)
{	
	BNode* pnew = NULL;
	int index = *tracer;
	if(index >= len){
		return pnew;
	}
	if(buf[index] == '#'){
		(*tracer)++;
		return pnew;	
	}else {
		pnew = new BNode();
		pnew->val = buf[index];
		(*tracer)++;

		pnew->pleft = BTreeCreate(buf, len, tracer);
		pnew->pright = BTreeCreate(buf, len, tracer);
		return pnew;
	}	
}

void BTreePrePrint(BNode *ph){
	if(ph == NULL) return ;
	cout << ph->val << " ";
	if(ph->pleft == NULL){
		;//cout << "#" << " ";
	}else{
		BTreePrePrint(ph->pleft);
	}

	if(ph->pright == NULL){
		;//cout << "#" << " ";
	}else{
		BTreePrePrint(ph->pright);
	}
}

void BTreeMidPrint(BNode *ph)
{
	if(ph == NULL) return ;
	if(ph->pleft != NULL){
		BTreeMidPrint(ph->pleft);	
	}
	cout << ph->val << " "; 
	if(ph->pright != NULL){
		BTreeMidPrint(ph->pright);
	}
}

int bfindB(int *buf, int len , int sum){
	int beg = 0;
	int end = len - 1;
	int mid = 0;
	int bigger = end;

	while(beg < end){
		mid = (beg+end)/2;
		if(buf[mid] < sum){
			beg++;			
		}else if(buf[mid] > sum){
			bigger = mid;
			end--;
		}else{
			break;
		}
	}
	return bigger;
}

void findSum(int*buf, int len, int sum)
{
	int beg = 0;
	int end = bfindB(buf, len, sum) - 1;

	while(beg < end){
		if(buf[beg]+ buf[end] > sum){
			end--;
		}else if(buf[beg] + buf[end] < sum){
			beg++;
		}else{
			cout<< buf[beg] << " + "<< buf[end] << endl;
			beg++;
		}
	}
}

BNode* BTreeConvert(BNode *ph){
	BNode *pl = NULL;
	BNode *pr = NULL;
	BNode *proot = ph;
	if(ph == NULL) return NULL;

	if(ph->pleft != NULL){
		pl = BTreeConvert(ph->pleft);
		while(pl && pl->pright!= NULL){
			pl = pl->pright;		
		}
		pl->pright = proot;
		proot->pleft = pl;
	}
	
	if(ph->pright != NULL){
		pr = BTreeConvert(ph->pright);
		while(pr && pr->pleft != NULL){
			pr = pr->pleft;
		}
		pr->pleft = proot;
		proot->pright = pr;
	}	

	return proot;
}

int findCommonLen(string lstr, string sstr)
{
	

	
}

int main(){
	//int len = sizeof(buf)/sizeof(buf[0]);
	//int k = findTopK(buf, sizeof(buf)/sizeof(buf[0]), 4);
	//cout << "find: "<< k << endl;
	/*qsort(buf, sizeof(buf)/sizeof(buf[0]));
	for (int i =0; i< sizeof(buf)/sizeof(buf[0]); i++){
		cout << buf[i] << " "<< endl;
	}*/

	//hsort(buf,len);
	//cout << "bfind:" << bfind(buf, len, 2) << endl;
	//char buf[] = "adjustStr";
	//cout << "B:" << buf<< endl;
	//clearStr(buf, sizeof(buf)/sizeof(buf[0]), "us");
	//cout << "A:" << buf<< endl;
	/*	
	pNode* phead = createList(buf, sizeof(buf)/sizeof(buf[0]));
	printList(phead);

	phead = revertList(phead);
	printList(phead);

	phead = createcircle(phead);
	//printList(phead);

	bool isRound = checkList(phead);
	cout << "isRound :" << isRound << endl;*/

	/*string str("test");
	char bufA[10];
	memcpy(bufA, str.c_str(), str.length());
	char *bufB = &bufA[2];*/

	//Mid O
	/*
	char btBuf[] = "ABC##DE#GF#H#"; 
	int index = 0;

	cout << btBuf << endl;
	BNode *pn = BTreeCreate(btBuf, sizeof(btBuf)/sizeof(btBuf[0]), &index);

	BTreePrePrint(pn);
	cout << endl;

	BTreeMidPrint(pn);
	cout << endl;*/
}










