#include<stdio.h>
#include<stdlib.h>


int present(int table_frame[], int nf, int page)
{

    for(int i=0; i<nf; i++)
        if(page == table_frame[i])
            return 1;
    return 0;

}

void printtable(int table_frame[], int nf)
{

    for(int i=0; i<nf; i++)
    {
        if(table_frame[i] == -1)
            continue;
        else
            printf("%02d ", table_frame[i]);
    }
  
}


void fifo(int *ReferencePages,int np,int nf)
{
  
    int i,pos=0;

    int table_frame[nf];
    for(i=0; i<nf; i++)
    {
        table_frame[i]=-1;
    }

   

    int count1=0;
 
    for(i=0; i<np; i++)
    {
        printf("%02d ",ReferencePages [i]);
        if(!present(table_frame,nf,ReferencePages[i]))
        {
            if(table_frame[pos]!=-1)
            {
                count1++;
                printf("F   ");
            }
            else
            {
                printf("    ");
            }
            table_frame[pos] = ReferencePages [i];
            pos = (pos+1)%nf ;//considering it as a queue
            printtable(table_frame,nf);
            printf("\n");
            continue;
        }
        else
        {
            printf("    ");
        }
        printtable(table_frame,nf);
        printf("\n");

    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", count1);

}



void optimal(int *ReferencePages,int np,int nf)
{

    int frames[nf], temp[nf];
    int flag1, flag2, flag3, i, j, k, pos, max,faults = 0;
    for(i = 0; i < nf; ++i)
    {
        frames[i] = -1;
    }
    for(i = 0; i < np; ++i)
    {

        printf("%02d ", ReferencePages[i]);
   
        flag1 = flag2 = 0;
        for(j = 0; j < nf; ++j)
        {
            if(frames[j] == ReferencePages[i])
            {
                flag1 = flag2 = 1;
                break;
            }
        }
//flag at the starting of the string
        if(flag1 == 0)
        {
            for(j = 0; j < nf; ++j)
            {
                if(frames[j] == -1)
                {

                    frames[j] = ReferencePages[i];
                    flag2 = 1;
                    break;
                }
            }
        }
//flag at the mid position
        if(flag2 == 0)
        {
            flag3 =0;
            for(j = 0; j < nf; ++j)
            {
                temp[j] = -1;
                for(k = i + 1; k < np; ++k)
                {
                    if(frames[j] == ReferencePages[k])
                    {
                        temp[j] = k;
                        break;
                    }
                }
            }
            for(j = 0; j < nf; ++j)
            {
                if(temp[j] == -1)
                {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }
//flag at the rear position
            if(flag3 ==0)
            {
                max = temp[0];
                pos = 0;
                for(j = 1; j < nf; ++j)
                {
                    if(temp[j] > max)
                    {
                        max = temp[j];
                        pos = j;
                    }
                }
            }
            frames[pos] = ReferencePages[i];
            faults++;
            printf("F   ");
        }
        else
        {
            printf("    ");
        }

        printtable(frames, nf);
        printf("\n");
    }

    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",faults);

}



int findLRU(int time[], int n)
{
    int i, minimum = time[0], pos = 0;

    for(i = 1; i < n; ++i)
    {
        if(time[i] < minimum)
        {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

void LRU(int *ReferencePages,int np,int nf)
{
    int  frames[nf], counter = 0, time[nf], flag1, flag2, i, j, pos, faults = 0;


    for(i = 0; i < nf; ++i)
    {
        frames[i] = -1;
    }

    for(i = 0; i < np; ++i)
    {
        printf("%02d ", ReferencePages[i]);
        flag1 = flag2 = 0;

        for(j = 0; j < nf; ++j)
        {
            if(frames[j] == ReferencePages[i])
            {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if(flag1 == 0)
        {
            for(j = 0; j < nf; ++j)
            {
                if(frames[j] == -1)
                {
                    counter++;
                   
                    frames[j] = ReferencePages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if(flag2 == 0)
        {
            pos = findLRU(time, nf);
            counter++;
            faults++;
            frames[pos] = ReferencePages[i];
            time[pos] = counter;
            printf("F   ");
        }
        else
        {
            printf("    ");
        }


        printtable(frames, nf);
        printf("\n");

    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",faults);

}




void clock(int *ReferencePages,int np,int nf)
{

    int frames[nf],rf_bit[nf];
    for(int i=0; i<nf; i++)
    {
        frames[i]=-1;
        rf_bit[i]=0;
    }

    int pos=-1,count1=0;

    for(int i=0; i<np; i++)
    {
        printf("%02d ",ReferencePages[i]);

        for(int j=0; j<nf; j++)
        {
            if(frames[j]==ReferencePages[i])
            {
               
                rf_bit[j]=1;
                break;
            }
        }

        if(!present(frames,nf,ReferencePages[i]))
        {

            pos=(pos+1)%nf;
            while(rf_bit[pos]==1)
            {
                rf_bit[pos]=0;
                pos=(pos+1)%nf;
            }

            if(frames[pos]!=-1)
            {
                count1++;
                printf("F   ");
            }
            else
            {
                printf("    ");
            }
            frames[pos]=ReferencePages[i];
            rf_bit[pos]=1;
            printtable(frames,nf);
            printf("\n");
         
            continue;
        }
        else
        {
            printf("    ");
        }
        printtable(frames,nf);
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", count1);
}



//function like strcmp

int compareStrings(char* x, char* y)
{
    int flag = 0;

   
    while (*x != '\0' || *y != '\0')
    {
        if (*x == *y)
        {
            x++;
            y++;
        }

       
        else if ((*x == '\0' && *y != '\0')
                 || (*x != '\0' && *y == '\0')
                 || *x != *y)
        {
            flag = 1;
            return flag;
            break;
        }
    }


  
    return flag;
  
}




int main()
{

    int NumOfpages;
    char algo[20];
    int *val=malloc(2*sizeof(int));


// printf("Size of pages is: \n");
    scanf("%d", &NumOfpages);

    // printf("algorithm is: \n");
    scanf("%s", algo);
    printf("Replacement Policy = %s\n", algo);
    printf("-------------------------------------\n");

    int i=0;
    int temp;


    scanf("%d",&temp);
    val[i]=temp;
    while(1)
    {
        scanf("%d",&temp);
        if(temp==-1)
            break;
      
        i=i+1;
        val=realloc(val,i*sizeof(val));
        val[i]=temp;
    }


    int length =i+1;

    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
    char fifo_algo[10]="FIFO";
    char optimal_algo[10]="OPTIMAL";
    char lru_algo[10]="LRU";
    char clock_algo[10]="CLOCK";

    if (compareStrings(algo,fifo_algo)==0)
    {
        fifo(val,length,NumOfpages);
    }
    else if (compareStrings(algo,optimal_algo)==0)
    {
        optimal(val,length,NumOfpages);
    }
    else if (compareStrings(algo,lru_algo)==0)
    {
        LRU(val,length,NumOfpages);
    }
    else if (compareStrings(algo,clock_algo)==0)
    {
        clock(val,length,NumOfpages);
    }
    return 0;
}

