#include <stdio.h>
#include <string.h>
#include <ctype.h>

void process(char *);
void normalize(char *);

int main(void)
{
   char str[1024];
/*   int t, T;*/

/*   scanf("%d\n", &T);
for (t = 0; t < T; t++)
{*/
   fgets(str, 1023, stdin);
   while (!feof(stdin))
   {
      normalize(str);
      process(str);
      printf("\n");
      fgets(str, 1023, stdin);
   }
/*}*/

   return 0;
}

void process(char *str)
{
   int len = strlen(str);
   int fact[16], fact_rev[16];
   int i, j, k, l;
   char buffer[10];

   if (len == 0) return;

   fact[0] = fact[1] = 1;
   for (i = 2; i <= 10; i++)
      fact[i] = fact[i - 1] * i;
   fact_rev[0] = 1;
   fact_rev[1] = len;
   for (i = 2; i <= len; i++)
      fact_rev[i] = fact_rev[i - 1] * (len - i + 1);
      
   for (i = 0; i < fact[len]; i++)
   {
      memset(buffer, 0, sizeof(buffer));
      for (j = 0; j < len; j++)
      {
         k = (i / fact_rev[j]) % (len - j);
         for (l = 0; l < len; l++)
            if (buffer[l] == 0)
            {
               if (k == 0)
               {
                  buffer[l] = str[len - j - 1];
                  break;
               }
               else
                  k--;
            }
      }
      printf("%s\n", buffer);
   }
}

void normalize(char *str)
{
   char buffer[1024];
   char *c;
   int len;

/*   c = strchr(str, '\n');
   if (c) *c = 0;
   c = strchr(str, '\r');
   if (c) *c = 0;*/

   for (c = str, len = 0; *c; c++)
   {
      if (isalpha((*c)) || isdigit((*c)))
         buffer[len++] = *c;
   }
   buffer[len] = 0;
   memcpy(str, buffer, 1024 * sizeof(char));
} 
