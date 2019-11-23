int main (void)
{
  int arr1[0];
  int arr2[1];
  int arr3[4];

  arr2[0] = 10;


  arr3[0] = 0;
  arr3[1] = 1;
  arr3[2] = 2;
  arr3[3] = 3;

  printf("%d\n", arr1[0]);

  printf("%d\n", arr2[0]);

  printf("%d\n",arr3[0]);
  printf("%d\n",arr3[1]);
  printf("%d\n",arr3[2]);
  printf("%d\n",arr3[3]);

  if( arr3[3] == 3 && arr3[3] != 2 )
  {
    printf("1\n");
  }
  else
  {
    printf("0\n");
  }

  if( arr3[3] == 3 || arr3[3] != 2 )
  {
    printf("1\n");
  }
  else
  {
    printf("0\n");
  }

  if( arr3[3] == 3 && ( arr3[0] != 0 || arr3[3] != 2 ) )
  {
    printf("1\n");
  }
  else
  {
    printf("0\n");
  }

  return 0;
}
