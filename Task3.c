#include <math.h>
#include <stdlib.h>
#include <stdio.h>
int func(int** arr, int* n, int* len_arr);

int func(int** arr, int* n, int* len_arr){
int summ=0, count=0, flag=0,s=0, average=0;
int temp_len=0, leng;
int* temp_arr;
for(int i=0; i<*n; i++ ){
    count=count+len_arr[i];
}
for (int i=0; i<*n; i++){
    for(int j=0; j<len_arr[i]; j++){
        summ=summ+arr[i][j];
    }

}
average=summ/count;
for (int i=0; i<*n; i++){
    for(int j=0; j<len_arr[i]; j++){
        if (arr[i][j] == average){
           flag=1;
           s=i;
         }
    }
    if(flag!=0)break;
}
if(flag==0){
return 2;
}
else{
    temp_arr = (int*)malloc(0*sizeof(int));
    for (int d = s; d < (*n-1); d++){
        temp_len = len_arr[d];
        temp_arr = (int*)realloc(temp_arr, temp_len*sizeof(int));
        for (int e = 0; e < temp_len; e++){
            temp_arr[e] = arr[d][e];
        }
        arr[d] = (int*)realloc(arr[d], len_arr[d+1]*sizeof(int));
        for (int j = 0; j < len_arr[d+1]; j++){
        arr[d][j] = arr[d+1][j];
        }
        arr[d+1] = (int*)realloc(arr[d+1], temp_len*sizeof(int));
        for (int f = 0; f < temp_len; f++){
        arr[d+1][f] = temp_arr[f];
        }
    }
    *n = *n-1;
    arr = (int**)realloc(arr, (*n)*sizeof(int*));

    for (int p=s; p<*n; p++){
        leng=len_arr[p];
        len_arr[p]=len_arr[p+1];
        len_arr[p+1]=leng;
    }
    len_arr=(int*)realloc(len_arr, (*n)*sizeof(int));

    free(temp_arr);
    return 0;
}
}


int main(void){
FILE*input;
FILE*output;
char temp[512];
int** arr;
int* len_arr;
int n=0,m=0,p=0;
char* string;
input=fopen("data.dat.txt", "r");
output=fopen("data.res.txt", "w");
if(!input || !output){
        printf("Невозможно открыть файл\n");
        return 1;
}
while(fgets(temp, sizeof(temp), input)!=NULL){
     n++;
}
fseek(input, 0, 0);
arr=(int**)malloc(n*sizeof(int*));
len_arr=(int*)malloc(n*sizeof(int));
if (arr==NULL || len_arr==NULL){
        printf("Невозможно выделить память\n");
        return 1;
}
for (int i=0; i<n; i++){
        string=fgets(temp, sizeof(temp), input);
        p=0;
        m=0;
        while (string[p]!='\0'){
            p++;
        }
        for (int k=0; k<p-1; k++){
            if (string[k]==' '){
                m++;
            }
        }
        len_arr[i]=m+1;
}
fseek(input, 0, 0);
for(int i=0; i<n; i++){
    arr[i]=(int*)malloc(len_arr[i]*sizeof(int));
    for (int j=0; j<len_arr[i]; j++){
        fscanf(input, "%d", &(arr[i][j]));
    }
}

printf("Исходный массив:\n");
for (int i=0; i<n; i++){
    for(int j=0; j<len_arr[i]; j++){
        printf("%d ", arr[i][j]);
    }
    printf("\n");
}
func(arr, &n, len_arr);
printf("Новый массив:\n");
for (int i=0; i<n; i++){
    for(int j=0; j<len_arr[i]; j++){
        printf("%d ", arr[i][j]);
        fprintf(output,"%d ", arr[i][j]);
    }
    printf("\n");
    fprintf(output, "\n");
}

free(len_arr);
for(int i=0; i<n; i++){
        free(arr[i]);
}
free(arr);
fclose(input);
fclose(output);
return 0;
}
