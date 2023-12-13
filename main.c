// Mumen Anbar
// 1212297
// S3

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




typedef struct node{    // the struct of each node of the numbers
    // data members
    int Data;
    int LENGTH;
    struct node *Next;  // pointer points to the next node if exists
    struct node *Pre;   // pointer points to the previous node if exists
}Node;

typedef struct MainNode{    // the struct of each node of the Main Linked List
    int ID;
    struct node *ptrNum;
    struct MainNode *Next;
    struct MainNode *Pre;
}MainNode;

void insert(int x, struct node* Head, int length){ // function to insert a node to the front of the list
    struct node* temp = (struct node*)malloc(sizeof(struct node)); // allocating a space for the new node
    temp->Next = Head->Next;  // connect the new node to the next node of the head
    Head->Next = temp;  // connect the head to the new node
    temp->Pre = Head;   // connect the new node to the head by previous pointer
    temp->Data = x;     // give the node a value
    temp->LENGTH = length;
    if(temp->Next != NULL) temp->Next->Pre = temp;  // connect the next node of the head as the previous of it is the new one
}

void insertToEnd(int x, struct node* Head, int length){  // insert to the end of the list
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->Data = x;
    temp->LENGTH = length;
    temp->Next = NULL;
    while(Head->Next != NULL) Head = Head->Next;
    temp->Pre = Head;
    Head->Next = temp;
}

void InsertToMain(struct MainNode* Head, struct node* CurNum, int id){ // insert to the main list(2d list)
    struct MainNode* temp = (struct MainNode*)malloc(sizeof(struct MainNode));
    temp->Next = Head->Next;
    temp->ptrNum = CurNum; // connecting the number to the main list
    temp->ID = id;
    temp->Pre = Head;
    Head->Next = temp;
}
bool IsNegative(struct node* L){ // check if the number is negative
    return (L->Next->Data < 0);
}

int GetSize(struct node* cur){ // get the length of the number
    int cnt = 0;
    while(cur->Next != NULL) {
        cnt++;
        cur = cur->Next;
    }
    return cnt;
}

int cmp(struct node* L1, struct node* L2){ // compare between two numbers
    struct node* tmp1 = L1->Next;
    struct node* tmp2 = L2->Next;
    int sz1 = GetSize(L1), sz2 = GetSize(L2);

    if(sz1 == sz2){ // if they have same sizes
        while(tmp1 != NULL){ // iterate over their values and the first diff value determine the answer
            if(tmp1->Data > tmp2->Data) return 1;
            if(tmp1->Data < tmp2->Data) return -1;
            tmp1 = tmp1->Next;
            tmp2 = tmp2->Next;
        }
        return 0;
    }
    else{ // if the have diff size
        if(IsNegative(L1) && IsNegative(L2)){ // if the number is negative the if its size bigger so it's smaller
            if(sz1 < sz2) return 1;
            if(sz1 > sz2) return -1;
        }
        else if(IsNegative(L1)){ // if l1 is negative but l2 is not
            return -1;
        }
        else if(IsNegative(L2)){ // if l2 is negative but l1 is not
            return 1;
        }
        else{ // if both are positive
            if(sz1 < sz2) return -1;
            if(sz1 > sz2) return 1;
        }
    }
}
struct node* Clear(struct node* L){ // reinitialize the list

