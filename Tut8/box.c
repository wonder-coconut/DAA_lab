/* Dynamic Programming implementation of Box Stacking problem */
#include<stdio.h>
#include<stdlib.h>
  
/* Representation of a box */
struct Box
{
  // h --> height, w --> width, d --> depth
  int h, w, d;  // for simplicity of solution, always keep w <= d
};

int min (int x, int y)
{ 
    return (x < y)? x : y; 
}

int max (int x, int y)
{ 
    return (x > y)? x : y; 
}

int compare (const void *a, const void * b)
{
    return ( (*(struct Box *)b).d * (*(struct Box *)b).w ) - ( (*(struct Box *)a).d * (*(struct Box *)a).w );
}

int maxStackHeight( struct Box arr[], int n )
{
   struct Box rot[3*n];
   int index = 0;
   for (int i = 0; i < n; i++)
   {
      // Copy the original box
      rot[index].h = arr[i].h;
      rot[index].d = max(arr[i].d, arr[i].w);
      rot[index].w = min(arr[i].d, arr[i].w);
      index++;
  
      // First rotation 
      rot[index].h = arr[i].w;
      rot[index].d = max(arr[i].h, arr[i].d);
      rot[index].w = min(arr[i].h, arr[i].d);
      index++;
  
      // Second rotation 
      rot[index].h = arr[i].d;
      rot[index].d = max(arr[i].h, arr[i].w);
      rot[index].w = min(arr[i].h, arr[i].w);
      index++;
   }
  
   n = 3*n;
  
   qsort (rot, n, sizeof(rot[0]), compare);
  
   int msh[n];
   for (int i = 0; i < n; i++ )
      msh[i] = rot[i].h;
  
   for (int i = 1; i < n; i++ )
      for (int j = 0; j < i; j++ )
         if ( rot[i].w < rot[j].w &&
              rot[i].d < rot[j].d &&
              msh[i] < msh[j] + rot[i].h
            )
         {
              msh[i] = msh[j] + rot[i].h;
         }
  

   int max = -1;
   for ( int i = 0; i < n; i++ )
      if ( max < msh[i] )
         max = msh[i];
  
   return max;
}

int main(int argc , char *argv[])
{
   int n = (argc-1)/3;
   struct Box arr[n];
   for(int i = 0 ; i < argc-1 ; i+=3)
   {
      arr[i].h = atoi(argv[i+1]);
      arr[i].w = atoi(argv[i+2]);
      arr[i].d = atoi(argv[i+3]);
   }

   printf("%d\n",maxStackHeight(arr , n));  
   
   return 0;
}