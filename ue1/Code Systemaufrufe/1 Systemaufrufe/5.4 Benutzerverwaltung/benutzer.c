
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd. h.>
#include <string.h>

int main(int argc, char *argv[]) {
   struct passwd *pas_ptr;
   if( argc != 2 ) {
      fprintf(stderr, "Usage: %s Name\n", argv[0]);
      exit (EXIT_FAILURE);
   }
  /* Alternativ mit getpwuid() :                       */
  /* pas_ptr=getpwuid( strtoul(argv[1], NULL, 10) );   */

   pas_ptr = getpwnam(argv[1]);
   if(pas_ptr == NULL) {
      printf("Konnte nichts über %s ermitteln\n", argv[1]);
      exit (EXIT_FAILURE);
   }

  /* TODO: Konfiguration der fehlenden Parameter
   printf("Folgende Angaben wurden ermittelt: \n");
   printf("Benutzername     : %s\n", todo);
   printf("Benutzernummer   : %d\n", todo);
   printf("Gruppennummer    : %d\n", todo);
   printf("Kommentar        : %s\n", todo);
   printf("Loginverzeichnis : %s\n", todo);
   printf("Loginshell       : %s\n", todo);
   return EXIT_SUCCESS;
}
