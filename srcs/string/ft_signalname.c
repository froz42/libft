#include <macros.h>
#include <signal.h>
#include <stddef.h>
#include <ft_printf.h>

#define SIGNAL_NAME(signalname) [signalname] = #signalname

static const char *signals[] = {
	[0] = "0",
	[1] = "1",
	SIGNAL_NAME(SIGINT),
	SIGNAL_NAME(SIGQUIT),
	SIGNAL_NAME(SIGILL),
	SIGNAL_NAME(SIGTRAP),
	SIGNAL_NAME(SIGABRT),
	SIGNAL_NAME(SIGBUS),
	SIGNAL_NAME(SIGFPE),
	SIGNAL_NAME(SIGKILL),
	SIGNAL_NAME(SIGUSR1),
	SIGNAL_NAME(SIGSEGV),
	SIGNAL_NAME(SIGUSR2),
	SIGNAL_NAME(SIGPIPE),
	SIGNAL_NAME(SIGALRM),
	SIGNAL_NAME(SIGTERM),
	SIGNAL_NAME(SIGSTKFLT),
	SIGNAL_NAME(SIGCHLD),
	SIGNAL_NAME(SIGCONT),
	SIGNAL_NAME(SIGSTOP),
	SIGNAL_NAME(SIGTSTP),
	SIGNAL_NAME(SIGTTIN),
	SIGNAL_NAME(SIGTTOU),
	SIGNAL_NAME(SIGURG),
	SIGNAL_NAME(SIGXCPU),
	SIGNAL_NAME(SIGXFSZ),
	SIGNAL_NAME(SIGVTALRM),
	SIGNAL_NAME(SIGPROF),
	SIGNAL_NAME(SIGWINCH),
	SIGNAL_NAME(SIGIO),
	SIGNAL_NAME(SIGPWR),
	SIGNAL_NAME(SIGSYS),
};

/**
 * @brief Return the name of the signal
 *
 * @param sig the signal
 * @return const char* the name of the signal
 */
const char *ft_signalname(int sig)
{
	for (int i = 0; i < (int)ELEM_COUNT(signals); i++)
		if (i == sig)
			return signals[i];
	static char buf[32];
	ft_snprintf(buf, sizeof(buf), "SIGRT_%d", sig - ELEM_COUNT(signals));
	return buf;
}