//
// Created by veyrie_f on 29/12/16.
//

#include "ClientLauncher/Logger.hpp"
#include "ClientLauncher/LoggerController.hpp"

Logger::Logger() : GameObject("Logger")
{
    AddComponent<LoggerController>();
}

Logger::~Logger()
{
}

LIB_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new Logger();
}