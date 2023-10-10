// TAD conjunto de inteiros - arquivo de teste
// Carlos Maziero, Set 2023

#include <stdio.h>
#include "set.h"

int main ()
{
  struct set_t *s1, *s2, *se, *su, *si, *sd, *sc, *sh ;

  printf ("==== set_create\n") ;
  s1 = set_create (100) ;
  s2 = set_create (100) ;
  printf ("s1: ") ;
  set_print (s1) ;
  printf ("s2: ") ;
  set_print (s2) ;

  printf ("=== set_add\n") ;
  for (int i = 20; i > 0; i-=2)
    set_add (s1, i) ;
  printf ("s1: ") ;
  set_print (s1) ;

  for (int i = 1; i < 20; i+=2)
    set_add (s2, i) ;
  printf ("s2: ") ;
  set_print (s2) ;

  printf ("=== set_del\n") ;
  printf ("Deleting from s1: ") ;
  for (int i = 6; i < 16; i++)
  { 
    printf ("%d ", i) ;
    set_del (s1, i) ;
  }
  printf ("\n") ;
  printf ("s1: ") ;
  set_print (s1) ;

  printf ("Deleting from s2: ") ;
  for (int i = 16; i >=6; i--)
  { 
    printf ("%d ", i) ;
    set_del (s2, i) ;
  }
  printf ("\n") ;
  printf ("s2: ") ;
  set_print (s2) ;

  printf ("=== set_equal\n") ;
  se = set_create (100) ;
  for (int i = 20; i > 0; i-=2)
    set_add (se, i) ;
  for (int i = 6; i < 16; i++)
    set_del (se, i) ;
  printf ("s1: ") ;
  set_print (s1) ;
  printf ("s2: ") ;
  set_print (s2) ;
  printf ("se: ") ;
  set_print (se) ;
  if (set_equal (s1, s2))
    printf ("s1 and s2 are equal\n") ;
  else
    printf ("s1 and s2 are different\n") ;
  if (set_equal (s1, se))
    printf ("s1 and se are equal\n") ;
  else
    printf ("s1 and se are different\n") ;

  printf ("=== set_union\n") ;
  su = set_create (100) ;
  set_union (s1, s2, su) ;
  printf ("s1: ") ;
  set_print (s1) ;
  printf ("s2: ") ;
  set_print (s2) ;
  printf ("su: ") ;
  set_print (su) ;

  printf ("=== set_intersect\n") ;
  set_add (se, 7) ;
  set_add (se, 35) ;
  si = set_create (100) ;
  set_intersect (se, su, si) ;
  printf ("se: ") ;
  set_print (se) ;
  printf ("su: ") ;
  set_print (su) ;
  printf ("si: ") ;
  set_print (si) ;

  printf ("=== set_diff (se - su)\n") ;
  sd = set_create (100) ;
  set_diff (se, su, sd) ;
  printf ("se: ") ;
  set_print (se) ;
  printf ("su: ") ;
  set_print (su) ;
  printf ("sd: ") ;
  set_print (sd) ;

  printf ("=== set_contains\n") ;
  if (set_contains (su, s1))
    printf ("su contains s1\n") ;
  else
    printf ("su does not contain s1\n") ;
  if (set_contains (su, s2))
    printf ("su contains s2\n") ;
  else
    printf ("su does not contain s2\n") ;
  if (set_contains (su, sd))
    printf ("su contains sd\n") ;
  else
    printf ("su does not contain sd\n") ;

  printf ("=== set_copy\n") ;
  sc = set_create (100) ;
  set_copy (su, sc) ;
  printf ("su: ") ;
  set_print (su) ;
  printf ("sc: ") ;
  set_print (sc) ;

  printf ("=== huge set\n") ;
  sh = set_create (50000) ;
  for (int i = 0; i < 50000; i++)
    set_add (sh, i) ;
  printf ("sh has %d items\n", set_card (sh)) ;

  printf ("=== set_destroy\n") ;
  set_destroy (s1) ;
  set_destroy (s2) ;
  set_destroy (se) ;
  set_destroy (su) ;
  set_destroy (si) ;
  set_destroy (sd) ;
  set_destroy (sc) ;
  set_destroy (sh) ;
}

