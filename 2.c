#include<stdio.h>
#include<string.h>
#define N strlen(gen_poly)

char gen_poly[28];
char data[28];
char check[30];
int data_length,i, j;

void XOR()
{
    for(int k=1;k<N;k++)
    {
        check[k] = (check[k] == gen_poly[k])?'0':'1';
    }
}

void crc()
{
    for(i=0;i<N;i++)
    {
        check[i] = data[i];
    }
    do
    {
        if(check[0] == '1')
        {
            XOR();
        }
        for(j=0;j<N-1;j++)
        {
            check[j] = check[j+1];
        }
        check[j] = data[i++];
    }while(i<=data_length+N-1);
        
}

void receiver()
{
    printf("Enter the recieverd data\n");
    scanf("%s",data);
    printf("Data recieved : %s\n",data);
    
    crc();
    
    for(i=0;((i<N-1) && (check[i] !='1')); i++);
    
    if(i<N-1)
        printf("Error Detected\n");
    else
        printf("No error detected\n");
}

int main()
{
    printf("Enter the Data to be transmitted\n");
    scanf("%s",data);
    
    printf("Enter the Generating polynomial\n");
    scanf("%s",gen_poly);
    
    data_length = strlen(data);
    
    for(i=data_length; i<data_length+N-1; i++)
    {
        data[i] = '0';
    }
    
    printf("the Data to be transmitted :%s\n", data);
    printf("The generating polynomial :%s\n",gen_poly);
    
    crc();
    
    printf("CRC value :%s \n",check);
    
    for(i=data_length; i<data_length+N-1; i++)
    {
        data[i] = check[i-data_length];
    }
    printf("Data to be transmitted:%s\n",data);
    
    receiver();
    return 0;

}