    if(L != NULL) Delete(L); // check if it's not null so delete the other nodes
    L = (struct node*)malloc(sizeof(struct node)); // creating a list
    if(L == NULL) printf("Out of memory!\n"); // if there is no space in memory
    L->Next = NULL;
    L->Pre = NULL;
    return L;
}
void Delete(struct node* L){ // delete a list
    struct node* P;
    struct node* temp;
    P = L->Next;
    L->Next = NULL;
    while(P != NULL){
        temp = P->Next;
        free(P);    // remove it from the memory
        P = temp;
    }
}
struct node* SubNegWithNeg(struct node* a, struct node* b){ // subtract two negative numbers
    struct node* ans = (struct node*)malloc(sizeof(struct node));
    ans->Next = NULL;
    ans->Pre = NULL;
    bool NegAns = (cmp(a, b) < 0); // b > a the answer will be negative
    if(NegAns){ // swap the values to have a > b
        struct node* tmp = a;
        a = b;
        b = tmp;
    }
    while(a->Next != NULL) a = a->Next;  // reverse the list
    while(b->Next != NULL) b = b->Next;  // reverse the list
    int size = 0, dec = 0;
    while((a->Pre != NULL) && (b->Pre != NULL)){ // while both lists have more nodes
        int x = a->Data, y = b->Data;
        if(x < 0){
            x = 9;
        }
        if(x < y){
            x -= dec;
            x += 10;
            dec = 1;
        }
        else x -= dec;
        int sum = x - y;
        insert(sum, ans, ++size); // add the sum value to the ans list
        a = a->Pre;
        b = b->Pre;
        if(dec) a = a->Pre;
    }
    while(a->Pre != NULL){ // if a list have extra nodes than b
        insert(a->Data, ans, ++size);
        a = a->Pre;
    }
    while(b->Pre != NULL){ // if b list have extra nodes than a
        insert(b->Data, ans, ++size);
        b = b->Pre;
    }
    if(NegAns) (ans->Next->Data) *= -1; // mul the answer to be negative
    return ans;
}
struct node* SubPosWithPos(struct node* a, struct node* b){ // subtract two positive numbers
    struct node* ans = (struct node*)malloc(sizeof(struct node));
    ans->Next = NULL;
    ans->Pre = NULL;
    bool NegAns = (cmp(a, b) < 0);
    if(NegAns){
        struct node* tmp = a;
        a = b;
        b = tmp;
    }
    while(a->Next != NULL) a = a->Next;
    while(b->Next != NULL) b = b->Next;
    int size = 0, dec = 0;
    while((a->Pre != NULL) && (b->Pre != NULL)){
        int x = abs(a->Data) - dec, y = b->Data; // dec is decreasing the num if we had larger previous number
        if(dec){
            dec = 0;
        }
        if(x < y){
            x += 10; // add 10 so we moved a digit to right
            dec = 1;
        }
        int sum = x - y;
        insert(sum, ans, ++size);
        a = a->Pre;
        b = b->Pre;
        if(dec) a = a->Pre;
    }
    while(a->Pre != NULL){
        insert(abs(a->Data), ans, ++size);
        a = a->Pre;
    }
    while(b->Pre != NULL){
        insert(abs(b->Data), ans, ++size);
        b = b->Pre;
    }
    if(NegAns) (ans->Next->Data) *= -1;
    return ans;
}
struct node* AddSameSign(struct node* a,struct node* b){  // add two negative/positive numbers
    struct node* ans = (struct node*)malloc(sizeof(struct node));
    ans->Next = NULL;
    ans->Pre = NULL;

    bool Negative = IsNegative(a);
    while(a->Next != NULL) a = a->Next;
    while(b->Next != NULL) b = b->Next;
    int size = 0;
    int carry = 0;
    while((a->Pre != NULL) && (b->Pre != NULL)){
        int sum = abs(a->Data) + abs(b->Data) + carry; // add each digit + the carry
        insert(sum % 10, ans, ++size);
        //printf("%d+%d   ", a->Data, b->Data);
        a = a->Pre;
        b = b->Pre;
        carry = sum / 10; // delete last digit of carry
    }
    while(a->Pre != NULL){
        insert((abs(a->Data) + carry) % 10, ans, ++size);
        carry = (abs(a->Data) + carry) / 10;
        a = a->Pre;
    }
    while(b->Pre != NULL){
        insert((abs(b->Data) + carry) % 10, ans, ++size);
        carry = (abs(b->Data) + carry) / 10;
        b = b->Pre;
    }
    if(carry) insert(carry, ans, ++size);
    if(Negative){
        (ans->Next->Data) *= -1;
    }
    return ans;
}
struct node* Sub(struct node* a, struct node* b){ // Main Subtract function
    struct node* ans;

    if(!IsNegative(a) && !IsNegative(b))ans = SubNegWithNeg(a, b); // if both are negative

    else if(IsNegative(a) && IsNegative(b)) ans = SubPosWithPos(a, b); // if both are positive

