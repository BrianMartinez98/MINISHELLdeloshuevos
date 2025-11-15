#include "../minishell.h"
#include <sys/stat.h>
#include <unistd.h>

void    read_me_built(t_shell *shell)
{
    struct stat file_stat;
    char        *file_path = NULL;

    ft_putstr_fd("Minishell: README.md: Permission denied\n", STDERR);
    if (!shell->cmds || !shell->cmds[0] || !shell->cmds[0][0])
    {
        shell->last_status = 127;
        return ;
    }
    file_path = shell->cmds[0][0];
    if (!file_path)
    {
        shell->last_status = 127;
        return;
    }
    if (stat(file_path, &file_stat) == -1)
    {
        shell->last_status = 127; // Command not found
        return ;
    }
    if (!(file_stat.st_mode & S_IXUSR))
    {
        shell->last_status = 126; // Permission denied
        return ;
    }
    shell->last_status = 0;
}