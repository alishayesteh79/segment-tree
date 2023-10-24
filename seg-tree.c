// IN THE NAME OF GOD

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int getmid(int s, int e) { 
	return s + (e -s)/2;
}

int max(int z,int x){
    if(z>x){
        return z;
    }
    else return x;
}
int min(int z,int x){
    if(z>x){
        return x;
    }
    else return z;
}


void add(int* st , int sl  ,int sr , int ql , int qr , int si){
    if (sl > qr || sr < ql){
        return ;
    }
    int l = max(sl , ql);
    int r = min(sr , qr);
    int difl = l-ql;
    int difr = r -ql;
    // int lvalue = arr[l];
    // int rvalue = arr[r];
    int num = r - l + 1;
    int value = num*((difl+difr)/2);
    
    st[si] += value;
    
    if(sl != sr){
        int mid = getmid(sl,sr);
        add(st, sl, mid, ql, qr, 2*si + 1);
        add(st, mid+1, sr, ql, qr, 2*si + 2);
    }
    
    
    
    
}
int getsum(int *st, int sl, int sr, int ql, int qr, int si){
	// If segment of this node is a part of given range, then return
	// the sum of the segment
	if (ql <= sl && qr >= sr)
		return st[si];
		
	// If segment of this node is outside the given range
	if (sr < ql || sl > qr)
		return 0;

	// If a part of this segment overlaps with the given range
	int mid = getmid(sl, sr);
	return getsum(st, sl, mid, ql, qr, 2*si+1) +
		getsum(st, mid+1, sr, ql, qr, 2*si+2);

}
	
	
	
	

int ask(int* st, int n, int l, int r){
	// Check for erroneous input values
	if (l < 0 || r > n-1 || l > r)
	{
		printf("Invalid Input");
		return -1;
	}
	int sum = getsum(st, 0, n-1, l, r, 0);
	
	return sum % (1000000009);
}



int fillst(int arr[], int l, int r, int *st, int si){
	
	if (l == r){
		st[si] = arr[l];
		return arr[l];
	}
	
	int mid = getmid(l , r);
	st[si] = fillst(arr, l, mid, st, si*2+1) +
			fillst(arr, mid+1, r, st, si*2+2);
	return st[si];
	
}


int *constructst(int arr[], int n){
	int h = (int)(ceil(log2(n)));
	int max_size = 2*(int)pow(2, h) - 1;
	
	int* st =(int*)malloc(max_size*sizeof(int));
	
	fillst(arr, 0, n-1, st, 0);
	return st;

}

int main(){
//	int arr[] = {1, 3, 5, 7, 9, 11};
//	n = sizeof(arr)/sizeof(arr[0]);
//	
//	//construct the segment tree
//	int *segt = construct(arr, n);
	int n ;
	int q ;
	int arr[n];
	scanf("%d %d" , &n , &q);

	for (int i = 0 ; i < n ; i++){
		scanf("%d", &arr[i]);
		
	}

	char task[q][3];
	int task1[q];
	int task2[q];
	
	char temp[3];
	for(int i = 0 ; i < q ; i++){
		scanf("%s %d %d", temp , &task1[i] , &task2[i] );
		task[i][0] = temp[0];
		task[i][1] = temp[1];
		task[i][2] = temp[2];
	}

	
	int* st = constructst(arr , n);
	
	for (int i = 0 ; i < q ; i++){
	    
	   if(task[i][0] == 'a' && task[i][1] == 's' && task[i][2] == 'k'){
	       printf("%d\n", ask(st, n, task1[i]-1 , task2[i]-1));
	   }
	   if(task[i][0] == 'a' && task[i][1] == 'd' && task[i][2] == 'd'){
	       add(st,0,n-1,task1[i]-1,task2[i]-2,0);
	   }
	   
	}
	
}
