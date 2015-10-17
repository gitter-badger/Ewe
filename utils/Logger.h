#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

class Logger {
public:
  Logger ( );
  ~Logger ( );

  void debug(std::string message);
  void info(std::string message);
  void warn(std::string message);
  void error(std::string message);
  void fatal(std::string message);
};

#endif // LOGGER_H_
