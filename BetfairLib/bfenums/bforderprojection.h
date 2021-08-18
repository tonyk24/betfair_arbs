#ifndef BFORDERPROJECTION
#define BFORDERPROJECTION

#include <stdexcept>
#include <QString>

class BfOrderProjection {
public:
  enum Enum { ALL,
              EXECUTABLE,
              EXECUTION_COMPLETE };

  static Enum toEnum(const QString &str) {
    if (str == "ALL") {
      return ALL;
    } else if (str == "EXECUTABLE") {
      return EXECUTABLE;
    } else if (str == "EXECUTION_COMPLETE") {
      return EXECUTION_COMPLETE;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == ALL) {
      return QString("ALL");
    } else if (t == EXECUTABLE) {
      return QString("EXECUTABLE");
    } else if (t == EXECUTION_COMPLETE) {
      return QString("EXECUTION_COMPLETE");
    }
    return QString("UNKOWN_BfOrderProjectionEnum");
  }
};

#endif // BFORDERPROJECTION

