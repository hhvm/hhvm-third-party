#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#ifdef __cplusplus
extern "C" {
#endif

#define WNOHANG 1
#define WEXITSTATUS(status) (((status)  & 0xff00) >> 8)
#define WIFEXITED(status) (WTERMSIG(status) == 0)
#define WIFSTOPPED(status) (((status) & 0xff) == 0x7f)
#define WIFSIGNALED(status) (!WIFSTOPPED(status) && !WIFEXITED(status))
#define WSTOPSIG(status) WEXITSTATUS(status)
#define WTERMSIG(status) ((status) & 0x7f)
#define WCOREDUMP(status) ((status) & 0x80)

#ifndef pid_t
#ifdef _WIN64
typedef __int64 pid_t;
#else
typedef int     pid_t;
#endif
#endif

pid_t waitpid(pid_t pid, int *stat_loc, int options);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_WAIT_H */