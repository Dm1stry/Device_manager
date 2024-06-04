#ifndef BASE_SAVABLE_HPP 
#define BASE_SAVABLE_HPP

#include <QVector>
#include <QString>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
/*
Интерфейс для сохранения и восстановления состояния объекта.
*/

class BaseSavable
{
public:
    virtual json getStateToSave() = 0; // Метод для получения состояния для сохранения
    virtual bool restoreState(json) = 0; // Метод для восстановления состояния из сохраненных данных
    QVector<BaseSavable*> getChildren() const;
    void addChild(BaseSavable* child);
protected:
    virtual QString getName() const = 0;
private:
    QVector<BaseSavable*> children_;
};

#endif