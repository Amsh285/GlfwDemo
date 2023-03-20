#pragma once

#include "WindowApplication.h"

class WindowTestApplication final : public dsr::WindowApplication
{
private:
	virtual dsr::ApplicationExitCodes Setup() override;
};

