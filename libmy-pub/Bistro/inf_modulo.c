/*
** inf_modulo.c for bistro in /home/barre-_t//afs/public/bistro
** 
** Made by thibault barre-villeneuve
** Login   <barre-_t@epitech.net>
** 
** Started on  Tue Nov  2 14:46:47 2010 thibault barre-villeneuve
** Last update Wed Nov  3 14:26:54 2010 marie baudy
*/

char	*inf_modulo(char *nb1, char *nb2, char *base, char *ops)
{
  char	*result;

  result = (char *) my_div_particular(nb1, nb2, base, ops);
  result = (char *) my_mult_particular(result, nb2, base, ops);
  result = (char *) my_sous_particular(nb1, result, base, ops);  
  return (result);
}
