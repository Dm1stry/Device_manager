#ifndef IP_VALIDATOR_HPP
#define IP_VALIDATOR_HPP

#include <QRegularExpressionValidator>

class IPValidator : public QRegularExpressionValidator
{
Q_OBJECT
public:
    IPValidator(QObject *parent = nullptr);
};

#endif