 /*
 * echoChar1.c
 * Echoes a character entered by the user.
 * Bob Plantz - 4 June 2009
 */
#include <unistd.h>

int main(void)
{
  char aLetter;

  write(STDOUT_FILENO, "Enter one character: ", 21); //prompt user
  read(STDIN_FILENO, &aLetter, 2);
  write(STDOUT_FILENO, "You entered: ", 13);
  write(STDOUT_FILENO, &aLetter, 1);


  return 0;
}
