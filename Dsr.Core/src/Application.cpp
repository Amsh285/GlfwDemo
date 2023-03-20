#include "Application.h"

namespace dsr
{
	int ApplicationExitCodes::SuccessExitCode = EXIT_SUCCESS;

	ApplicationExitCodes ApplicationExitCodes::Success()
	{
		return ApplicationExitCodes("No Errors found.", SuccessExitCode);
	}
}
