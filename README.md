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
QObject* testService = new TestService();

// Add the service to the repository
serviceRepository.addService ("agent", "1.0", "test service", testService);
~~~~~~

The main funcuonality of the QJsonChannelServiceRepository is processing QJsonChannelMessage and dispatching them to QJsonChannelService.
~~~~~~

// A JSON-RPC request
QJsonChannelMessage request;
request.fromJson(...);

QJsonChannelMessage response = serviceRepository.processMessage (request);

// Get a JSOON-RPC response
QByteArray ... = response.toJson();
~~~~~~

[API Documentation](http://kdeyev.github.io/QJsonChannelCore)

## References
- [QJsonRpc](https://bitbucket.org/devonit/qjsonrpc) is a Qt implementation of the JSON-RPC protocol.
- [JSON Schema Service Descriptor](https://jsonrpc.org/historical/json-schema-service-descriptor.html) is simply a JSON Schema with the additional definition for methods.