#pragma once
#include "Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

class Log
{
private:
	static std::shared_ptr<spdlog::logger> s_Logger;

public:
	Log();
	~Log();

	static void Init();
	static std::shared_ptr<spdlog::logger> GetLogger();
};