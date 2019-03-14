# QJsonChannel Core Library <img src="https://seeklogo.com/images/C/c-logo-43CE78FF9C-seeklogo.com.png" width="24" height="24">

QJsonChannelCore utilises ideas and some implementation details of [QJsonRpc](https://bitbucket.org/devonit/qjsonrpc) implementation. QJsonRpc library has tight integration with communication transport and supports server-to-client messages. So QJsonChannelCore library development was started for resolving these QJsonRpc specialties. 
In addition, QJsonChannelCore supports [JSON Schema Service Descriptor](https://jsonrpc.org/historical/json-schema-service-descriptor.html) for services and methods discovery.

The main component of QJsonChannelCore is QJsonChannelServiceRepository. 
~~~~~~
// Build a service repository
QJsonChannelServiceRepository serviceRepository;
~~~~~~

You can bind QObjects to the QJsonChannelServiceRepository.
~~~~~~
// Build a service object
QSharedPointer<QObject> testService (new TestService());

// Add the service to the repository
serviceRepository.addService ("object", "1.0", "test service", testService);
~~~~~~

The main funcuonality of the QJsonChannelServiceRepository is processing QJsonChannelMessage and dispatching them to QJsonChannelService.
~~~~~~
// A JSON-RPC request
QJsonChannelMessage request;
request.fromJson (...);

QJsonChannelMessage response = serviceRepository.processMessage (request);

// Get a JSOON-RPC response as a string
QByteArray ... = response.toJson ();
~~~~~~

You also can wrap your QObject by QJsonChannelService and work directly with the service:
~~~~~~
QJsonChannelService service("myService", "7.5 alpha", "Service answers toy your questions", QSharedPointer<QObject> (new Oracle ()));

// A JSON-RPC request
QJsonChannelMessage request = QJsonChannelMessage::createRequest("question", QJsonValue (42));

QJsonChannelMessage response = service.dispatch (request);

// Get a JSOON-RPC response as integer
int answer = response.result ().toInt ();
~~~~~~

## Service class

Service object should inherit from QObject
~~~~~~~
class TestService : public QObject {
	Q_OBJECT
public:

~~~~~~~

Properties are axposed using Q_PROPERTY
~~~~~~~
	Q_PROPERTY(float readOnlyProperty READ getReadOnlyProperty);
	Q_PROPERTY(int propertyWithGetterSetter READ getPropertyWithGetterSetter WRITE setPropertyWithGetterSetter);
~~~~~~~
Both getter and setter functions will be automatically added to a service for properties wich are binded to member:
~~~~~~~
	Q_PROPERTY(QString property MEMBER property);
~~~~~~~

Pubblic invokable methods will be exposed with QJsonChannel
~~~~~~~
	Q_INVOKABLE QString invokableGetter();
	Q_INVOKABLE void invokableSetter(QString p);
~~~~~~~

Public slots will be exposed as well:
~~~~~~~
public Q_SLOTS:
	void    slot();
	void    slotWithParams(const QString& first, bool second, double third);
	QString slotWithParamsAndReturnValue(const QString& name);

	void    slotWithVariantParams(const QString& first, bool second, double third, const QVariant& fourth);
	void    slotWithDefaultParameter(const QString& first, const QString& second = QString());
~~~~~~~~


[API Documentation](http://kdeyev.github.io/QJsonChannelCore)

## References
- [QJsonRpc](https://bitbucket.org/devonit/qjsonrpc) is a Qt implementation of the JSON-RPC protocol.
- [JSON Schema Service Descriptor](https://jsonrpc.org/historical/json-schema-service-descriptor.html) is simply a JSON Schema with the additional definition for methods.