#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED 1
#include <ft_printf.h>

#include <signal.h>

#define SICODE_NAME(sicode)                                                                        \
	case sicode:                                                                                   \
		return #sicode

/**
 * @brief Return the code name for the given signal and si_code
 *
 * @param sig the signal number
 * @param si_code the si_code of the signal
 * @return const char* the code name
 */
const char *ft_sicodename(int sig, int si_code)
{
	/* for kernel-generated signals */
	switch (si_code)
	{
		SICODE_NAME(SI_ASYNCNL);
		SICODE_NAME(SI_TKILL);
		SICODE_NAME(SI_SIGIO);
		SICODE_NAME(SI_ASYNCIO);
		SICODE_NAME(SI_MESGQ);
		SICODE_NAME(SI_TIMER);
		SICODE_NAME(SI_QUEUE);
		SICODE_NAME(SI_USER);
		SICODE_NAME(SI_KERNEL);
	}
	/* for signal specific signals */
	switch (sig)
	{
	case SIGILL:
		switch (si_code)
		{
			SICODE_NAME(ILL_ILLOPC);
			SICODE_NAME(ILL_ILLOPN);
			SICODE_NAME(ILL_ILLADR);
			SICODE_NAME(ILL_ILLTRP);
			SICODE_NAME(ILL_PRVOPC);
			SICODE_NAME(ILL_PRVREG);
			SICODE_NAME(ILL_COPROC);
			SICODE_NAME(ILL_BADSTK);
		}
		break;
	case SIGFPE:
		switch (si_code)
		{
			SICODE_NAME(FPE_INTDIV);
			SICODE_NAME(FPE_INTOVF);
			SICODE_NAME(FPE_FLTDIV);
			SICODE_NAME(FPE_FLTOVF);
			SICODE_NAME(FPE_FLTUND);
			SICODE_NAME(FPE_FLTRES);
			SICODE_NAME(FPE_FLTINV);
			SICODE_NAME(FPE_FLTSUB);
		}
		break;
	case SIGSEGV:
		switch (si_code)
		{
			SICODE_NAME(SEGV_MAPERR);
			SICODE_NAME(SEGV_ACCERR);
			SICODE_NAME(SEGV_BNDERR);
			SICODE_NAME(SEGV_PKUERR);
		}
		break;
	case SIGBUS:
		switch (si_code)
		{
			SICODE_NAME(BUS_ADRALN);
			SICODE_NAME(BUS_ADRERR);
			SICODE_NAME(BUS_OBJERR);
			SICODE_NAME(BUS_MCEERR_AR);
			SICODE_NAME(BUS_MCEERR_AO);
		}
		break;
	case SIGTRAP:
		switch (si_code)
		{
			SICODE_NAME(TRAP_BRKPT);
			SICODE_NAME(TRAP_TRACE);
			SICODE_NAME(TRAP_BRANCH);
			SICODE_NAME(TRAP_HWBKPT);
			SICODE_NAME(TRAP_UNK);
		}
		break;
	case SIGCHLD:
		switch (si_code)
		{
			SICODE_NAME(CLD_EXITED);
			SICODE_NAME(CLD_KILLED);
			SICODE_NAME(CLD_DUMPED);
			SICODE_NAME(CLD_TRAPPED);
			SICODE_NAME(CLD_STOPPED);
			SICODE_NAME(CLD_CONTINUED);
		}
		break;
	case SIGPOLL:
		switch (si_code)
		{
			SICODE_NAME(POLL_IN);
			SICODE_NAME(POLL_OUT);
			SICODE_NAME(POLL_MSG);
			SICODE_NAME(POLL_ERR);
			SICODE_NAME(POLL_PRI);
			SICODE_NAME(POLL_HUP);
		}
		break;
	}
	static char buff[64];
	ft_snprintf(buff, sizeof(buff), "UNKNOWN (%d)", si_code);
	return buff;
}