    else if(!IsNegative(a) && IsNegative(b)){ // if signs are different
        (b->Next->Data) *= -1; // mul the number by -1
         ans = AddSameSign(a, b);
        (b->Next->Data) *= -1;  // mul the number by -1
        (ans->Next->Data) *= -1;    // mul the number by -1
    }
    else if(IsNegative(a) && !IsNegative(b)){ // if signs are different
        (a->Next->Data) *= -1;  // mul the number by -1
         ans = AddSameSign(a, b);
        (a->Next->Data) *= -1;  // mul the number by -1
        (ans->Next->Data) *= -1;    // mul the number by -1
    }
    return ans;
}
struct node* Add(struct node* a,struct node* b){ // add function
    struct node* ans;
    if(a->Next == NULL || b->Next == NULL) ans = AddSameSign(a, b); // if they have same sign
    else if((!IsNegative(a) && !IsNegative(b)) || (IsNegative(a) && IsNegative(b))) ans = AddSameSign(a, b);
    else if(!IsNegative(a) && IsNegative(b)){
        (b->Next->Data) *= -1;
        ans = SubPosWithPos(a, b);
        (b->Next->Data) *= -1;
    }
    else if(IsNegative(a) && !IsNegative(b)){
        (a->Next->Data) *= -1;
        ans = SubPosWithPos(b, a);
        (a->Next->Data) *= -1;
    }
    return ans;
}
struct node* Mul(struct node* a, struct node* b){
    struct node* ans = (struct node*)malloc(sizeof(struct node));
    ans->Next = NULL;
    ans->Pre = NULL;
    //bool Neg = ((a->Next->Data < 0 && b->Next->Data > 0)||(a->Next->Data > 0 && b->Next->Data < 0)); // THIS IS THE CORRECT ONE FOR NEGATIVE NUMBERS

    while(a->Next != NULL) a = a->Next;
    while(b->Next != NULL) b = b->Next;
    struct node* FirstDigit = b;

    int DigitsDone = 0;
    while(a->Pre != NULL){
        struct node* CurRes = (struct node*)malloc(sizeof(struct node));
        CurRes->Next = NULL;
        CurRes->Pre = NULL;

        b = FirstDigit;
        for(int i = 0;i < DigitsDone; i++) insertToEnd(0, CurRes, 0);
        int carry = 0;
        while(b->Pre != NULL){
            //int CurMul = abs(b->Data) * abs(a->Data) + abs(carry); // THIS IS THE CORRECT ONE FOR NEGATIVE NUMBERS
            int CurMul = abs(b->Data) * abs(a->Data) + abs(carry);
            insert(CurMul % 10, CurRes, 0);
            carry = CurMul / 10;
            b = b->Pre;
        }
        if(carry) insert(carry, CurRes, 0);
        if(ans->Next == NULL) ans = CurRes;
        else ans = Add(ans, CurRes);
        DigitsDone++;
        a = a->Pre;
    }
    //if(Neg) (ans->Next->Data) *= -1; // THIS IS THE CORRECT ONE FOR NEGATIVE NUMBERS
    return ans;
}
struct node* Div(struct node* a, struct node* b){
    struct node* ans = (struct node*)malloc(sizeof(struct node));
    ans->Next = NULL;
    ans->Pre = NULL;

    bool Neg = ((a->Next->Data < 0 && b->Next->Data > 0)||(a->Next->Data > 0 && b->Next->Data < 0));
    bool ok = 0;
    if(b->Next->Data < 0){
        b->Next->Data *= -1;
        ok = 1;
    }
    struct node* cur = (struct node*)malloc(sizeof(struct node));
    cur->Next = NULL;
    cur->Pre = NULL;
    insert(abs(a->Next->Data), cur, 0);
    a = a->Next;
    int cnt = 0;
    while(a->Next != NULL){
        cnt = 0;
        //printf("%d\n",a->Data);
        while(cmp(b, cur) > 0 && (a->Next) != NULL){
            insertToEnd(abs(a->Next->Data), cur, 0);
            a = a->Next;
        }
        while(cmp(cur, b) >= 0){
            cur = Sub(cur, b);
            cnt++;
        }
        //printf("%d\n",cmp(b, cur));
        insert(cnt, ans, 0);
        //printf("%d\n",a->Next->Data);
    }
    if(Neg) (ans->Next->Data) *= -1;
    if(ok) b->Next->Data *= -1;
    return ans;
}
struct node* find(int x, struct MainNode* L){ // find the address of a list
    while(L->Next != NULL){
        L = L->Next;
        if(L->ID == x) return (L->ptrNum);
    }
    return NULL;
}

