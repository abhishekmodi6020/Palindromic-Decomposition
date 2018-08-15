/*
 * palindromic_decomp.c
 *
 *  Created on: 08-Oct-2017
 *      Author: Abhishek Modi
 */

#include<stdio.h>
#include<string.h>

char reverse(char *word,int count,int len){
	if(len == 1) return NULL;
	char temp = word[len - 1];
	word[len - 1] = word[count];
	word[count] = temp;

	if (strlen(word)%2 == 0){
		if((strlen(word)-1)/2 == count) return NULL;
		count++;
		len--;
		return reverse(word,count,len);
	}else if(strlen(word)%2 != 0){
		if((strlen(word)/2) == count) return NULL;
		count++;
		len--;
		return reverse(word,count,len);
	}
return NULL;
}

int inorder(int * A, int N){
//	1	2	2	4	5
	int f1,f2,f3,x;
	int i,count = 1;
	for(i=0;A[i] != NULL;i++){
		count++;
	}
	if(count < 3){
		return 1;
	}

	//	Setting flag 1 to appropiate values
	if (A[N-1] > A[N-2]){
		f1 = 1;
		f3 = 1;
	}
	else if (A[N-1] < A[N-2]){
		f1 = 2;
		f3 = 2;
	}
	else if (A[N-1] == A[N-2]) f1 = 3;

	//	setting flag 2 to appropiate values
	if (A[N-2] > A[N-3]){
		if(f1 == 3) f2 = 3;
		else f2 = 1;
	}
	else if (A[N-2] < A[N-3])
		if(f1 == 3) f2 = 3;
		else f2 = 2;
	else if (A[N-2] == A[N-3]){
		if(f1 == 1) f2 = 1;
		else if (f1 == 2) f2 = 2;
		else if (f1 = 3) f2 = 3;
	}

	if(f1!=f2) return 0;
	//	After all comparisions
	if((N-3)== 0)return 1;

	x = inorder(A,N-1);
	return x;
}


int check_pal(char *A){
	int counter = 0, len = strlen(A);
	while(counter < (len -1)){
		if(A[counter] != A[len -1]){
			return 0;
		}
		counter++;
		len--;
	}
	return 1;
}

char pal_decomp(char * sub1,char * temp2,int * count,int * total){
	/* count is used for displaying the final output
	 * and it value depends upon sub1 string.
	 */
	char sub2[8];
	char temp[100];
	int i,j,k,x,is_pal;
	int sub2_len,sub1_len;

	//	Base case i.e when sub1 = NULL;
	if(strlen(sub1) == 0) return NULL;

	//	nested for taking combinations such as a, ab, aba..
	for(i=0;sub1[i]!= NULL;i++){
		for(j=0;sub1[j]!=NULL;j++){

			//	Storing values in substring 2
			for(k = 0;k<=j;k++){
				sub2[k] = sub1[k];
			}
			sub2[k] = NULL;					//	ending sub2 with \0.

			sub2_len = strlen(sub2);
			sub1_len = strlen(sub1);
			x = sub2_len;

			//	removing values from sub1 which are in sub2
			strcpy(temp,sub1);
			for(k=0;k<sub1_len-sub2_len;k++,x++){
				sub1[k] = temp[x];
			}
			sub1[k] = NULL;					//	ending sub2 with \0.

			//	Check sub2 is palindrome.
			if(sub2_len == 1 || sub2_len == 0) is_pal = 1;
			else{
				is_pal = check_pal(sub2);
			}

			//	if sub2 is not pal.->then return
			if(is_pal == 0) {
				strcpy(sub1,temp);
				if(sub2_len == strlen(temp)){
					return NULL;
				}else{
					continue;
				}
			}

			//	Truncates temp2 for storing appropiate values
			while(*count!=0){
				if(!isalnum(temp2[strlen(temp2)-1])){
					temp2[strlen(temp2)-1] = NULL;
				}
				else{
					temp2[strlen(temp2)-1] = NULL;
					*count = *count - 1;
				}
			}
			// Appends value of sub2 to temp2 for printing
			strcat(temp2,sub2);
			strcat(temp2,", ");
//			printf("%s\n",sub2);

			//	Returns to the previous recurssion if sub1 is NULL.
			if(strlen(sub1) == 0){
				*total = *total + 1;
				printf("%s\n",temp2);
				return NULL;
			}
			pal_decomp(sub1,temp2,count,total);
//			printf("\n-------------------------------------------\n");
			strcpy(sub1,temp);
			*count = strlen(sub1);

		}
	}
}



void main(){
	//	Remember to comment the below line
	setbuf(stdout, NULL);

	//	Task 1
	printf("Enter strings. Stop with -1.\n");
	while(1){
		char word[100];
		int count = 0;

		scanf("%s",word);
		if(!(strcmp(word,"-1"))){
			printf("s = ");
			break;
		}
		reverse(word,count,strlen(word));
		printf("s = reversed: %s\n",word);
	}

	//	Task 2
	while(1){
		int i, N, x;
		printf("Enter size of array. (Stop with -1.) ");
		scanf("%d",&N);
		if(N == -1) break;
		int arr[100];
		printf("Enter array elements separated by spaces: ");
		for(i=0;i<N;i++){
			scanf("%d",&arr[i]);
		}
		arr[i] = NULL;
//		printf("array is:\n");
//		for(i = 0;i<N;i++){
//			printf("%d\n",arr[i]);
//		}
		x = inorder(arr,N);
		printf("sorted: %d\n",x);
	}


	//	Task 3
	printf("Enter strings. Stop with -1.\n");
	while(1){
		int total = 0;
		char sub[100];
		int count = 0;
		char temp2[200];
		temp2[0] = NULL;

		scanf("%s",sub);
		if(strlen(sub) == 2 ){
			if(!strcmp(sub,"-1")){
				printf("s =\n");
				break;
			}
		}
		printf("s =\n");
		pal_decomp(sub,temp2,&count,&total);
		printf("%d\n\n",total);
	}


}
