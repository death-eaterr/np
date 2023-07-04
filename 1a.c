#include <stdio.h>
#include<string.h>
int main()
{
    int n,len=0;
    printf("enter the no of frames:");
    scanf("%d",&n);
    char str[n][100];
    char op[100]="", conv[100];
    for(int i=0;i<n;i++){
        printf("enter the frame %d",i+1);
        scanf("%s",str[i]);
        len=strlen(str[i]);
        sprintf(conv,"%d",len);
        strcat(str[i],conv);
        strcat(op,str[i]);
        
    }
    printf("the byte stuffed data is:\n");
    printf("01111110-");
    printf("%s",op);
    printf("-01111110");
    

    return 0;
}