int main()
{
    struct MainNode* Head = (struct MainNode*)malloc(sizeof(struct MainNode));
    Head->Next = NULL;
    Head->Pre = NULL;

    FILE* FileIn;
    FILE* FileOut;
    FileIn = fopen("input.txt", "r");
    FileOut = fopen("output.txt", "w");
    int size = 0;
    char num[1000];
    char c;
    int cnt = 0;
    if(FileIn){
        while ((c = getc(FileIn)) != EOF){ // while unfinishing
            if(c != ' '){
                num[size++] = c;
            }
            else{
                struct node* CurNum = (struct node*)malloc(sizeof(struct node));
                CurNum->Next = NULL;
                CurNum->Pre = NULL;
                for(int i = size - 1;i >= 0; i--) {
                    if(i == 1 && (num[i - 1] == '-' || num[i - 1] == '+')){
                        if(num[i - 1] == '+') insert((num[i] - '0'), CurNum, size - 1);
                        else insert((num[i] - '0') * -1, CurNum, size - 1);
                        break;
                    }
                    insert((num[i] - '0'), CurNum, size);
                }
                InsertToMain(Head, CurNum, ++cnt);
                size = 0;
            }
        }
    }
    if(size){
        struct node* CurNum = (struct node*)malloc(sizeof(struct node));
        CurNum->Next = NULL;
        CurNum->Pre = NULL;
        for(int i = size - 1;i >= 0; i--) {
            if(i == 1 && (num[i - 1] == '-' || num[i - 1] == '+')){
                if(num[i - 1] == '+') insert((num[i] - '0'), CurNum, size - 1); // I WAS DEBUGGING HERE
                    else insert((num[i] - '0')*-1, CurNum, size - (num[0] == '-' || num[0] == '+'));
                    break;
            }
                    insert((num[i] - '0'), CurNum, size - (num[0] == '-' || num[0] == '+'));
        }
        InsertToMain(Head, CurNum, ++cnt);
    }
    struct MainNode* tmp = Head->Next;
    printf("Please Choose Two Numbers of The Following:\n");
    while(tmp != NULL){
        printf("%d- ", cnt - (tmp->ID) + 1);
        struct node* CurNode = tmp->ptrNum;
        while(CurNode->Next != NULL){
            CurNode = CurNode->Next;
            printf("%d", CurNode->Data);
        }
        tmp = tmp->Next;
        printf("\n");
    }
    int x;
    printf("1st Num ID:\n");
    scanf("%d", &x);
    struct MainNode* L1 = find(cnt - x + 1, Head);
    printf("2nd Num ID:\n");
    scanf("%d", &x);
    struct MainNode* L2 = find(cnt - x + 1, Head);

    struct node* ans;
    fprintf(FileOut, "Results:\n");
    fprintf(FileOut, "Addition: ");
    ans = Add(L1, L2);
    while(ans->Next != NULL){    // iterate over the list
        ans = ans->Next;
        fprintf(FileOut, "%d", ans->Data); // print of the file
    }
    fprintf(FileOut, "\n");

    fprintf(FileOut, "Subtraction: ");
    ans = Sub(L1, L2);
    while(ans->Next != NULL){    // iterate over the list
        ans = ans->Next;
        fprintf(FileOut, "%d", ans->Data); // print of the file
    }
    fprintf(FileOut, "\n");

    fprintf(FileOut, "Multiplication: ");
    ans = Mul(L1, L2);
    while(ans->Next != NULL){    // iterate over the list
        ans = ans->Next;
        fprintf(FileOut, "%d", ans->Data); // print of the file
    }
    fprintf(FileOut, "\n");

    fprintf(FileOut, "Division: ");
    ans = Div(L1, L2);
    while(ans->Next != NULL){    // iterate over the list
        ans = ans->Next;
        fprintf(FileOut, "%d", ans->Data); // print of the file
    }
    fprintf(FileOut, "\n");

    fclose(FileIn);
    fclose(FileOut);
    return 0;
}
