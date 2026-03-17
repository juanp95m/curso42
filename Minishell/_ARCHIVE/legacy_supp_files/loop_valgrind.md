# simple

```
#include "minishell.h"

int	main(void)
{
	char *input_readline;
	t_shell shell;

	shell.last_exit_code = 0;
	while (1)
	{
		input_readline = readline("Miguishell$>");
		if (input_readline == NULL)
		{
			// rl_clear_history();
			break;
		}
		else if (strlen(input_readline) == 0)
			{
				free(input_readline);
				continue;
			}
		// add_history(input_readline);
		free(input_readline);
	}
	return (0);
}
```

```
==1648222== LEAK SUMMARY:
==1648222==    definitely lost: 0 bytes in 0 blocks
==1648222==    indirectly lost: 0 bytes in 0 blocks
==1648222==      possibly lost: 0 bytes in 0 blocks
==1648222==    still reachable: 214,344 bytes in 250 blocks
==1648222==         suppressed: 0 bytes in 0 blocks
==1648222== 
==1648222== For lists of detected and suppressed errors, rerun with: -s
==1648222== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

# with history
```
#include "minishell.h"

int	main(void)
{
	char *input_readline;
	t_shell shell;

	shell.last_exit_code = 0;
	while (1)
	{
		input_readline = readline("Miguishell$>");
		if (input_readline == NULL)
		{
			rl_clear_history();
			break;
		}
		else if (strlen(input_readline) == 0)
			{
				free(input_readline);
				continue;
			}
		add_history(input_readline);
		free(input_readline);
	}
	return (0);
}
```

```
==1648919== 
==1648919== LEAK SUMMARY:
==1648919==    definitely lost: 0 bytes in 0 blocks
==1648919==    indirectly lost: 0 bytes in 0 blocks
==1648919==      possibly lost: 0 bytes in 0 blocks
==1648919==    still reachable: 214,344 bytes in 250 blocks
==1648919==         suppressed: 0 bytes in 0 blocks
==1648919== 
==1648919== For lists of detected and suppressed errors, rerun with: -s
==1648919== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```