#include "ipvalidator.hpp"

IPValidator::IPValidator(QObject *parent /*= nullptr*/)
  : QRegularExpressionValidator(parent)
{
    QString ip_range = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegularExpression ip_regex ("^" + ip_range
                 + "\\." + ip_range
                 + "\\." + ip_range
                 + "\\." + ip_range + "$");
    this->setRegularExpression(ip_regex);
}