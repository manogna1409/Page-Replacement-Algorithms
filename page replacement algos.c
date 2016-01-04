#include<stdio.h>

void fifo(char [],char [],int,int);
void lru(char [],char [],int,int);
void opt(char [],char [],int,int);
void lfu(char [],char [],int,int);
void display(int,char [],char [],int);

int main()
{
   int ch,YN=1,i,l,f;
   char F[10],s[25];

   
   printf("\n\n\tEnter the number of empty frames: ");
   scanf("%d",&f);
   printf("\n\n\tEnter the length of the string:");
   scanf("%d",&l);
   printf("\n\n\tEnter the string: ");
   scanf("%s",s);
   for(i=0;i<f;i++)
     F[i]=-1;
      do
    {
      printf("\n1:fifo\n2:LRU\n3:OPT\n4:LFU\n5.EXIT");
      printf("\n\nEnter your choice: ");
      scanf("%d",&ch);
      //system(“clear”);
      switch(ch)
       {
      case 1:
          for(i=0;i<f;i++)
           {
             F[i]=-1;
           }

          fifo(s,F,l,f);
          break;
      case 2:
          for(i=0;i<f;i++)
           {
             F[i]=-1;
           }
          lru(s,F,l,f);
          break;
      case 3:
          for(i=0;i<f;i++)
           {
             F[i]=-1;
           }

          opt(s,F,l,f);
          break;
     case 4:
	  for(i=0;i<f;i++)
		F[i]=-1;
	lfu(s,F,l,f);
	break;

      case 5:
          exit(0);
       }
      printf("\n\n\tDo u want to continue IF YES PRESS 1\n\n\tELSE PRESS 0 : ");
      scanf("%d",&YN);
    }while(YN==1);return(0);
}

//fifo
void fifo(char s[],char F[],int l,int f)
{
   int i,j=0,k,flag=0,cnt=0;
   printf("\n\tPAGE\t    FRAMES\t  FAULTS");

   for(i=0;i<l;i++)
    {
       for(k=0;k<f;k++)
    {
      if(F[k]==s[i])
        flag=1;  // same element is already present 
    }

       if(flag==0)
    {
      printf("\n\t%c\t",s[i]);
      F[j]=s[i];
      j++;

      for(k=0;k<f;k++)
       {
        printf(" %c",F[k]);
       }
      printf("\tPage-fault%d",cnt);
      cnt++;
    }

       else   // same element loop
    {
      flag=0;
      printf("\n\t%c\t",s[i]);
      for(k=0;k<f;k++)
       {
        printf("%c",F[k]);
       }

      printf("\tNO page-fault");
    }
       if(j==f)
    j=0;
    
}

}


//LRU
void lru(char s[],char F[],int l,int f)
{
   int i,j=0,k,m,flag=0,cnt=0,top=0;
   printf("\n\tPAGE\t    FRAMES\t  FAULTS");
   for(i=0;i<l;i++)
    {
       for(k=0;k<f;k++)
    {
      if(F[k]==s[i])
       {
        flag=1; // means same element is present in F array
         break;
       }
    }

       printf("\n\t%c\t",s[i]);
       if(j!=f && flag!=1)
    {
      F[top]=s[i];
      j++;

      if(j!=f)
       top++;
    }
       else  // j==f 
    {
       if(flag!=1)
        {
          for(k=0;k<top;k++)
           {
        F[k]=F[k+1];   // bottom element is removed from stack
           }

           F[top]=s[i];
        }
       if(flag==1)
        {
           for(m=k;m<top;m++)
           {
        F[m]=F[m+1];   // k-> position of same element in stack. it is removed and same element is kept on top of stack
           }

           F[top]=s[i];
        }
    }
       for(k=0;k<f;k++)
    {
     printf("   %c",F[k]);
    }

       if(flag==0)
    {
      printf("\tPage-fault%d",cnt);
      cnt++;
    }
       else
     printf("\tNo page fault");
       flag=0;
    }

}

//optimal
void opt(char s[],char F[],int l,int f)
{
   int i,j=0,k,m,flag=0,cnt=0,temp[10];

   printf("\n\tPAGE\t    FRAMES\t  FAULTS");
   for(i=0;i<10;i++)
     temp[i]=0;

   for(i=0;i<f;i++)
     F[i]=-1;

   for(i=0;i<l;i++)
    {
       for(k=0;k<f;k++)
    {
      if(F[k]==s[i])
        flag=1;
    }

       if(j!=f && flag==0) // F array not full and  element is new
    {
      F[j]=s[i];
      j++;
    }

       else if(flag==0) // j==f
    {
       for(m=0;m<f;m++)
        {
          for(k=i+1;k<l;k++)
           {
          if(F[m]!=s[k])
           {
             temp[m]=temp[m]+1;
           }
          else
           break;
           }
        }

       m=0;
       for(k=0;k<f;k++)
        {
           if(temp[k]>temp[m])
        {
          m=k;
        }
        }

       F[m]=s[i];
    }

       printf("\n\t%c\t",s[i]);
       for(k=0;k<f;k++)
    {
       printf("  %c",F[k]);
    }
       if(flag==0)
    {
      printf("\tPage-fault %d",cnt);
      cnt++;
    }
       else
     printf("\tNo Page-fault");
       flag=0;

       for(k=0;k<10;k++)
     temp[k]=0;
     }
}



void lfu(char s[],char F[],int l,int f)
{

int i,j=0,k,ch,c,flag=0,a,nk;
int st,ps,pos;
for(i=0;i<f;i++)
F[i]=-1;
st=100;
for(i=0;i<l;i++)
{
	flag=0; // flag 
	st=100;
	pos=100;
for(c=0;c<f;c++)
if(s[i]==F[c])
flag++;

if(flag==0)
{
if(j<f)
{
F[j]=s[i];
j++;
}

else  // if filled
{
for(k=0;k<f;k++)
{
a=0; // count for frequency
for(ch=i;ch>=0;ch--)
{
if(F[k]==s[ch])
{
a++;    // a-frequency of element occured till now
nk=ch; // element index of that frequency
}

}

if(a>1)
{
if(st>a)
{
st=a;
ps=k; // ps -> frame index in refernce string
}
else
if(st==a) // if current and previous freq are same 
{
if(pos>ch) // we check for position
ps=k; // ps ->  position of element is stored
}

}

else
if(a==1)
{
if(pos>nk)  // if freq is same , we check the indexes 
{
pos=nk; // nk-> index of already occurance pos of the searching element 
ps=k; // ps -> frame index in refernce string
st=a; // st -> frequency of element              
}
}

}
F[(ps)]=s[i];
}
}
display(f,s,F,i);
} // first for loop

printf("\n");

}

void display(int f,char s[],char F[],int i)
{
          int k;
          if(i==1)
          {
                   printf("\t\t\t");
                   for(k=0;k<f;k++)
                   printf("_ _");
          }
          printf("\n%c",s[i]);
 
          for(k=0;k<f;k++)
          {
                   printf("|");
                   printf("_");
                   if(F[k]!=-1)
                   printf("%c",F[k]);
                   else
                   printf(" ");
                   printf("_");
          }
          printf("|");
}




