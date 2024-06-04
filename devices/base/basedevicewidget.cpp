#include "basedevicewidget.hpp"

BaseDeviceWidget::BaseDeviceWidget(QWidget * parent /*= nullptr*/)
  : QWidget(parent),
	status_(Status::IDLE),
	name_("no name"),
	operator_ptr_(nullptr)
{

}

BaseDeviceWidget::BaseDeviceWidget(QString name, QWidget * parent /*= nullptr*/)
  : QWidget(parent),
    status_(Status::IDLE),
    name_(name),
	operator_ptr_(nullptr)
{

}

BaseDeviceWidget::~BaseDeviceWidget()
{

}

// Возвращает имя устройства
QString BaseDeviceWidget::getName() const
{
	return name_;
}

// Конструирует набор битов команды, но не отсылает её
QByteArray BaseDeviceWidget::getCommand(QString command, QVector<double> arguments) const
{
	QByteArray byte_command;
	if(commands_.contains(command))  // Проверяем, есть лу у устройства команда с соответстующим именем
	{
		byte_command = (commands_[command])->buildCommand(arguments);
	}
	return byte_command;
}

// Устанавливает отображаемое имя устройства
void BaseDeviceWidget::setName(QString name)
{
	name_ = name;
}


void BaseDeviceWidget::setOperator(Operator *op)
{
	operator_ptr_ = op;
}

// Обрабатывает данные, пришедшие от класса опреатора, в том числе проверяет принадлежность
void BaseDeviceWidget::processData(QByteArray data)
{}

// Обрабатывает широковещательные сообщения, высылаемые устройствами
void BaseDeviceWidget::processBroadcast(QString command, QVector<double> arguments)
{
	
}


// Создает команду с соответствующим именем, адресом и аргументами. Если команда с таким именем уже существует, заменит её
void BaseDeviceWidget::setCommand(QString name, quint8 address, QVector<quint8> arg_lengths, quint8 command_length /*= 4*/)
{
	Command * new_command = new Command(name, address, arg_lengths, command_length, this);
	if(commands_.contains(name))
	{
		delete commands_[name];
		commands_.remove(name);
	}
	addChild(new_command);
	commands_[name] = new_command;
}


// Создает запрос с соответствующим именем и адресом. Если запрос с таким именем уже существует, заменит его
void BaseDeviceWidget::setRequest(QString name, quint8 address)
{
	Command * new_request = new Command(name, address, QVector<quint8>(), 1, this);
	if(requests_.contains(name))
	{
		delete requests_[name];
		requests_.remove(name);
	}
	addChild(new_request);
	requests_[name] = new_request;
}

// Изменяет имя существующей команды
void BaseDeviceWidget::renameCommand(QString old_name, QString new_name)
{
	if(commands_.contains(old_name))
	{
		commands_[old_name]->setName(new_name);
	}
}

// Удаляет команду с заданными именем
void BaseDeviceWidget::removeCommand(QString name)
{
	if(commands_.contains(name))
	{
		delete commands_[name];
		commands_.remove(name);
	}
}


// Отправляет байт код команды с закодированными аргументами физическому устройству
bool BaseDeviceWidget::executeCommand(QString command, QVector<double> arguments)
{
	if(commands_.contains(command))  // Проверяем, есть лу у устройства команда с соответстующим именем
	{
		QByteArray byte_command = (commands_[command])->buildCommand(arguments);
		emit newCommand(byte_command);
		return true;
	}
	return false;
}

/*
Позволяет исполнить команду заданную в текстовом формате. Нужно для работы планировщика задач
Принимает команду в виде:
	<имя_команды> <аргумент_1> <аргумент_2> ...
Аргументы должны быть целыми беззнаковыми числами
*/
bool BaseDeviceWidget::executeCommand(QString command_line)
{
	QStringList command_argv = command_line.split(' '); // Разбиваем строку команды на подстроки по пробелу
	if(commands_.contains(command_argv[0]))  // Проверяем, есть лу у устройства команда с соответстующим именем
	{
		QVector<double> arguments;
		for(int i = 1; i < command_argv.size(); ++i)
		{
			arguments.push_back(command_argv[i].toDouble());  // Собираем аргументы команды в вектор числовых значений
		}
		QByteArray command = (commands_[command_argv[0]])->buildCommand(arguments);
		emit newCommand(command);
		return true;
	}
	return false;
}


// Позволяет отправить запрос заданнуому устройству
bool BaseDeviceWidget::sendRequest(QString request)
{
	if(requests_.contains(request))
	{
		emit newRequest(requests_[request]->buildCommand());
		return true;
	}
	return false;
}

// Если у команды сменилось имя, обновит сохраненное у себя имя
void BaseDeviceWidget::updateCommandName(QString old_name, QString new_name)
{
	if(commands_.contains(old_name))
	{
		commands_[new_name] = commands_[old_name];
		commands_.remove(old_name);
	}
}

